#ifndef FASTREAD_SOURCEFILE_H_
#define FASTREAD_SOURCEFILE_H_

#include <Rcpp.h>

#include <boost/interprocess/file_mapping.hpp>
#include <boost/interprocess/mapped_region.hpp>

#include "Source.h"

class SourceFile : public Source {
  boost::interprocess::file_mapping fm_;
  boost::interprocess::mapped_region mr_;

  const char* begin_;
  const char* end_;

public:

  SourceFile(const std::string& path) {
    try {
      fm_ = boost::interprocess::file_mapping(path.c_str(),
        boost::interprocess::read_only);
      mr_ = boost::interprocess::mapped_region(fm_,
        boost::interprocess::read_only);
    } catch(boost::interprocess::interprocess_exception& e) {
      Rcpp::stop("Cannot read file %s", path) ;
    }

    begin_ = static_cast<char*>(mr_.get_address());
    end_ = begin_ + mr_.get_size();
  }

  const char* begin() {
    return begin_;
  }

  const char* end() {
    return end_;
  }

};

#endif
