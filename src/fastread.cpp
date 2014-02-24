#include <fastread.h>

using namespace Rcpp ;
using namespace fastread ;

// [[Rcpp::export]]
CharacterVector read_lines(SEXP input, int n = 0){ 
    if( Rf_inherits(input, "connection" ) ){
        ReadConnectionSource<>  source(input);
        LinesReader<ReadConnectionSource<> > reader(source) ;
        return reader.read(n) ;
    } else {
        std::string path = as<std::string>(input) ;
        MMapSource<> source(path) ;
        LinesReader< MMapSource<> > reader(source) ;
        return reader.read(n) ;
    }
}

// [[Rcpp::export]]
int count_lines(SEXP input, bool header = true){
    if( Rf_inherits(input, "connection" ) ){
        ReadConnectionSource<>  source(input);
        return source.count_lines(header) ;
    } else {
        std::string path = as<std::string>(input) ;
        MMapSource<>  source(path) ;
        return source.count_lines(header) ;
    }
}

// [[Rcpp::export]]
SEXP parse_text( CharacterVector x, std::string what){
    CharacterVectorSource<> source(x) ;
    int n = x.size() ;
    VectorInput< CharacterVectorSource<> >* input = 
        make_vector_input< CharacterVectorSource<> >(what, n, source );
    
    for( int i=0; i<n; i++){
        source.more() ;
        input->set(i);
    }
    Shield<SEXP> out( input->get() ) ;
    delete input ;
    return out ;
}

