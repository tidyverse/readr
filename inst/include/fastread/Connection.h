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
  
#endif
