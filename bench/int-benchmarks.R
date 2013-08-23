require(methods)
require(devtools)
require(data.table)
require(microbenchmark)
load_all( "fastread" )

n <- 1e6

strtol <- parseInt_strtol
qi     <- parseInt_qi
naive  <- parseInt_naive

microbenchmark( 
    strtol( "integers.csv", 10*1e6 ), 
    qi( "integers.csv", 10*1e6 ), 
    naive( "integers.csv", 10*1e6 ),
    times = 5L
)

d1 <- strtol( "integers.csv", 10*1e6 )
d2 <- qi( "integers.csv", 10*1e6 )
d3 <- naive( "integers.csv", 10*1e6 )
identical( d1, d2 )
identical( d1, d3 )

    
