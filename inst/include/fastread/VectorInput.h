#ifndef FASTREAD_VectorInput_H
#define FASTREAD_VectorInput_H

namespace fastread {

    template <typename Source>
    class VectorInput {
    public:
        VectorInput() : source(0) {}
        VectorInput( Source* source_) : source(source_) {}
        virtual ~VectorInput(){} ;

        virtual void set( int i ) = 0 ;

        virtual SEXP get() = 0;
        virtual bool skip() const { return false ; }
        virtual bool is_rownames() const { return false ; }

        void set_source(Source& source_){
            source = &source_ ;
        }

    protected:
        Source* source ;
    } ;

    template <typename Source>
    class VectorInput_Integer : public VectorInput<Source> {
    public:
        typedef VectorInput<Source> Base ;

        VectorInput_Integer( int n ) : Base(), data(no_init(n)){}

        VectorInput_Integer( int n, Source* source_ ) :
            Base(source_), data( no_init(n) ) {}
        void set( int i ){
            data[i] = Base::source->get_int() ;
        }
        inline SEXP get(){ return data ; }

    private:
        IntegerVector data ;
    } ;

    template <typename Source>
    class VectorInput_Factor : public VectorInput<Source> {
    public:
        typedef VectorInput<Source> Base ;

        VectorInput_Factor(int n ) : Base(),
            data(no_init(n)),
            level_map(),
            max_level(0)
            {}

        VectorInput_Factor( int n, Source* source_ ) : Base(source_),
            data( no_init(n) ),
            level_map(),
            max_level(0)
            {}

        // we store the values as integers, the first seen level is set
        // to 1, then 2, ...
        // and the values are reordered later when we know all the levels
        void set( int i){
            SEXP st = Base::source->get_String() ;
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
        IntegerVector data ;
        typedef boost::unordered_map<SEXP, int> MAP;
        MAP level_map ;
        int max_level ;
    } ;

    template <typename Source>
    class VectorInput_Double : public VectorInput<Source> {
    public:
        typedef VectorInput<Source> Base ;

        VectorInput_Double( int n) : Base(), data(no_init(n)){}
        VectorInput_Double( int n, Source* source_ ) :
            Base(source_), data(no_init(n) ){}
        void set( int i ){
             data[i] = Base::source->get_double() ;
        }
        inline SEXP get(){ return data ; }

    private:
        DoubleVector data ;
    } ;

    template <typename Source>
    class VectorInput_String : public VectorInput<Source> {
    public:
        typedef VectorInput<Source> Base ;
        VectorInput_String( int n) : Base(), data(no_init(n)){}
        VectorInput_String( int n, Source* source_ ) :
            Base(source_), data(no_init(n) ){}
        void set( int i ) {
            data[i] = Base::source->get_String() ;
        }
        inline SEXP get(){ return data ; }

    private:
        CharacterVector data ;
    } ;

    template <typename Source>
    class VectorInput_Date_ymd : public VectorInput<Source>{
    public:
        typedef VectorInput<Source> Base ;

        VectorInput_Date_ymd( int n ) : Base(), data(no_init(n)){}
        VectorInput_Date_ymd( int n, Source* source_ ) :
            Base(source_), data(no_init(n)){}

        void set(int i){
            data[i] = Base::source->get_Date_Ymd() ;
        }
        inline SEXP get(){
            data.attr("class") = "Date" ;
            return data ;
        }

    private:
        NumericVector data ;
    } ;

    template <typename Source>
    class VectorInput_POSIXct : public VectorInput<Source>{
    public:
        typedef VectorInput<Source> Base ;

        VectorInput_POSIXct( int n ) : Base(), data(no_init(n)){}
        VectorInput_POSIXct( int n, Source* source_ ) :
            Base(source_), data(no_init(n)){}

        void set(int i){
            data[i] = Base::source->get_POSIXct() ;
        }
        inline SEXP get(){
            data.attr("class") = CharacterVector::create( "POSIXct", "POSIXt" ) ;
            return data ;
        }

    private:
        NumericVector data ;
    } ;

    template <typename Source>
    class VectorInput_Time : public VectorInput<Source>{
    public:
        typedef VectorInput<Source> Base ;

        VectorInput_Time( int n ) : Base(), data(no_init(n)){}
        VectorInput_Time( int n, Source* source_ ) :
            Base(source_), data(no_init(n)){}

        void set(int i){
            data[i] = Base::source->get_Time() ;
        }
        inline SEXP get(){
            data.attr("class") = "Time" ;
            return data ;
        }

    private:
        NumericVector data ;
    } ;


    template <typename Source>
    class VectorInput_Rownames : public VectorInput_String<Source> {
    public:
        VectorInput_Rownames( int n ) : VectorInput_String<Source>(n){}
        VectorInput_Rownames( int n, Source* source_ ) : VectorInput_String<Source>(n, source_){}
        bool is_rownames() const { return true ; }
    } ;

    template <typename Source>
    class VectorInput_Skip : public VectorInput<Source> {
    public:
        typedef VectorInput<Source> Base ;

        VectorInput_Skip( int ) : Base(){} ;
        VectorInput_Skip( int, Source* source_ ) : Base(source_){}
        void set( int i ) {
            Base::source->skip() ;
        }
        inline SEXP get(){ return R_NilValue ; }
        virtual bool skip() const { return true ; }
    } ;

    template <typename Source>
    VectorInput<Source>* create_parser(List spec, int n, Source& source){
      String clazz = (as<CharacterVector>(spec["type"]))[0];

      if( clazz == "integer"   ) return new VectorInput_Integer<Source>(n, &source) ;
      if( clazz == "double"    ) return new VectorInput_Double<Source>(n, &source) ;
      if( clazz == "character" ) return new VectorInput_String<Source>(n, &source) ;
      if( clazz == "skip"      ) return new VectorInput_Skip<Source>(n, &source) ;
      if( clazz == "factor"    ) return new VectorInput_Factor<Source>(n, &source) ;
      if( clazz == "Date"      ) return new VectorInput_Date_ymd<Source>(n, &source) ;
      if( clazz == "POSIXct"   ) return new VectorInput_POSIXct<Source>(n, &source) ;
      if( clazz == "Time"      ) return new VectorInput_Time<Source>(n, &source) ;
      stop( "unsupported column type" ) ;
      return 0 ;
    }

}

#endif
