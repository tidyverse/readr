#include <fastread.h>

using namespace Rcpp ;
using namespace fastread ;

// [[Rcpp::export]]
List read_csv( SEXP input, int n, CharacterVector classes ){
    if( Rf_inherits( input, "connection" ) ){
        ReadConnection con_reader( as<int>(input) );
        DataReader<ReadConnection> data_reader(con_reader) ;
        return data_reader.read( n, classes ) ;
    } else {
        std::string path = as<std::string>(input) ;
        MMapReader mmap_reader(path) ;
        DataReader<MMapReader> data_reader(mmap_reader) ;
        return data_reader.read( n, classes ) ;
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

