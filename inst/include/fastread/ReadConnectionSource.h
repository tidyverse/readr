#ifndef FASTREAD_ReadConnectionSource_H
#define FASTREAD_ReadConnectionSource_H

namespace fastread {
        
    class ReadConnectionSource : public Source<ReadConnectionSource>{
    public:
        typedef Source<ReadConnectionSource> Base ;
        
        enum Origin {
            START = 1, 
            CURRENT = 2, 
            END = 3
        } ;
        
        enum ReadWrite {
            READ = 1, 
            WRITE = 2
        } ;
        
        ReadConnectionSource(SEXP con_d, char sep = ',', char quote = '"', char esc = '\\') ;
        
        bool ensure_full_line(); 
        bool more() ;
        bool can_seek() const ;
        
        double byte_offset(Origin origin = START) const ;
        
        void seek(double pos, Origin origin = START) ;
        
    private:
        Rconnection con ;
        
        void find_last_line() ;
        
        int chunk_size ;
        std::vector<char> buffer ;
        char* data ;
        char* last_full_line ;
        int n ;
        
    } ;
}

#endif
