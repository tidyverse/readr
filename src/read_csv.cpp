#include <fastread.h>

using namespace Rcpp ;
using namespace fastread ;

// [[Rcpp::export]]
List read_csv_impl( SEXP input, CharacterVector classes, int n, bool header ){
    if( Rf_inherits( input, "connection" ) ){
        typedef ReadConnectionSource<KeepAllLines> DataSource ;
        DataSource source( input ) ;
        return DataReader<DataSource>(source).read( n, classes, header ) ;
    } else {
        typedef MMapSource<KeepAllLines> DataSource ; 
        std::string path = as<std::string>(input) ;
        DataSource source(path) ;
        return DataReader<DataSource>(source).read( n, classes, header) ;
    }
}

// [[Rcpp::export]]
List read_csv_impl_filter_pattern( SEXP input, CharacterVector classes, int n, bool header, LogicalVector filter_pattern ){
    if( Rf_inherits( input, "connection" ) ){
        typedef ReadConnectionSource<FilterRecylerLines> DataSource ;
        DataSource source( input, filter_pattern ) ;
        return DataReader<DataSource>(source).read( n, classes, header ) ;
    } else {
        typedef MMapSource<FilterRecylerLines> DataSource ; 
        std::string path = as<std::string>(input) ;
        DataSource source(path, filter_pattern) ;
        return DataReader<DataSource>(source).read( n, classes, header) ;
    }
}

