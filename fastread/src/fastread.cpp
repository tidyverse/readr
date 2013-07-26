#include <Rcpp.h>
#include <boost/tokenizer.hpp>

// [[Rcpp::depends(BH)]]

using namespace Rcpp ;
using namespace boost ;

typedef boost::tokenizer< boost::escaped_list_separator<char> > Tokenizer ;
    
// [[Rcpp::export]]
CharacterVector tokenize(std::string s){
    Tokenizer tok(s);
    return CharacterVector( tok.begin(), tok.end() ) ;
}


/*** R
    tokenize( '123, "foo", 12.0' )
*/
