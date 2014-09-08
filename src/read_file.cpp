#include <fastread.h>

#include <fstream>
#include <sstream>
#include <boost/interprocess/file_mapping.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <fcntl.h>

using namespace Rcpp ;
using namespace boost::interprocess;

class FileRead {
public:
  FileRead( const std::string& path ) {
    try{
      file_mapping fm(path.c_str(), read_only);
      mr.reset(new mapped_region(fm, read_only));
    }
    catch(interprocess_exception& e){
      stop("could not read file");
    }

    size = mr->get_size();
    data = static_cast<char*>(mr->get_address());
  }

  String get(){
    return Rf_mkCharLen(data, size) ;
  }

private:

  // prevent copy
  FileRead( const FileRead& ) ;
  FileRead& operator=(const FileRead& ) ;

  char* data ;
  int size ;
  std::auto_ptr<mapped_region> mr;
} ;

//' Read file in a single string
//'
//' @param path file path name
//' @export
// [[Rcpp::export]]
String read_file( const std::string& path ){
  return FileRead(path).get() ;
}
