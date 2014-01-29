#ifndef FASTREAD_MMapSource_H
#define FASTREAD_MMapSource_H

namespace fastread {
        
    class MMapSource : public Source<MMapSource>{
    public:
        typedef Source<MMapSource> Base ;
        
        MMapSource( const std::string& filename, char sep = ',', char quote = '"', char esc = '\\' )  ;
        
        inline bool more(){ return false ;}
        
        // no-op as we always have the full data mmapped
        inline void ensure_full_line(){}
        
    private:
        int file_descriptor ;
        size_t filesize ;
        char* memory_start ;
        char* eof ;
    } ;
}

#endif
