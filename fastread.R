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
  
# require( microbenchmark )
# microbenchmark(     
#     read_csv( 'data.txt', n, rep( "double", 5 ) ), 
#     read.csv( 'data.txt', sep = ",", 
#         header = FALSE, stringsAsFactors = FALSE, nrows = n,
#         colClasses = c("numeric", "numeric", "numeric", "numeric", "numeric" ) ), 
#     fread( 'data.txt', sep = ",", header = FALSE, stringsAsFactors = FALSE, nrows = n ), 
#     times = 10L 
# )
#  
# q("no")

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


