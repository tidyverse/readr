require(methods)
require(devtools)
require(data.table)
load_all( "." )
 
source("bench/data.R")
n <- 1e5
if( !file.exists("bench/integers.csv") ) make_integer_matrix( "bench/integers.csv", 10, n )
if( !file.exists("bench/matrix.csv") ) make_matrix( "bench/matrix.csv", 10, n )
if( !file.exists("bench/factors.csv") ) make_factors( "bench/factors.csv", 10, n )

require( microbenchmark )

options( width = 150, digits = 3 )

# d1 <- read_csv( 'bench/matrix.csv', n, rep( "double", 10 ) )
# d2 <- fread( 'bench/matrix.csv', sep = ",", header = FALSE, stringsAsFactors = FALSE, nrows = n )
# d3 <- read.csv( 'bench/matrix.csv', sep = ",", 
#          header = FALSE, stringsAsFactors = FALSE, nrows = n,
#          colClasses = rep( "numeric", 10 ) )
# stopifnot( all.equal( d1, d3 ) )
#          
microbenchmark(     
    fastread = read_csv( 'bench/matrix.csv', n, rep( "double", 10 ) ), 
    # base = read.csv( 'bench/matrix.csv', sep = ",", 
    #     header = FALSE, stringsAsFactors = FALSE, nrows = n,
    #     colClasses = rep( "numeric", 10 ) ), 
    datatable = fread( 'bench/matrix.csv', sep = ",", header = FALSE, stringsAsFactors = FALSE, nrows = n ), 
    times = 10L 
)
  

microbenchmark(     
    fastread = read_csv( 'bench/integers.csv', n, rep( "int", 10 ) ), 
    # base = read.csv( 'bench/integers.csv', sep = ",", 
    #     header = FALSE, stringsAsFactors = FALSE, nrows = n,
    #     colClasses = rep( "numeric", 10 ) ), 
    datatable = fread( 'bench/integers.csv', sep = ",", header = FALSE, stringsAsFactors = FALSE, nrows = n ), 
    times = 10L 
)
# d1 <- read_csv( 'bench/integers.csv', n, rep( "int", 10 ) )
# d2 <- read.csv( 'bench/integers.csv', sep = ",", 
#          header = FALSE, stringsAsFactors = FALSE, nrows = n,
#          colClasses = rep( "integer", 10 ) )
# all.equal( d1, d2 )
#         

# f <- read_csv( 'bench/factors.csv', n, rep( "factor", 10 ) )
# d <- read.csv( "bench/factors.csv", header = FALSE )
# e <- fread( "bench/factors.csv", stringsAsFactors = TRUE, sep = ",", header = FALSE, nrows = n )

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
    fastread = read_csv( 'bench/factors.csv', n, rep( "factor", 10 ) ), 
    # base = read.csv( 'bench/factors.csv', sep = ",", 
    #     header = FALSE, stringsAsFactors = TRUE, nrows = n,
    #     colClasses = rep( "factor", 10 ) ), 
    datatable = fread_factors( 'bench/factors.csv', sep = ",", header = FALSE, nrows = n ), 
    times = 10L 
)

# microbenchmark(     
#     fastread = read_csv( 'bench/factors.csv', n, rep( "character", 10 ) ), 
#     base = read.csv( 'bench/factors.csv', sep = ",", 
#         header = FALSE, stringsAsFactors = FALSE, nrows = n,
#         colClasses = rep( "character", 10 ) ), 
#     datatable = fread( 'bench/factors.csv', sep = ",", header = FALSE, nrows = n ), 
#     times = 10L 
# )
# 
