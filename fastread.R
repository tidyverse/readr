require(methods)
require(devtools)
require(data.table)

load_all( "fastread" )

if( !file.exists( "data.txt" ) ){
    line <- '1, 1.3'
    f <- file( "data.txt", open = "w" )
    for( i in 1:1e6){
        writeLines( line, f )    
    }
    close(f)
}

n <- 1e6

message( "fastread :: read_csv" )
system.time( d1 <- read_csv( 'data.txt', n ) )

message( "fastread :: read_csv2" )
system.time( d1 <- read_csv2( 'data.txt', n ) )

message( "fastread :: read_file" )
system.time( d1 <- read_file( 'data.txt' ) )

message( "fastread :: read_tokens" )
system.time( d1 <- read_tokens( 'data.txt', n, 2 ) )

message( "fastread :: skip_tokens" )
system.time( d1 <- skip_tokens( 'data.txt', n, 2 ) )

message( "utils :: read.csv" )
system.time( d2 <- read.csv( 'data.txt', sep = ",", header = FALSE, stringsAsFactors = FALSE, nrows = n ) )

message( "data.table :: fread" )
system.time( d3 <- fread( 'data.txt', sep = ",", header = FALSE, stringsAsFactors = FALSE, nrows = n ) )

message( "-------" )

message( "fastread :: scan_" )
system.time( scan_( "data.txt", n*2, character() ) )

message( "utils :: scan" )
system.time( scan( "data.txt", character(), nmax = n*2, sep = "," ) )


message( "fastread :: scan_ (scanning double) " )
system.time( scan_( "data.txt", n*2, character() ) )

message( "utils :: scan (scanning double)" )
system.time( scan( "data.txt", numeric(), nmax = n*2, sep = ","  ) )


