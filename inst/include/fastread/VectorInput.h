#ifndef FASTREAD_VectorInput_H
#define FASTREAD_VectorInput_H

namespace fastread {

    template <typename Source>
    class VectorInput {
    public:
        VectorInput( Source& reader_) : reader(reader_) {}
        virtual ~VectorInput(){} ;
        
        virtual void set( int i ) = 0 ;
        
        virtual SEXP get() = 0;
        virtual bool skip() const { return false ; }
        virtual bool is_rownames() const { return false ; }
    
    protected:
        Source& reader ;
    } ;
    
    template <typename Source>
    class VectorInput_Integer : public VectorInput<Source> {
    public:
        typedef VectorInput<Source> Base ;
        
        VectorInput_Integer( int n, Source& reader_ ) : 
            Base(reader_), data( Rcpp::no_init(n) ) {}
        void set( int i ){
            data[i] = Base::reader.get_int() ;    
        }
        inline SEXP get(){ return data ; } 
        
    private:
        Rcpp::IntegerVector data ;
    } ;
    
    template <typename Source>
    class VectorInput_Factor : public VectorInput<Source> {
    public:
        typedef VectorInput<Source> Base ;
        
        VectorInput_Factor( int n, Source& reader_ ) : Base(reader_), 
            data( Rcpp::no_init(n) ), 
            level_map(), 
            max_level(0)
            {}
        
        // we store the values as integers, the first seen level is set
        // to 1, then 2, ...
        // and the values are reordered later when we know all the levels
        void set( int i){
            SEXP st = Base::reader.get_String() ;
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
        
        SEXP get() {
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
            
    private:
        Rcpp::IntegerVector data ;
        typedef boost::unordered_map<SEXP, int> MAP;  
        MAP level_map ;
        int max_level ;
    } ;
    
    template <typename Source>
    class VectorInput_Double : public VectorInput<Source> {
    public:
        typedef VectorInput<Source> Base ;
        
        VectorInput_Double( int n, Source& reader_ ) : 
            Base(reader_), data(Rcpp::no_init(n) ){}
        void set( int i ){
             data[i] = Base::reader.get_double() ;
        }
        inline SEXP get(){ return data ; } 
        
    private:
        Rcpp::DoubleVector data ;
    } ;
    
    template <typename Source>
    class VectorInput_String : public VectorInput<Source> {
    public:
        typedef VectorInput<Source> Base ;
        
        VectorInput_String( int n, Source& reader_ ) : 
            Base(reader_), data(Rcpp::no_init(n) ){}
        void set( int i ) {
            data[i] = Base::reader.get_String() ;
        }
        inline SEXP get(){ return data ; } 
        
    private:
        Rcpp::CharacterVector data ;
    } ;
    
    template <typename Source>
    class VectorInput_Rownames : public VectorInput_String<Source> {
    public:
        VectorInput_Rownames( int n, Source& reader_ ) : VectorInput_String<Source>(n, reader_){}
        bool is_rownames() const { return true ; }
    } ;
    
    template <typename Source>
    class VectorInput_Skip : public VectorInput<Source> {
    public:
        typedef VectorInput<Source> Base ;
        
        VectorInput_Skip( int, Source& reader_ ) : Base(reader_){}
        void set( int i ) {
            Base::reader.skip_token() ;
        }
        inline SEXP get(){ return R_NilValue ; } 
        virtual bool skip() const { return true ; }
    } ;
    
    template <typename Source>
    VectorInput<Source>* make_vector_input( int rtype, int n, Source& reader){
        switch( rtype ){
            case INTSXP:  return new VectorInput_Integer<Source>(n, reader) ;
            case REALSXP: return new VectorInput_Double<Source>(n, reader) ;
            case STRSXP:  return new VectorInput_String<Source>(n, reader) ;
            default:
                stop( "unsupported type" ) ;
        }
        return 0 ;    
    }
    
    template <typename Source>
    VectorInput<Source>* make_vector_input( const std::string& clazz, int n, Source& reader ){
        if( ( clazz == "int" )   || ( clazz == "I" ) || ( clazz == "integer"   ) ) return new VectorInput_Integer<Source>(n, reader) ;
        if( ( clazz == "double") || ( clazz == "D" ) || ( clazz == "numeric"   ) ) return new VectorInput_Double<Source>(n, reader) ;
        if( ( clazz == "string") || ( clazz == "S" ) || ( clazz == "character" ) ) return new VectorInput_String<Source>(n, reader) ;
        if( ( clazz == "names" ) || ( clazz == "row.names" ) || ( clazz == "rownames" ) ) return new VectorInput_Rownames<Source>( n, reader ) ; 
        if( ( clazz == "NULL"  ) || ( clazz == "_" )     || ( clazz == "skip" ) ) return new VectorInput_Skip<Source>(n, reader) ;
        if( ( clazz == "factor") ) return new VectorInput_Factor<Source>(n, reader) ;
        
        stop( "unsupported" ) ;
        return 0 ;
        
    }
    
}

#endif
