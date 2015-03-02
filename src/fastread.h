#ifndef FASTREAD_FASTREAD_H
#define FASTREAD_FASTREAD_H

#include <Rcpp.h>

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

#include "Connection.h"

#include "LinePolicy.h"
#include "SeparatorPolicy.h"

#include "DateTimeParser.h"
#include "Source.h"
#include "MMapSource.h"
#include "ReadConnectionSource.h"
#include "CharacterVectorSource.h"

#include "get_int_naive.h"
#include "VectorInput.h"

#include "LinesReader.h"

#endif
