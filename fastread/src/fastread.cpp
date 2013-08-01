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

// [[Rcpp::export]]
double parseDouble_strtod( std::string file, int nd ){
    MMapReader reader( file ) ;
    return reader.parseDouble_strtod(nd) ;    
}

// [[Rcpp::export]]
double parseDouble_double_conversion( std::string file, int nd ){
    MMapReader reader( file ) ;
    return reader.parseDouble_double_conversion(nd) ;    
}

// [[Rcpp::export]]
double parseDouble_fast_atof( std::string file, int nd ){
    MMapReader reader( file ) ;
    return reader.parseDouble_fast_atof(nd) ;    
}
