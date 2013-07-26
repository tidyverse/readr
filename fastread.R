require(methods)
require(devtools)
load_all( "fastread" )

if( !file.exists( "data.txt" ) ){
    line <- '1, 1.3'
    f <- file( "data.txt", open = "w" )
    for( i in 1:1e5){
        writeLines( line, f )    
    }
    close(f)
}

n <- 1e5
message( "fastread :: read_csv" )
system.time( d1 <- read_csv( 'data.txt', n ) )

message( "utils :: read.csv" )
system.time( d2 <- read.csv( 'data.txt', sep = ",", header = FALSE, stringsAsFactors = FALSE, nrows = n ) )

system.time( scan_( "data.txt", n*2 ) )

