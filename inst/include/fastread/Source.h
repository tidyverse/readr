#ifndef FASTREAD_Source_H
#define FASTREAD_Source_H

namespace fastread {
       
    template <typename Class>
    class Source {
    public:
        
        Source(char sep_, char quote_, char esc_) : sep(sep_), quote(quote_), esc(esc_), inquote(false) {}
        
        inline void set(char* p_, char* end_){ 
            p = p_ ; end = end_ ;
        }
        inline char* get(){ 
            return p ; 
        }
        
        void skip(){
            move_until_next_token_start(); 
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
            return Rf_mkCharLen( q, move_until_next_token_start() ) ;
        }
        
        double get_double(){
            using boost::spirit::qi::double_;
            using boost::spirit::qi::parse;
            double res = 0.0 ;
            char* q = p ;
            parse( q, q + move_until_next_token_start(), double_, res ) ;
            return res ;
        }
    
    protected:
        char* p ;
        char* end ;
        
    private:      
    
        char sep, quote, esc ;
        bool inquote ;
        
        inline bool valid_digit(char c){
            static char before_zero = '0' - 1 ;
            static char after_nine = '9' + 1 ;
            return c > before_zero && c < after_nine ;
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
            for (value = 0; valid_digit(*p); ++p ) {
                value = value * 10 + (*p - '0');
            }
        
            return sign * value ;
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
                    } else if( next == sep || next == '\n' ){
                        // end of line
                        break ;
                    } else if( next == '\r' && *p == '\n' ){
                        p++; break ;    
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
            return len ;
        }
    
        
    } ;
}

#endif
