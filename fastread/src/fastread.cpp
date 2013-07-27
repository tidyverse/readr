#include "fastread.h"

using namespace Rcpp ;
using namespace fastread ;

// [[Rcpp::export]]
List read_csv(std::string file, int n ){
    MMapReader reader( file ) ;
    reader.read( n) ;
    return reader.get() ;
}

// [[Rcpp::export]]
void read_all_lines_ifstream(std::string filename, int n){
  std::string line;
  std::ifstream myfile(filename.c_str());
  for( int i=0; i<n; i++){
      getline( myfile, line );    
  }
}

// [[Rcpp::export]]
void read_all_lines_FILE(std::string filename){
    FILE* file = fopen( filename.c_str(), "r" ) ;
    char next ;
    while( ( next = fgetc(file) ) != EOF ) ;
    fclose(file);
}

// // [[Rcpp::export]]
// SEXP scan_( std::string filename, int n, SEXP what ){
//     ScanInput input( TYPEOF(what), n) ;
//     MMapReader reader(filename) ;
//     for( int i=0; i<n; i++){
//         if( reader.is_finished() ) break ;
//         input.set( i, reader.get_token() ) ;
//     }
//     return input.get() ;
// }

