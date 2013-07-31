#include "fastread.h"

using namespace Rcpp ;
using namespace fastread ;

// [[Rcpp::export]]
List read_csv(std::string file, int n, CharacterVector classes ){
    MMapReader reader( file ) ;
    reader.read( n, classes ) ;
    return reader.get() ;
}

// [[Rcpp::export]]
List allocate_vectors(std::string file, int n, CharacterVector classes ){
    MMapReader reader( file ) ;
    reader.setup( n, classes ) ;
    return reader.get() ;
}

// [[Rcpp::export]]
int count_lines(std::string file ){
    MMapReader reader( file ) ;
    return reader.count_lines() ;
}

