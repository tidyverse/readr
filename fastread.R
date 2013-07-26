require(methods)
require(devtools)
load_all( "fastread" )

if( !file.exists( "data.txt" ) ){
    line <- '1'
    f <- file( "data.txt", open = "w" )
    for( i in 1:1e6){
        writeLines( line, f )    
    }
    close(f)
}

n <- 1e5
message( "fastread :: read_csv" )
system.time( read_csv( 'data.txt', n ) )

message( "utils :: read.csv" )
system.time( read.csv( 'data.txt', sep = ",", header = FALSE, stringsAsFactors = FALSE, nrows = n ) )

