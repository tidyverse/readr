#ifndef READR_WRITE_CONNECTION_H_
#define READR_WRITE_CONNECTION_H_

#include <Rcpp.h>
#include <boost/iostreams/categories.hpp> // sink_tag
#include <ios>                            // streamsize

typedef struct Rconn* Rconnection;
Rconnection get_connection(SEXP con);

// http://www.boost.org/doc/libs/1_63_0/libs/iostreams/doc/tutorial/container_sink.html
namespace io = boost::iostreams;

class connection_sink {
private:
  Rconnection con_;

public:
  typedef char char_type;
  typedef io::sink_tag category;

  connection_sink(SEXP con);
  std::streamsize write(const char* s, std::streamsize n);
};

#endif
