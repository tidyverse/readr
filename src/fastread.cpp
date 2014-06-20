#include <fastread.h>

using namespace Rcpp ;
using namespace fastread ;

//' Read lines
//'
//' @param input Either a path to a file, or a \code{connection}.
//' @param n Number of lines to read. If \code{0}, all lines in the file
//'   will be read.
//' @export
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


//' Count the number of lines in a file.
//'
//' @param input Either a path to a file, or a \code{connection}.
//' @param header If \code{TRUE}, subtract one line to account for the
//'   header.
//' @export
// [[Rcpp::export]]
int count_lines(SEXP input){
    if( Rf_inherits(input, "connection" ) ){
        ReadConnectionSource<>  source(input);
        return source.count_lines() ;
    } else {
        std::string path = as<std::string>(input) ;
        MMapSource<>  source(path) ;
        return source.count_lines() ;
    }
}

// [[Rcpp::export]]
SEXP parse_text( CharacterVector x, List parser){
    CharacterVectorSource<> source(x) ;
    int n = x.size() ;
    VectorInput< CharacterVectorSource<> >* input =
        create_parser< CharacterVectorSource<> >(parser, n, source );

    for( int i=0; i<n; i++){
        source.more() ;
        input->set(i);
    }
    Shield<SEXP> out( input->get() ) ;
    delete input ;
    return out ;
}
