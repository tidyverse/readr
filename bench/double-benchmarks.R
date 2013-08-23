require(methods)
require(devtools)
require(data.table)
require(microbenchmark)
load_all( "fastread" )

n <- 1e6

tod <- parseDouble_strtod( "matrix.csv", 10*1e6 )
tof <- parseDouble_fast_atof( "matrix.csv", 10*1e6 )
qi  <- parseDouble_qi( "matrix.csv", 10*1e6 )
atof  <- parseDouble_atof( "matrix.csv", 10*1e6 )

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
    strtod( "matrix.csv", 10*1e6 ), 
    fast_atof( "matrix.csv", 10*1e6 ), 
    spirit_qi( "matrix.csv", 10*1e6 ), 
    atof( "matrix.csv", 10*1e6 ), 
    times = 5L
)

