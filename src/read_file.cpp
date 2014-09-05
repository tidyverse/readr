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
    //TODO catch error if mapping fails...
    file_mapping fm(path.c_str(), read_only);
    mr = new mapped_region(fm, read_only);

    size = mr->get_size();
    data = static_cast<char*>(mr->get_address());
  }

  String get(){
    return Rf_mkCharLen(data, size) ;
  }

  ~FileRead(){
    mr->flush();
    delete mr;
  }

private:

  // prevent copy
  FileRead( const FileRead& ) ;
  FileRead& operator=(const FileRead& ) ;

  char* data ;
  int size ;
  mapped_region* mr;
} ;

//' Read file in a single string
//'
//' @param path file path name
//' @export
// [[Rcpp::export]]
String read_file( const std::string& path ){
  return FileRead(path).get() ;
}
