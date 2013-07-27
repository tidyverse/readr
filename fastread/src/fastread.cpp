#include "fastread.h"

using namespace Rcpp ;

namespace fastread{
    
    template <typename T>
    class FromString{
    public:
        FromString() : ss(""){} 
        
        // maybe worth using e.g. atoi for int, etc ...
        T get( const std::string& s){
            ss.str( s );
            ss >> value ;
            return value ;
        }
        
    private:
        std::istringstream ss ;
        T value ;
    } ;  
    
    template <>
    class FromString<int>{
    public:
        FromString() {} 
        inline int get( const std::string& s){
            return atoi(s.c_str());
        }
        
    } ;  
    
    template <>
    class FromString<double>{
    public:
        FromString() {} 
        inline double get( const std::string& s){
            return atof(s.c_str());
        }
        
    } ;  
    
    
    template <>
    class FromString< String >{
       public:
           FromString(){}
           String get(const std::string& s){ return String(s) ;}
       
    } ;
    
    class VectorInput {
    public:
        VectorInput(){}
        virtual ~VectorInput(){} ;
        
        virtual void set( int i, const std::string& chunk ) = 0 ;
        virtual SEXP get() = 0; 
    } ;
    
    template <typename Storage, typename Converter>
    class VectorInput_Template : public VectorInput {
    public:
        VectorInput_Template( int n ) : data(n), converter() {}
        
        void set( int i, const std::string& chunk ){
            data[i] = converter.get( chunk ) ;
        }
        SEXP get(){ return data ; }
        
    private:
        Storage data;  
        Converter converter ;
    } ;
    
    // just does nothing with the chunk
    class VectorInput_Skip : public VectorInput {
    public:
        VectorInput_Skip( int n ){}
        void set( int i, const std::string& chunk ){}
        SEXP get(){ return R_NilValue; }
    };
    
    typedef VectorInput_Template< IntegerVector   , FromString<int>    > VectorInput_Integer ;
    typedef VectorInput_Template< DoubleVector    , FromString<double> > VectorInput_Double  ;
    typedef VectorInput_Template< CharacterVector , FromString<String> > VectorInput_String  ;
    
    VectorInput* make_vector_input( int rtype, int n ){
        switch( rtype ){
            case INTSXP:  return new VectorInput_Integer(n) ;
            case REALSXP: return new VectorInput_Double(n) ;
            case STRSXP:  return new VectorInput_String(n) ;
            default:
                stop( "unsupported type" ) ;
        }
        return 0 ;
    }
    
    VectorInput* make_vector_input( const std::string& clazz, int n ){
        if( ( clazz == "int" )   || ( clazz == "I" ) || ( clazz == "integer"   ) ) return new VectorInput_Integer(n) ;
        if( ( clazz == "double") || ( clazz == "D" ) || ( clazz == "numeric"   ) ) return new VectorInput_Double(n) ;
        if( ( clazz == "string") || ( clazz == "S" ) || ( clazz == "character" ) ) return new VectorInput_String(n) ;
        if( clazz == "_" ) return new VectorInput_Skip(n) ;
        stop( "unsupported" ) ;
        return 0 ;
    }
    
    // PIMPL class around VectorInput
    class ScanInput {
    public:
        ScanInput( int rtype, int n) : input( make_vector_input(rtype, n) ){}
        ScanInput( const std::string& clazz, int n) : input( make_vector_input(clazz, n) ){}
        ~ScanInput(){ delete input ; }
        inline void set(int i, const std::string& chunk ){ input->set(i, chunk) ; }
        inline SEXP get(){ return input->get(); }
        
    private:
        VectorInput* input ;
    } ;   
    
    class DataReader {
    public:
        DataReader(int n_) : n(n_), inputs(), ncol(2) {
            inputs.push_back( new VectorInput_Integer(n) ) ;
            inputs.push_back( new VectorInput_Double(n)  ) ;
            // inputs.push_back( new VectorInput_String(n)  ) ;
        }
        
        void read_file( const std::string& filename){
            FileReader reader(filename) ;
            
            for( int i=0; i<n; i++){
                for( int j=0; j<ncol; j++){
                    inputs[j]->set( i, reader.get_token() ) ;    
                }
            }
        }
        
        ~DataReader(){
            // deleting the inputs
            for( int i=0; i<ncol; i++){
                delete inputs[i] ;    
            }
        }
        
        List get(){
            List out(ncol) ;
            for( int i=0; i<ncol; i++){
                out[i] = inputs[i]->get() ;    
            }
            return out ;
        }
        
    private:
        int n ;
        // TODO: make a dedicated class for inputs, e.g.
        // DataFrameInput
        std::vector< VectorInput* > inputs ;
        int ncol ;
    } ; 

}


using namespace fastread ;

// [[Rcpp::export]]
List read_csv(std::string file, int n ){
    DataReader reader( n ) ;
    reader.read_file( file ) ;
    return reader.get() ;
}

// [[Rcpp::export]]
SEXP scan_( std::string filename, int n, SEXP what ){
    ScanInput input( TYPEOF(what), n) ;
    FileReader reader(filename) ;
    for( int i=0; i<n; i++){
        if( reader.is_finished() ) break ;
        input.set( i, reader.get_token() ) ;
    }
    return input.get() ;
}

