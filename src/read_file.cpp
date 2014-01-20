#include <fastread.h>

#include <fstream>
#include <sstream>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

using namespace Rcpp ;

class FileRead {
public:
  FileRead( const std::string& path ){
    struct stat file_info;
    
    fd = open( path.c_str() , O_RDONLY );
    if (fstat(fd, &file_info) == -1) {
      stop("Could not read file information.");
    }
    
    size = file_info.st_size;
    data = (char*) mmap(0, size, PROT_READ, MAP_SHARED, fd, 0);
    
    if (data == MAP_FAILED) {
      close(fd);
      stop("Error mapping the file.");
    }
  
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
  int fd ;
} ;

//' Read file in a single string
//' 
//' @param path file path name
//' @export
// [[Rcpp::export]]
String read_file( const std::string& path ){
  return FileRead(path).get() ;
}
