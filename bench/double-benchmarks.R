require(methods)
require(devtools)
require(data.table)
require(microbenchmark)
load_all( "." )

n <- 1e5
source("bench/data.R")
if( !file.exists("bench/matrix.csv") ) make_matrix( "bench/matrix.csv", 10, n )

tod <- parseDouble_strtod( "bench/matrix.csv", 10*1e6 )
tof <- parseDouble_fast_atof( "bench/matrix.csv", 10*1e6 )
qi  <- parseDouble_qi( "bench/matrix.csv", 10*1e6 )
atof  <- parseDouble_atof( "bench/matrix.csv", 10*1e6 )

identical( qi, tod )

# diffs <- tod - tof
# sum( diffs != 0.0 )
# range( diffs[ diffs != 0.0 ] )
# table( diffs[ diffs != 0.0 ] )

strtod <- parseDouble_strtod
fast_atof <- parseDouble_fast_atof
spirit_qi <- parseDouble_qi
atof <- parseDouble_atof


microbenchmark( 
    strtod( "bench/matrix.csv", 10*1e6 ), 
    fast_atof( "bench/matrix.csv", 10*1e6 ), 
    spirit_qi( "bench/matrix.csv", 10*1e6 ), 
    atof( "bench/matrix.csv", 10*1e6 ), 
    times = 5L
)

