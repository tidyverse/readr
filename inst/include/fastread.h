#ifndef FASTREAD_FASTREAD_H
#define FASTREAD_FASTREAD_H

#include <Rcpp.h>
using namespace Rcpp;

//#include <sys/mman.h>
//#include <sys/stat.h>
#include <boost/interprocess/file_mapping.hpp>
#include <boost/interprocess/mapped_region.hpp>

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

#include <fastread/LinePolicy.h>
#include <fastread/SeparatorPolicy.h>

#include <fastread/DateTimeParser.h>
#include <fastread/Source.h>
#include <fastread/MMapSource.h>
#include <fastread/ReadConnectionSource.h>
#include <fastread/CharacterVectorSource.h>

#include <fastread/get_int_naive.h>
#include <fastread/VectorInput.h>

#include <fastread/LinesReader.h>

#endif
