require(methods)
require(devtools)
require(data.table)
require(microbenchmark)
load_all( "fastread" )

n <- 1e6

dc  <- parseDouble_double_conversion( "matrix.csv", 10*1e6) 
tod <- parseDouble_strtod( "matrix.csv", 10*1e6 )
tof <- parseDouble_fast_atof( "matrix.csv", 10*1e6 )
qi  <- parseDouble_qi( "matrix.csv", 10*1e6 )

identical( qi, tod )

# diffs <- tod - tof
# sum( diffs != 0.0 )
# range( diffs[ diffs != 0.0 ] )
# table( diffs[ diffs != 0.0 ] )

strtod <- parseDouble_strtod
double_conv <- parseDouble_double_conversion
fast_atof <- parseDouble_fast_atof
spirit_qi <- parseDouble_qi

microbenchmark( 
    strtod( "matrix.csv", 10*1e6 ), 
    double_conv( "matrix.csv", 10*1e6 ), 
    fast_atof( "matrix.csv", 10*1e6 ), 
    spirit_qi( "matrix.csv", 10*1e6 ), 
    times = 5L
)

