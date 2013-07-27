#ifndef FASTREAD_FASTREAD_H
#define FASTREAD_FASTREAD_H

#include <Rcpp.h>

#include <iostream>
#include <fstream>
#include <sstream>

namespace fastread {
    
    class MMapReader ;
    
    class VectorInput {
    public:
        VectorInput( MMapReader& reader_) : reader(reader_) {}
        virtual ~VectorInput(){} ;
        
        virtual void set( int i ) = 0 ;
        
        virtual SEXP get() = 0;
    protected:
        MMapReader& reader ;
    } ;
    
    class VectorInput_Integer : public VectorInput {
    public:
        VectorInput_Integer( int n, MMapReader& reader_ ) : VectorInput(reader_), data(n){}
        void set( int i ) ;
        inline SEXP get(){ return data ; } 
        
    private:
        Rcpp::IntegerVector data ;
        char* end ;
    } ;
    
    class VectorInput_Double : public VectorInput {
    public:
        VectorInput_Double( int n, MMapReader& reader_ ) : VectorInput(reader_), data(n){}
        void set( int i ) ;
        inline SEXP get(){ return data ; } 
        
    private:
        Rcpp::DoubleVector data ;
        char* end ;
    } ;
    
    class VectorInput_String : public VectorInput {
    public:
        VectorInput_String( int n, MMapReader& reader_ ) : VectorInput(reader_), data(n){}
        void set( int i ) ;
        inline SEXP get(){ return data ; } 
        
    private:
        Rcpp::CharacterVector data ;
        char* end, *start ;
        std::string buffer ;
    } ;
    
    class VectorInput_Skip : public VectorInput {
    public:
        VectorInput_Skip( int , MMapReader& reader_ ) : VectorInput(reader_){}
        void set( int i ) ;
        inline SEXP get(){ return R_NilValue ; } 
    } ;
    
    VectorInput* make_vector_input( int rtype, int n, MMapReader& ) ;
    VectorInput* make_vector_input( const std::string& clazz, int n, MMapReader& ) ;
        
    class MMapReader {
       public:
           MMapReader( const std::string& filename, char sep_ = ',', char quote_ = '"', char esc_ = '\\' ) ;
           ~MMapReader() ;
           
           void read(int n) ;
           Rcpp::List get() ;
           
           inline char* get_pointer() const { return p; }
           inline void  set_pointer(char* p_) { p = p_ ; }
           
           void move_until_next_token_start() ;
           
       private:
           
           int file_descriptor ;
           char sep, quote, esc ;
           
           char* memory_start ;
           char* p ;
           size_t filesize ;
           bool inquote ;
           
           int n, ncol ;
           std::vector<VectorInput*> inputs ;
    } ;
    
}     

#endif
