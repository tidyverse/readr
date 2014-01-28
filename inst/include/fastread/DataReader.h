#ifndef FASTREAD_DataReader_H
#define FASTREAD_DataReader_H

namespace fastread {
    
    template <typename Source>
    class DataReader {
    public:     
        typedef VectorInput<MMapReader> Input ;
           
        DataReader( Source& source_ ) : source(source_){} 
        
        List read( int n, CharacterVector classes ){
            if( n <= 0 ) stop( "not handling yet" ) ;
            std::vector<Input*> inputs ;
            
            int ncol = classes.size() ;
            for( int i=0; i<ncol; i++){
                String cl = classes[i] ;
                inputs.push_back( make_vector_input<Source>(cl, n, source ) ) ;   
            }
            ncol = inputs.size() ;
            for( int i=0; i<n; i++) {
                for( int j=0; j<ncol; j++){
                    inputs[j]->set(i) ;
                }
            }
                  
            std::vector<Input*> columns ; columns.reserve(ncol) ;
            int ncolumns = 0 ;   
            Input* row_names = 0 ;
            
            for( int i=0; i<ncol; i++){
                if( inputs[i]->skip() ) continue ;
                if( inputs[i]->is_rownames() ){
                    row_names = inputs[i] ; 
                    continue ;    
                }
                columns.push_back( inputs[i] ) ; ncolumns++ ;
            }
            
            List out(ncolumns) ;
            // automatic names for now
            // TODO: handle names in header line
            CharacterVector names(ncolumns) ;
            
            for( int i=0; i<ncolumns; i++){
                String V("V") ; V += (i+1) ;
            
                names[i] = V ;
                out[i] = columns[i]->get() ;    
            }
            out.attr( "class" ) = "data.frame" ;
            out.attr( "names" ) = names ;
            if( row_names ){
                out.attr( "row.names" ) = row_names->get() ;   
            } else {
                out.attr( "row.names") = IntegerVector::create( NA_INTEGER, -n) ;
            }
            
            for( int i=0; i<inputs.size(); i++) {
                delete inputs[i] ;
            }
            
            return out ;
        }
        
    private:
        Source& source ;
        
    } ;
    
}

#endif
