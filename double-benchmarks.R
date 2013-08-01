require(methods)
require(devtools)
require(data.table)
require(microbenchmark)
load_all( "fastread" )

n <- 1e6
dc  <- parseDouble_double_conversion( "matrix.csv", 10*1e6) 
tod <- parseDouble_strtod( "matrix.csv", 10*1e6 )
identical( dc, tod )

microbenchmark( 
    parseDouble_strtod( "matrix.csv", 10*1e6 ), 
    parseDouble_double_conversion( "matrix.csv", 10*1e6 ), 
    times = 10L
)
    

