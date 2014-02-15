#include <fastread.h>

using namespace Rcpp ;
using namespace fastread ;

class MultipleConnectionReader {
public:
    typedef VectorInput< ReadConnectionSource<KeepAllLines> > Input ;
    
    MultipleConnectionReader( CharacterVector classes_, IntegerVector nlines_, bool header_ ) : 
        classes(classes_), nlines(nlines_), header(header_) 
    {
        ncol = classes.size() ;
        ncolumns = 0 ;
        nrows = nlines[ nlines.size()-1 ] ;
        row_names = 0 ;
        
        for( int i=0; i<ncol; i++){
            String cl = classes[i] ;
            inputs.push_back( make_vector_input<ReadConnectionSource<KeepAllLines> >(cl, nrows ) ) ;
            if( !inputs[i]->is_rownames() && ! inputs[i]->skip() ) {
                ncolumns++ ;
                columns.push_back(inputs[i]) ;
            }
            if( inputs[i]->is_rownames() ){
                row_names = inputs[i] ;    
            }
        }
        
        names = CharacterVector(ncolumns) ;
        if( !header ){
            for( int i=0; i<ncolumns; i++){
                String V("V") ; V += (i+1) ;
                names[i] = V ;
            }         
        }
        
    }                                          

    ~MultipleConnectionReader(){
        for( int i=0; i<inputs.size(); i++){
            delete inputs[i] ;    
        }
        inputs.clear() ;
    }
       
    void process(SEXP con, int index){
        ReadConnectionSource<KeepAllLines> source(con) ; 
        if( header ){
            if( index == 1 ){
                // read header line
                source.ensure_full_line() ;
                for( int i=0; i<ncolumns; i++){
                    names[i] = source.get_String() ;   
                }
            } else {
                // skip header line
                source.skip_line() ;
            }
        }
        
        for( int i=0; i<ncol; i++){
            inputs[i]->set_source(source) ;    
        }
        
        // read the data
        int start ; 
        if( index == 1 ){
            start = 0 ;
        } else {
            start = nlines[index-2]-1;    
        }
        int end = nlines[index-1]-1 ;
        
        for( int i=start; i<end; i++) {
            source.ensure_full_line() ;
            for( int j=0; j<ncol; j++){
                inputs[j]->set(i) ;
            }
        }
        
    }
    
    SEXP get(){
        List out(ncolumns) ;
           
        for( int i=0; i<ncolumns; i++){
            out[i] = columns[i]->get() ;
        }
            
        out.attr( "class" ) = "data.frame" ;
        out.attr( "names" ) = names ;
        if( row_names ){
            out.attr( "row.names" ) = row_names->get() ;   
        } else {
            out.attr( "row.names") = IntegerVector::create( NA_INTEGER, -nrows) ;
        }
            
        return out ;
    }

private:
    CharacterVector classes ;
    IntegerVector nlines ;
    bool header ;  
    Input* row_names ;
    std::vector<Input*> inputs ;
    std::vector<Input*> columns ;
    
    int ncol ;
    int ncolumns ;
    int nrows ;
    CharacterVector names ;
     
} ;

RCPP_MODULE(MultipleConnectionReader){
    class_<MultipleConnectionReader>("MultipleConnectionReader")
        .constructor<CharacterVector,IntegerVector,bool>()
        .method("process", &MultipleConnectionReader::process)
        .method("get", &MultipleConnectionReader::get)
    ;
}
