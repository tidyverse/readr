require(methods)
require(devtools)
require(data.table)
require(microbenchmark)
load_all( "." )

n <- 1e5
source( "bench/data.R" )
if( !file.exists("bench/integers.csv") ) make_integer_matrix( "bench/integers.csv", 10, n )

strtol <- parseInt_strtol
qi     <- parseInt_qi
naive  <- parseInt_naive

microbenchmark( 
    strtol( "bench/integers.csv", 10*1e6 ), 
    qi( "bench/integers.csv", 10*1e6 ), 
    naive( "bench/integers.csv", 10*1e6 ),
    times = 5L
)

d1 <- strtol( "bench/integers.csv", 10*1e6 )
d2 <- qi( "bench/integers.csv", 10*1e6 )
d3 <- naive( "bench/integers.csv", 10*1e6 )
identical( d1, d2 )
identical( d1, d3 )

    
