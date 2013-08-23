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

