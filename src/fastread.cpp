#include <fastread.h>

using namespace Rcpp ;
using namespace fastread ;

// [[Rcpp::export]]
List read_csv( SEXP input, int n, CharacterVector classes ){
    METRONOME_RESET
    if( Rf_inherits( input, "connection" ) ){
        ReadConnectionSource source(input);
        DataReader<ReadConnectionSource> reader(source) ;
        return reader.read( n, classes ) ;
    } else {
        std::string path = as<std::string>(input) ;
        MMapSource source(path) ;
        DataReader<MMapSource> reader(source) ;
        return reader.read( n, classes ) ;
    }
}

// [[Rcpp::export]]
CharacterVector read_lines(SEXP input, int n = 0){ 
    if( Rf_inherits(input, "connection" ) ){
        ReadConnectionSource source(input);
        LinesReader<ReadConnectionSource> reader(source) ;
        return reader.read(n) ;
    } else {
        std::string path = as<std::string>(input) ;
        MMapSource source(path) ;
        LinesReader<MMapSource> reader(source) ;
        return reader.read(n) ;
    }
}

// [[Rcpp::export]]
int count_lines(SEXP input){
    if( Rf_inherits(input, "connection" ) ){
        ReadConnectionSource source(input);
        return source.count_lines() ;
    } else {
        std::string path = as<std::string>(input) ;
        MMapSource source(path) ;
        return source.count_lines() ;
    }
}

// [[Rcpp::export]]
SEXP scan_text( CharacterVector x, std::string what){
    CharacterVectorSource source(x) ;
    int n = x.size() ;
    VectorInput<CharacterVectorSource>* input = 
        make_vector_input<CharacterVectorSource>(what, n, source );
    
    for( int i=0; i<n; i++){
        source.more() ;
        input->set(i);
    }
    Shield<SEXP> out( input->get() ) ;
    delete input ;
    return out ;
}

