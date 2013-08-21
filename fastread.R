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

make_factors <- function( file = "factors.csv", nc = 10, nr = 1e6 ){
    d <- matrix( sample(LETTERS, nc*nr, replace = TRUE), ncol = nc )
    write.table( d , file, row.names = FALSE, col.names = FALSE, sep = ",", quote = FALSE )    
}

make_integer_matrix <- function( file = "integers.csv", nc = 10, nr = 1e6 ){
    min <- as.integer( -2^31+1 )
    max <- as.integer( 2^31 -1)
    d <- matrix( as.integer( round( runif( nc * nr,  min, max ) ) ), ncol = nc )
    write.table( d , file, row.names = FALSE, col.names = FALSE, sep = "," )    
}

n <- 1e6

require( microbenchmark )

options( width = 150 )

# d1 <- read_csv( 'matrix.csv', n, rep( "double", 10 ) )
# d2 <- fread( 'matrix.csv', sep = ",", header = FALSE, stringsAsFactors = FALSE, nrows = n )
# d3 <- read.csv( 'matrix.csv', sep = ",", 
#          header = FALSE, stringsAsFactors = FALSE, nrows = n,
#          colClasses = rep( "numeric", 10 ) )
# stopifnot( all.equal( d1, d3 ) )
#          
# microbenchmark(     
#     read_csv( 'matrix.csv', n, rep( "double", 10 ) ), 
#     # read.csv( 'matrix.csv', sep = ",", 
#     #     header = FALSE, stringsAsFactors = FALSE, nrows = n,
#     #     colClasses = rep( "numeric", 10 ) ), 
#     fread( 'matrix.csv', sep = ",", header = FALSE, stringsAsFactors = FALSE, nrows = n ), 
#     times = 10L 
# )
# 

# microbenchmark(     
#     read_csv( 'integers.csv', n, rep( "int", 10 ) ), 
#     # read.csv( 'integers.csv', sep = ",", 
#     #     header = FALSE, stringsAsFactors = FALSE, nrows = n,
#     #     colClasses = rep( "numeric", 10 ) ), 
#     fread( 'integers.csv', sep = ",", header = FALSE, stringsAsFactors = FALSE, nrows = n ), 
#     times = 10L 
# )
# d1 <- read_csv( 'integers.csv', n, rep( "int", 10 ) )
# d2 <- read.csv( 'integers.csv', sep = ",", 
#          header = FALSE, stringsAsFactors = FALSE, nrows = n,
#          colClasses = rep( "integer", 10 ) )
# all.equal( d1, d2 )
#         

# f <- read_csv( 'factors.csv', n, rep( "factor", 10 ) )
# d <- read.csv( "factors.csv", header = FALSE )
# e <- fread( "factors.csv", stringsAsFactors = TRUE, sep = ",", header = FALSE, nrows = n )

# the stringsAsFactors argument of fread does not work, so we create the 
# factors afterwards using data.table "by reference" syntax
fread_factors <- function( ... ){
    res <- fread(...)
    res[ , V1  := as.factor(V1 ) ]
    res[ , V2  := as.factor(V2 ) ]
    res[ , V3  := as.factor(V3 ) ]
    res[ , V4  := as.factor(V4 ) ]
    res[ , V5  := as.factor(V5 ) ]
    res[ , V6  := as.factor(V6 ) ]
    res[ , V7  := as.factor(V7 ) ]
    res[ , V8  := as.factor(V8 ) ]
    res[ , V9  := as.factor(V9 ) ]
    res[ , V10 := as.factor(V10) ]
    res
}
microbenchmark(     
    read_csv( 'factors.csv', n, rep( "factor", 10 ) ), 
    read.csv( 'factors.csv', sep = ",", 
        header = FALSE, stringsAsFactors = TRUE, nrows = n,
        colClasses = rep( "factor", 10 ) ), 
    fread_factors( 'factors.csv', sep = ",", header = FALSE, nrows = n ), 
    times = 10L 
)

