#ifndef FASTREAD_DATE_TIME_PARSER_H
#define FASTREAD_DATE_TIME_PARSER_H

namespace fastread {
        
    template <typename Class>
    class DateTimeParser{
    public:
        
        double parse_Date( char*& stream ){
            p = stream ;
            double res = 0 ;
            
            if( valid_digit() ){
                
                // reading year
                int y = read_year() ;
                if( y >= 0 ){
                                    // feb 29th
                    res += y*YEAR + ( (y+1)/4 ) ;     
                }
                
                skip_non_digit() ;
                
                // month
                if( valid_digit() ){
                    int m = read_month() ;
                    res += days_at_month_start(m) ;
                    
                    // feb 29th
                    if( m > 2 && (y&3) == 2 ) res += 1 ;
                    
                    skip_non_digit() ;
                    
                    // day
                    if( valid_digit() ){
                        int d = read_day() ;
                        if( d > 1 ){
                            res += d ;    
                        }
                    }
                    
                }
                
            }
            
            
            stream = p ;
            return res ;
        }
        
        double parse_DateTime_Ymd(char*& stream){
            
            
            p = stream ;
            double res = 0.0 ;
            if( valid_digit() ){
                
                // reading year
                int y = read_year() ;
                if( y >= 0 ){
                                    // feb 29th
                    res += y*YEAR + ( (y+1)/4 ) * DAY ;     
                }
                
                skip_non_digit() ;
                
                // month
                if( valid_digit() ){
                    int m = read_month() ;
                    res += seconds_at_month_start(m) ;
                    
                    // feb 29th
                    if( m > 2 && (y&3) == 2 ) res += DAY ;
                    
                    skip_non_digit() ;
                    
                    // day
                    if( valid_digit() ){
                        int d = read_day() ;
                        if( d > 1 ){
                            res += DAY * d ;    
                        }
                    }
                    
                }
                
            }
            
            stream = p;
            return res ;
        }
        
    private:
        char* p ;
        
        inline int seconds_at_month_start(int m){ 
            static const int data[] = { 0, 0, 2678400, 5097600, 7776000, 10368000, 13046400, 15638400,
                    18316800, 20995200, 23587200, 26265600, 28857600, 31536000 };
            return data[m] ;
        }
        
        inline int days_at_month_start(int m){
            static const int data[] = { 0, 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 } ;
            return data[m] ;
        }
        
        inline bool valid_digit(){
            return *p >= '0' && *p <= '9' ;    
        }
        
        inline int digit_value(){
            return *p - '0' ;    
        }
        
        static const int YEAR = 31536000 ;    
        static const int MINUTE = 60;
        static const int HOUR = 3600 ;
        static const int DAY = 86400 ;
		
		inline int read_year(){
            int y = read_int() ;
            if( y < 100 ) y+=2000 ;
            y -= 1970;
            return y ;
        }
        
        inline int read_month(){
            return read_int() ;
        }
        
        inline int read_day(){
            return read_int() ;
        }
        
        inline int read_int(){
            int m = 0 ;
            while( valid_digit() ) m = m*10 + digit_value(); p++ ;
            return m ;
        }
        
        inline void skip_non_digit(){
            while( !valid_digit() ) p++ ;    
        }
        
    };
    
}

#endif
