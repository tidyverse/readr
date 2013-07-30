#include "fastread.h"

using namespace Rcpp ;

namespace fastread{
    
    inline void VectorInput_Integer::set( int i){
        data[i] = reader.get_int() ;
    }
           
    inline void VectorInput_Double::set( int i ){
        data[i] = reader.get_double() ;
    }
    
    inline void VectorInput_String::set( int i ){
        data[i] = reader.get_String() ;
    }
    
    inline void VectorInput_Skip::set( int i){
        reader.move_until_next_token_start() ;
    }
    
    VectorInput* make_vector_input( int rtype, int n, MMapReader& reader ){
        switch( rtype ){
            case INTSXP:  return new VectorInput_Integer(n, reader) ;
            case REALSXP: return new VectorInput_Double(n, reader) ;
            case STRSXP:  return new VectorInput_String(n, reader) ;
            default:
                stop( "unsupported type" ) ;
        }
        return 0 ;
    }
    
    VectorInput* make_vector_input( const std::string& clazz, int n, MMapReader& reader ){
        if( ( clazz == "int" )   || ( clazz == "I" ) || ( clazz == "integer"   ) ) return new VectorInput_Integer(n, reader) ;
        if( ( clazz == "double") || ( clazz == "D" ) || ( clazz == "numeric"   ) ) return new VectorInput_Double(n, reader) ;
        if( ( clazz == "string") || ( clazz == "S" ) || ( clazz == "character" ) ) return new VectorInput_String(n, reader) ;
        if( ( clazz == "_" )     || ( clazz == "skip" ) ) return new VectorInput_Skip(n, reader) ;
        stop( "unsupported" ) ;
        return 0 ;
    }
    
}

