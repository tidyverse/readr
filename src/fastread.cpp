#include <fastread.h>

using namespace Rcpp ;
using namespace fastread ;

// [[Rcpp::export]]
List read_csv( SEXP input, int n, CharacterVector classes ){
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
int count_lines(std::string file){
    MMapReader reader( file ) ;
    return reader.count_lines() ;
}

// [[Rcpp::export]]
CharacterVector read_lines(std::string file, int n = 0){
    MMapReader reader( file ) ;
    return reader.read_lines(n) ;
}

