#' read from multiple compatible csv files
#' @export
read_csv_all <- function(files, classes, header = TRUE){
  
  nlines <- cumsum(sapply(files, function(file){
    con <- file(file, open = "r")
    on.exit(close(con))
    count_lines(con) - header
  }))
  
  reader <- new( MultipleConnectionReader, classes, nlines, header)
  
  for( i in seq_along(files)){
    con <- file( files[i], open = "r" )
    reader$process(con, i)
    close(con)
  }
  reader$get()
}
