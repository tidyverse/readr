#include <fastread.h>

using namespace Rcpp ;
using namespace fastread ;

// [[Rcpp::export]]
List read_csv(std::string file, int n, CharacterVector classes ){
    MMapReader mmap_reader(file) ;
    DataReader<MMapReader> data_reader(mmap_reader) ;
    return data_reader.read( n, classes ) ;
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

