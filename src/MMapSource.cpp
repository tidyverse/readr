#include <fastread.h>
    
namespace fastread{

    MMapSource::MMapSource( const std::string& filename, char sep, char quote, char esc) :
                Base(sep, quote, esc), file_descriptor( open(filename.c_str(), O_RDONLY) )
    {
        struct stat file_info;
        if (fstat(file_descriptor,&file_info) == -1) {
            stop( "cannot read file information" ) ;
        }
        filesize = file_info.st_size ;
        memory_start = (char *)mmap(NULL, filesize, PROT_READ, MAP_PRIVATE, file_descriptor, 0);
        eof = memory_start + filesize ;
        Base::set(memory_start, eof);
        
        last_full_line = eof - 1 ;
        while( *last_full_line != '\n' ) --last_full_line;
    
    } 

}
