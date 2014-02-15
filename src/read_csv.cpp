#include <fastread.h>

using namespace Rcpp ;
using namespace fastread ;

// [[Rcpp::export]]
List read_csv_impl( SEXP input, CharacterVector classes, int n, bool header ){
    if( Rf_inherits( input, "connection" ) ){
        ReadConnectionSource<KeepAllLines> source(input);
        if( n <= 0 ){
            if( !source.can_seek() )
                stop("connection cannot seek") ;
            
            double pos = source.byte_offset() ;
            n = source.count_lines() ;
            if(header) n--;
            source.seek(pos) ;
        }
        DataReader< ReadConnectionSource<KeepAllLines> > reader(source) ;
        return reader.read( n, classes, header ) ;
    } else {
        std::string path = as<std::string>(input) ;
        MMapSource<KeepAllLines> source(path) ;
        if( n <= 0 ){
            n = source.count_lines() ;
            source.seek(0) ;
        }
        DataReader< MMapSource<KeepAllLines> > reader(source) ;
        return reader.read( n, classes, header ) ;
    }
}

// [[Rcpp::export]]
List read_csv_impl_filter_pattern( SEXP input, CharacterVector classes, int n, bool header, LogicalVector filter_pattern ){
    return read_csv_impl(input, classes, n, header ) ;
}

