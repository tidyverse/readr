#ifndef FASTREAD_HSOURCEFILE_H
#define FASTREAD_HSOURCEFILE_H

#include <boost/interprocess/file_mapping.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <Rcpp.h>

class StreamFile {
  boost::interprocess::file_mapping fm_;
  boost::interprocess::mapped_region mr_;
  int pos_;
  size_t size_;
  char* addr_;

public:

  StreamFile(const std::string& path) : pos_(0) {
    try {
      fm_ = boost::interprocess::file_mapping(path.c_str(),
        boost::interprocess::read_only);
      mr_ = boost::interprocess::mapped_region(fm_,
        boost::interprocess::read_only);
    } catch(boost::interprocess::interprocess_exception& e) {
      Rcpp::stop("Cannot read file %s", path) ;
    }

    size_ = mr_.get_size();
    addr_ = static_cast<char*>(mr_.get_address());
  }

  int pos() {
    return pos_;
  }

  char get() {
    if (pos_ >= size_)
      return EOF;

    return addr_[pos_++];
  }

  char peek() {
    if (pos_ >= size_)
      return EOF;

    return addr_[pos_];
  }

};

#endif
