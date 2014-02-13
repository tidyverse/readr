#ifndef FASTREAD_DataReader_H
#define FASTREAD_DataReader_H

namespace fastread {
    
    template <typename Source>
    class DataReader {
    public:     
        typedef VectorInput<Source> Input ;
           
        DataReader( Source& source_ ) : source(source_){} 
        
        List read( int n, CharacterVector classes, bool header ){
            std::vector<Input*> inputs ;
            
            int ncol = classes.size() ;
            int ncolumns = 0 ;   
            
            for( int i=0; i<ncol; i++){
                String cl = classes[i] ;
                inputs.push_back( make_vector_input<Source>(cl, n, source ) ) ;
                if( !inputs[i]->is_rownames() && ! inputs[i]->skip() ) ncolumns++ ;
            }
            
            CharacterVector names(ncolumns) ;
            if( header ){
                source.ensure_full_line() ;
                for( int i=0; i<ncolumns; i++){
                    names[i] = source.get_String() ;   
                }
            } else {
                for( int i=0; i<ncolumns; i++){
                    String V("V") ; V += (i+1) ;
                    names[i] = V ;
                }   
            }
            for( int i=0; i<n; i++) {
                source.ensure_full_line() ;
                for( int j=0; j<ncol; j++){
                    inputs[j]->set(i) ;
                }
            }
                  
            std::vector<Input*> columns(ncolumns) ;
            Input* row_names = 0 ;
            
            for( int i=0, k=0; i<ncol; i++){
                if( inputs[i]->skip() ) continue ;
                if( inputs[i]->is_rownames() ){
                    row_names = inputs[i] ; 
                    continue ;    
                }
                columns[k++] = inputs[i];
            }
            List out(ncolumns) ;
            
            for( int i=0; i<ncolumns; i++){
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
