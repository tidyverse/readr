#ifndef FASTREAD_Source_H
#define FASTREAD_Source_H

namespace fastread {

    template <typename Class,
        typename LinePolicy = KeepAllLines,
        typename SeparatorPolicy = SingleCharacterSeparator
    >
    class Source {
    public:

        Source(
            LinePolicy line_policy_ = LinePolicy(),
            SeparatorPolicy sep_policy_ = SeparatorPolicy()
        ) :
            quote('"'), esc('\\'), inquote(false), line_policy(line_policy_), sep_policy(sep_policy_)
        {}

        inline void set(char* p_, char* end_){
            p = p_ ; end = end_ ;
        }
        inline char* get(){
            return p ;
        }

        void skip(){
            move_until_next_token_start();
        }

        void skip_line(){
            move_until_next_line() ;
        }

        SEXP get_line(){
            char* q = p;
            return Rf_mkCharLen(q, move_until_next_line());
        }

        int get_int(){
            int res = get_int_naive();
            move_until_next_token_start() ;
            return res ;
        }

        SEXP get_String(bool trim = true){
            char* q = p ;
            int len = move_until_next_token_start() ;

            // skip initial quote
            if( *q == quote ){
                len-- ;
                q++ ;
            }

            // skip end quote
            if( q[len-1] == quote ){
                len-- ;
            }

            // trim leading and trailing whitespaces
            if (trim) {
              if (*q == ' ') {
                len--;
                q++;
              }
              if (q[len-1] == ' ')
                len--;
            }

            // check if there are double quotes
            for( int i=0; i<len-1; i++){
                if( q[i] == '"' && q[i+1] == '"' ){
                    // found a double quote. so we need to escape it : "" -> \"

                    std::string buffer(q, q+len) ;
                    buffer.erase( i, 1 ) ;

                    size_t pos = i + 1;
                    while( ( pos = buffer.find( "\"\"", pos ) ) != std::string::npos){
                        buffer.erase( pos, 1 ) ;
                    }

                    return Rf_mkCharLen( buffer.data(), buffer.size() ) ;

                }
            }

            // double quotes not found
            SEXP res = Rf_mkCharLen( q, len ) ;

            return res ;
        }

        double get_double(){
            using boost::spirit::qi::double_;
            using boost::spirit::qi::parse;
            double res = 0.0 ;
            while( *p == ' ' || *p == '\t' || *p == '"' || *p == '\'' ) ++p ;
            char* q = p ;
            parse( q, q + move_until_next_token_start(), double_, res ) ;
            return res ;
        }

        inline int count_lines() {
            int res = count_lines__impl(typename Rcpp::traits::same_type< LinePolicy, KeepAllLines >::type() ) ;
            line_policy.reset() ;
            return res ;
        }

        double get_Date_Ymd(){
            char* start = p ;
            return date_time_parser.parse_Date(start, start + move_until_next_token_start() ) ;
        }

        double get_POSIXct(){
            char* start = p ;
            return date_time_parser.parse_POSIXct(start, start + move_until_next_token_start() ) ;
        }

        double get_Time(){
            char* start = p ;
            return date_time_parser.parse_Time(start, start + move_until_next_token_start() ) ;
        }

        char* p ;
        char* end ;
        DateTimeParser<Class> date_time_parser ;
        char quote, esc ;
        bool inquote ;
        LinePolicy line_policy ;
        SeparatorPolicy sep_policy ;

    private:

        // fast implementation of count lines as there is no need to
        // ask the line policy if we keep the line
        int count_lines__impl(Rcpp::traits::true_type ){
            int n = 0 ;
            if( p == end ) more() ;

            // skip the first line if necessary
            while(true){
                n += std::count( p, end, '\n' ) ;
                p = end ;
                if( !more() ) break ;
            }

            // get pointer to antepenultimate (before last) character
            p -= 2;

            // increment the number of lines by one if antepenultimate
            // character is not positioned on a full line
            return n + (int)(!ensure_full_line());

            // TODO: Might need to do the same trick in the function below
            // I still have not figured out when it is supposed to be used
        }

        // for each line, we need to ask to the line policy if we keep the line
        int count_lines__impl(Rcpp::traits::false_type ){
            int n = 0 ;
            if( p == end ) more() ;

            while(true){
                char* q = p ;
                while( q < end ){
                    q = std::find(q, end, '\n' ) ;
                    if( q < end && line_policy.keep_line(++q) ) {
                        n++ ;
                    }
                }
                p = end ;
                if( !more() ) break ;
            }
            return n ;
        }

        bool more(){
            return static_cast<Class&>(*this).more() ;
        }

        bool ensure_full_line(){
            return static_cast<Class&>(*this).ensure_full_line() ;
        }

        inline bool valid_digit(){
            return *p >= '0' && *p <= '9' ;
        }

        inline int digit_value(){
            return *p - '0' ;
        }

        inline int get_int_naive() {
            int sign, value ;

            // Skip leading white space, if any.
            while ( *p == ' ' || *p == '"' || *p == '\'') {
                ++p ;
            }

            // Get sign, if any.
            sign = 1;
            if (*p == '-') {
                sign = -1;
                ++p ;
            } else if (*p == '+') {
                ++p ;
            }

            // Exception needed because if the first character is not a
            // valid digit, then the function returns 0, which is not a
            // nice way to handle NA
            if (!valid_digit())
              return -1;

            // Get digits before decimal point or exponent, if any.
            for (value = 0; valid_digit(); ++p ) {
                value = value * 10 + digit_value() ;
            }

            return sign * value ;
        }

        inline void on_newline(){
            ensure_full_line();
            if( !line_policy.keep_line(p) ) {
                move_until_next_line() ;
            }
        }

        int move_until_next_token_start(){
            char next;
            int len = 0 ;
            while(p<end){
                next = *(p++) ;
                if( inquote ){
                    if( next == esc ){
                        // the next character is an escape character
                        ++p ; len++ ;
                    } else if( next == quote ){
                        // ending the quote
                        inquote = false ;
                    }
                } else {
                    if( next == quote ){
                        // entering a quote
                        inquote = true ;
                    } else if( sep_policy.is_sep(next) ){
                        break ;
                    } else if( next == '\n' ){
                        // end of line
                        on_newline() ;
                        break ;
                    } else if( next == '\r' && *p == '\n' ){
                        p++;
                        on_newline() ;
                        break ;
                    }
                }
                len++ ;
            }
            return len ;
        }

        int move_until_next_line(){
            char next;
            int len = 0 ;
            while( p < end ){
                next = *(p++) ;
                if( next == '\n' ){
                    break ;
                } else if( next == '\r' && *p == '\n' ){
                    p++;
                    break ;
                }
                len++ ;
            }
            if( p < end ) on_newline() ;
            return len ;
        }

    } ;


}

#endif
