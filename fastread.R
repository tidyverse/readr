require(methods)
require(devtools)
require(data.table)
load_all( "fastread" )

make_zeros <- function( file = "zeros.csv", nc = 50, nr = 1e6 ){
    d <- matrix( sample( c(0L, 1L), nc * nr, replace = TRUE ), ncol = nc )
    write.table( d , file, row.names = FALSE, col.names = FALSE, sep = "," )    
}

make_matrix <- function( file = "matrix.csv", nc = 10, nr = 1e6 ){
    d <- matrix( rnorm(nc*nr), ncol = nc )
    write.table( d , file, row.names = FALSE, col.names = FALSE, sep = "," )    
}
n <- 1e6

require( microbenchmark )

options( width = 150 )
microbenchmark(     
    read_csv( 'zeros.csv', n, rep( "int", 50 ) ), 
    count_lines( 'zeros.csv' ),  
    allocate_vectors( 'zeros.csv', n, rep( "int", 50 ) ), # counting just allocating the data 
    # read.csv( 'zeros.csv', sep = ",", 
    #     header = FALSE, stringsAsFactors = FALSE, nrows = n,
    #     colClasses = rep( "integer", 50 ) ), 
    fread( 'zeros.csv', sep = ",", header = FALSE, stringsAsFactors = FALSE, nrows = n ), 
    times = 10L 
)

microbenchmark(     
    read_csv( 'matrix.csv', n, rep( "double", 10 ) ), 
    count_lines( 'matrix.csv' ), 
    allocate_vectors( 'matrix.csv', n, rep( "double", 10 ) ), # counting just allocating the data 
    # read.csv( 'zeros.csv', sep = ",", 
    #     header = FALSE, stringsAsFactors = FALSE, nrows = n,
    #     colClasses = rep( "integer", 50 ) ), 
    fread( 'matrix.csv', sep = ",", header = FALSE, stringsAsFactors = FALSE, nrows = n ), 
    times = 10L 
)

q("no")

microbenchmark(     
    read_csv( 'matrix.csv', n, rep( "double", 10 ) ), 
    # read.csv( 'matrix.csv', sep = ",", 
    #     header = FALSE, stringsAsFactors = FALSE, nrows = n,
    #     colClasses = rep( "numeric", 10 ) ), 
    fread( 'matrix.csv', sep = ",", header = FALSE, stringsAsFactors = FALSE, nrows = n ), 
    times = 10L 
)

