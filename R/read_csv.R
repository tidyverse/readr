read_csv <- function(input, classes, n = 0, header = TRUE, filter_pattern = NULL){
  
  if( is.null(filter_pattern) ){ 
    read_csv_impl( input, classes, n, header )  
  } else {
    assert_that( is.logical(filter_pattern) )
    read_csv_impl_filter_pattern( input, classes, n, header, filter_pattern )  
  }
  
}
