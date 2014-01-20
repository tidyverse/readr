#include <fastread.h>

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
    
    // we store the values as integers, the first seen level is set
    // to 1, then 2, ...
    // and the values are reordered later when we know all the levels
    inline void VectorInput_Factor::set(int i){
        SEXP st = reader.get_String() ;
        // search for this strings as a key in the hash map
        MAP::iterator it = level_map.find(st) ;
        if( it == level_map.end() ){
            // not yet in the map, so increment the max_level and use it
            data[i] = ++max_level ;
            level_map[st] = max_level ;
        } else {
            // already on the map, just use the value for that key
            data[i] = it->second ;
        }
    }
    
    SEXP VectorInput_Factor::get(){
        // we now need to put the values in the correct order
        // as read.table does, so we first copy the hash map into 
        // a regular map so that data are sorted by keys
        std::map< std::string, int > sorted ;
        std::string buffer ;
        for( MAP::iterator it = level_map.begin(); it != level_map.end(); ++it){
            buffer = as<std::string>( it->first ) ;
            sorted[ buffer ] = it->second ;
        }
        int nlevels = sorted.size() ;
        // we then grab the keys of the sorted map. Those are the level names
        // and make a vector of codes, giving the real factor values for each 
        // value that was set while reading the data
        std::vector<int> code( nlevels ) ;
        std::map< std::string, int >::iterator sorted_it = sorted.begin() ;
        CharacterVector levels( nlevels ); 
        for( int i=0; i<nlevels; i++, ++sorted_it){
            code[ sorted_it->second ] = i + 1 ;
            levels[ i ] = sorted_it->first ;
        }
        // recode 
        int n = data.size() ;
        for( int i=0; i<n; i++){
            data[i] = code[ data[i] ] ;    
        }
        
        data.attr("levels") = levels ;
        data.attr("class" ) = "factor" ;
        
        return data ;
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
        if( ( clazz == "names" ) || ( clazz == "row.names" ) || ( clazz == "rownames" ) ) return new VectorInput_Rownames( n, reader ) ; 
        if( ( clazz == "NULL"  ) || ( clazz == "_" )     || ( clazz == "skip" ) ) return new VectorInput_Skip(n, reader) ;
        if( ( clazz == "factor") ) return new VectorInput_Factor(n, reader) ;
        stop( "unsupported" ) ;
        return 0 ;
    }
    
}

