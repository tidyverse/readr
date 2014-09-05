#include <fastread.h>

#include <fstream>
#include <sstream>
#include <boost/interprocess/file_mapping.hpp>
#include <boost/interprocess/mapped_region.hpp>
//#include <sys/mman.h>
//#include <sys/stat.h>
#include <fcntl.h>

using namespace Rcpp ;
using namespace boost::interprocess ;

class FileRead {
public:
  FileRead( const std::string& path ) {
    //TODO catch error if mapping fails...
    fm = &file_mapping(path, read_only);
    mr = &mapped_region(fm);

    size = mr->get_size();
    data = mr->get_address();
  }

  String get(){
    return Rf_mkCharLen(data, size) ;
  }

  ~FileRead(){
    munmap(data, size);
    close(fd);
  }

private:

  // prevent copy
  FileRead( const FileRead& ) ;
  FileRead& operator=(const FileRead& ) ;

  char* data ;
  int size ;
  file_mapping* fm;
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
