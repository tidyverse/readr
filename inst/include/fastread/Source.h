#ifndef FASTREAD_Source_H
#define FASTREAD_Source_H

namespace fastread {
      
    template <typename Class, template <class> class LinePolicy = KeepAllLines >
    class Source {
    public:
        
        Source(char sep_, char quote_, char esc_, LinePolicy<Source> line_policy_ = LinePolicy<Source>() ) : 
            sep(sep_), quote(quote_), esc(esc_), inquote(false), line_policy(line_policy_)
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
        
        SEXP get_String(){
            char* q = p ;
            int len = move_until_next_token_start() ;
            while( *q == quote ){
                len-- ;
                q++ ;
            }
            while( q[len-1] == quote ){
                len-- ;    
            }
            SEXP res = Rf_mkCharLen( q, len ) ;
            return res ;
        }
        
        double get_double(){
            using boost::spirit::qi::double_;
            using boost::spirit::qi::parse;
            double res = 0.0 ;
            char* q = p ;
            parse( q, q + move_until_next_token_start(), double_, res ) ;
            return res ;
        }
        
        inline int count_lines(bool header) {
            return count_lines__impl( header, typename Rcpp::traits::same_type< LinePolicy<Source>, KeepAllLines<Source> >::type() ) ;
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
        char sep, quote, esc ;
        bool inquote ;
        LinePolicy<Source> line_policy ;
        
        CharacterVector get_headers(int nc, bool header){
            if( p == end ) more() ;
            CharacterVector out(nc) ;
            if(header){
                for( int i=0; i<nc; i++){
                    out[i] = get_String();     
                }
                return out ;
            } else {
                for( int i=0; i<nc; i++){
                    String V("V") ; V += (i+1) ;
                    out[i] = V ;
                }
                on_newline() ;
            }
            return out ;
        }
        
    private:
        
        // fast implementation of count lines as there is no need to 
        // ask the line policy if we keep the line
        int count_lines__impl( bool header, Rcpp::traits::true_type ){
            int n = 0 ;
            if( p == end ) more() ;
            
            // skip the first line if necessary
            if( header ) {
                p = std::find( p, end, '\n' ) + 1 ;
            }
            while(true){
                n += std::count( p, end, '\n' ) ;
                p = end ;
                if( !more() ) break ;    
            }
            return n ;            
        }
        
        // for each line, we need to ask to the line policy if we keep the line
        int count_lines__impl( bool header, Rcpp::traits::false_type ){
            int n = 0 ;
            if( p == end ) more() ;
            
            // skip the first line
            if( header ){
                p = std::find(p, end, '\n' ) + 1;
            }
            while(true){
                char* q = p ;
                while( q < end ){
                    q = std::find(q, end, '\n' ) ;
                    if( q < end && line_policy.keep_line(*this) ) {
                        n++ ;
                    }
                    q++ ;
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
            while ( *p == ' ' ) {
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
        
            // Get digits before decimal point or exponent, if any.
            for (value = 0; valid_digit(); ++p ) {
                value = value * 10 + digit_value() ;
            }
        
            return sign * value ;
        }
        
        inline void on_newline(){
            ensure_full_line();                
            if( !line_policy.keep_line(*this) ) {
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
                    } else if( next == sep ){
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
