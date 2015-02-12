#ifndef FASTREAD_VectorInput_H
#define FASTREAD_VectorInput_H

namespace fastread {

    template <typename Source>
    class VectorInput {
    public:
        VectorInput( Source* source_) : source(source_) {}
        virtual ~VectorInput(){} ;

        virtual void set( int i ) = 0 ;
        virtual SEXP get() = 0;
        virtual bool skip() const { return false ; }

    protected:
        Source* source ;
    } ;

    template <typename Source>
    class VectorInput_Integer : public VectorInput<Source> {
    public:
        typedef VectorInput<Source> Base ;

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

        VectorInput_Factor( int n, Source* source_, CharacterVector levels_, bool ordered_ ) : Base(source_),
            data( no_init(n) ),
            levels(levels_),
            ordered(ordered_)
            {
              int m = levels.size();

              // Train unordered map with int
              level_map = boost::unordered_map<SEXP, int>();
              for (int i = 0; i < m; ++i) {
                SEXP level = levels[i];
                level_map[level] = i;
              }
            }

        void set( int i){
            SEXP st = Base::source->get_String() ;

            MAP::iterator it = level_map.find(st) ;
            if( it == level_map.end() ){
                stop("Value not in list of allowed levels");
            } else {
                data[i] = it->second + 1 ;
            }
        }

        SEXP get() {
            data.attr("levels") = levels ;
            if (ordered) {
              data.attr("class") = CharacterVector::create("ordered", "factor");
            } else {
              data.attr("class" ) = "factor";
            }

            return data ;
        }

    private:
        IntegerVector data ;
        CharacterVector levels;
        bool ordered;
        typedef boost::unordered_map<SEXP, int> MAP;
        MAP level_map ;
    } ;

    template <typename Source>
    class VectorInput_Double : public VectorInput<Source> {
    public:
        typedef VectorInput<Source> Base ;

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
        VectorInput_String( int n, Source* source_, bool trim_ ) :
            Base(source_),
            data(no_init(n)),
            trim(trim_)
            {

            }
        void set( int i ) {
            data[i] = Base::source->get_String() ;
        }
        inline SEXP get(){ return data ; }

    private:
        CharacterVector data ;
        bool trim;
    } ;

    template <typename Source>
    class VectorInput_Date_ymd : public VectorInput<Source>{
    public:
        typedef VectorInput<Source> Base ;

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
        VectorInput_Rownames( int n, Source* source_ ) : VectorInput_String<Source>(n, source_){}
        bool is_rownames() const { return true ; }
    } ;

    template <typename Source>
    class VectorInput_Skip : public VectorInput<Source> {
    public:
        typedef VectorInput<Source> Base ;

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
      if( clazz == "character" ) {
        bool trim = as<LogicalVector>(spec["trim"]);
        return new VectorInput_String<Source>(n, &source, trim) ;
      }
      if( clazz == "skip"      ) return new VectorInput_Skip<Source>(n, &source) ;
      if( clazz == "factor"    ) {
        CharacterVector levels = as<CharacterVector>(spec["levels"]);
        bool ordered = (as<LogicalVector>(spec["ordered"]))[0];
        return new VectorInput_Factor<Source>(n, &source, levels, ordered) ;
      }
      if( clazz == "Date"      ) return new VectorInput_Date_ymd<Source>(n, &source) ;
      if( clazz == "POSIXct"   ) return new VectorInput_POSIXct<Source>(n, &source) ;
      if( clazz == "Time"      ) return new VectorInput_Time<Source>(n, &source) ;
      stop( "unsupported column type" ) ;
      return 0 ;
    }

}

#endif
