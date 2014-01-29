#ifndef FASTREAD_FASTREAD_H
#define FASTREAD_FASTREAD_H

#include <Rcpp.h>
using namespace Rcpp; 

#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>   // for open()
#include <unistd.h>  // for close()

#include <iostream>
#include <fstream>
#include <sstream>
#include <boost/unordered_map.hpp>

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>

#include <fastread/Connection.h>

#include <fastread/Source.h>
#include <fastread/MMapSource.h>
#include <fastread/ReadConnectionSource.h>

#include <fastread/get_int_naive.h>
#include <fastread/VectorInput.h>
#include <fastread/MMapReader.h>
#include <fastread/DataReader.h>

#endif
