#ifndef FASTREAD_Connection_H
#define FASTREAD_Connection_H

#define class class_name
#define private private_ptr
#include <R_ext/Connections.h>
#undef class
#undef private
#define R_EOF	-1
 
extern "C" {
    extern Rconnection getConnection(int) ;
    extern int Rconn_fgetc(Rconnection con);
}

namespace fastread {
    
    class ReadConnection {
    public:
        ReadConnection(int con_id) : 
            con(getConnection(con_id)), chunk_size(1000), buffer(chunk_size), data(&buffer[0]) 
        {
        }
        
        int read_chunk(){
            size_t res = con->read( data, 1, chunk_size, con ) ;
            return res ;
        }
        
        // inspired from Rconn_getline (connections.c)
        int readline(){
            int c, nbuf = -1;
            while((c = Rconn_fgetc(con)) != R_EOF) {
                if(nbuf+1 >= chunk_size) resize() ;
                if(c != '\n'){
                    data[++nbuf] = (char) c;
                } else {
                    data[++nbuf] = '\0';
                    break;
                }
            }
            if(nbuf >= 0 && data[nbuf]) {
                if(nbuf+1 >= chunk_size) resize(); 
                data[++nbuf] = '\0';
            }
            return(nbuf);                
        }
        
        inline char* get_data(){ return data ; }
        
    private:       
        
        void resize(){
            chunk_size *= 2 ;
            buffer.resize(chunk_size, '\0' );
            data = &buffer[0] ;
        }
        
        Rconnection con ;
        
        int chunk_size ;
        std::vector<char> buffer ;
        char* data ;
    };

}
  
#endif
