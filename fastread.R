require(methods)
require(devtools)
require(data.table)

load_all( "fastread" )

n <- 1e6

if( !file.exists( "data.txt" ) ){
    line <- '1.0,1.0,1.0,1.0,2.0'
    f <- file( "data.txt", open = "w" )
    for( i in 1:n ){
        writeLines( line, f )    
    }
    close(f)
}
    
make_zeros <- function( file = "zeros.csv", nc = 50, nr = 1e6 ){
    d <- matrix( sample( c(0L, 1L), nc * nr, replace = TRUE ), ncol = nc )
    write.table( d , file, row.names = FALSE, col.names = FALSE, sep = "," )    
}

make_matrix <- function( file = "matrix.csv", nc = 10, nr = 1e6 ){
    d <- matrix( rnorm(nc*nr), ncol = nc )
    write.table( d , file, row.names = FALSE, col.names = FALSE, sep = "," )    
}


require( microbenchmark )

n <- 1e6
microbenchmark(     
    read_csv( 'zeros.csv', n, rep( "int", 50 ) ), 
    read.csv( 'zeros.csv', sep = ",", 
        header = FALSE, stringsAsFactors = FALSE, nrows = n,
        colClasses = rep( "integer", 50 ) ), 
    fread( 'zeros.csv', sep = ",", header = FALSE, stringsAsFactors = FALSE, nrows = n ), 
    times = 10L 
)

microbenchmark(     
    read_csv( 'matrix.csv', n, rep( "double", 10 ) ), 
    read.csv( 'matrix.csv', sep = ",", 
        header = FALSE, stringsAsFactors = FALSE, nrows = n,
        colClasses = rep( "numeric", 10 ) ), 
    fread( 'matrix.csv', sep = ",", header = FALSE, stringsAsFactors = FALSE, nrows = n ), 
    times = 10L 
)


q("no")

message( "fastread :: read_csv" )
system.time( d1 <- read_csv( 'data.txt', n, classes = rep( "double" , 5L)  ) )
lapply( d1, head )
str( d1 )

message( "utils :: read.csv" )
system.time( d2 <- read.csv( 'data.txt', sep = ",", 
    header = FALSE, stringsAsFactors = FALSE, nrows = n,
    colClasses = rep( "numeric", 5L ) ) )
lapply( d2, head )

message( "data.table :: fread" )
system.time( d3 <- fread( 'data.txt', sep = ",", header = FALSE, 
    stringsAsFactors = FALSE, nrows = n ) )
lapply( d3, head )

q("no")

# message( "-------" )
# 
# message( "fastread :: scan_" )
# system.time( scan_( "data.txt", n*2, character() ) )
# 
# message( "utils :: scan" )
# system.time( scan( "data.txt", character(), nmax = n*2, sep = "," ) )
# 
# 
# message( "fastread :: scan_ (scanning double) " )
# system.time( scan_( "data.txt", n*2, numeric() ) )
# 
# message( "utils :: scan (scanning double)" )
# system.time( scan( "data.txt", numeric(), nmax = n*2, sep = ","  ) )


