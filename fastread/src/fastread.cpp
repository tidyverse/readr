#include <Rcpp.h>
#include <boost/tokenizer.hpp>

#include <iostream>
#include <fstream>
#include <sstream>

// [[Rcpp::depends(BH)]]

using namespace Rcpp ;

namespace fastread{
    
    /**
     * Abstraction around Boost::Tokenizer, so that we can use something else
     * without affecting the rest of the code
     */
    class Tokenizer {
        typedef boost::tokenizer< boost::escaped_list_separator<char> > BoostTokenizer ;
        BoostTokenizer tokenizer_ ;
        
    public:
        typedef BoostTokenizer::const_iterator const_iterator ;
        
        Tokenizer(const std::string& line) : tokenizer_(line){}
        const_iterator begin() const { return tokenizer_.begin(); }
        const_iterator end() const   { return tokenizer_.end(); }
    } ;
    
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
    class FromString< String >{
       public:
           FromString(){}
           String get(const std::string& s){ return String(s) ;}
       
    } ;
    
    class VectorInput_Base {
    public:
        VectorInput_Base(){}
        virtual ~VectorInput_Base(){} ;
        
        virtual void set( int i, const std::string& chunk ) = 0 ;
        virtual SEXP get() = 0; 
    } ;
    
    template <typename Storage, typename Converter>
    class VectorInput : public VectorInput_Base {
    public:
        VectorInput( int n ) : data(n), converter() {}
        
        void set( int i, const std::string& chunk ){
            data[i] = converter.get( chunk ) ;
        }
        SEXP get(){ return data ; }
        
    private:
        Storage data;  
        Converter converter ;
    } ;
    
    typedef VectorInput< IntegerVector   , FromString<int>    > VectorInput_Integer ;
    typedef VectorInput< DoubleVector    , FromString<double> > VectorInput_Double  ;
    typedef VectorInput< CharacterVector , FromString<String> > VectorInput_String  ;
    
    class DataReader {
    public:
        DataReader(int n_) : n(n_), data(), ncol(1) {
            data.push_back( new VectorInput_Integer(n) ) ;
            // data.push_back( new VectorInput_Double(n)  ) ;
            // data.push_back( new VectorInput_String(n)  ) ;
        }
        
        void set( int i, const std::string& line ){
            fastread::Tokenizer tok(line);
            fastread::Tokenizer::const_iterator it = tok.begin() ;
            for( int j=0; j<ncol; j++, ++it){
                data[j]->set( i, *it ) ;
            }
        }   
        
        void read_file( const std::string& filename){
            std::string line ;
            std::ifstream file(filename.c_str());
            
            for( int i=0; i<n; i++){
                std::getline (file,line);
                set( i, line );
            }
            file.close();
        }
        
        ~DataReader(){
            // deleting the inputs
            for( int i=0; i<ncol; i++){
                delete data[i] ;    
            }
        }
        
        List get(){
            List out(ncol) ;
            for( int i=0; i<ncol; i++){
                out[i] = data[i]->get() ;    
            }
            return out ;
        }
        
    private:
        int n ;
        std::vector< VectorInput_Base* > data ;
        int ncol ;
    } ; 
    
}

// [[Rcpp::export]]
List read_csv(std::string file, int n ){
    fastread::DataReader reader( n ) ;
    reader.read_file( file ) ;
    return reader.get() ;
}

