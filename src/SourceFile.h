#ifndef FASTREAD_SOURCEFILE_H_
#define FASTREAD_SOURCEFILE_H_

#include "Source.h"
#include "boost.h"
#include <Rcpp.h>

class SourceFile : public Source {
  boost::interprocess::file_mapping fm_;
  boost::interprocess::mapped_region mr_;

  const char* begin_;
  const char* end_;

public:
  SourceFile(
      const std::string& path,
      int skip,
      std::vector<std::string> comments,
      const std::string encoding) {

    set_encoding(encoding);
    set_comments(comments);

    try {
      fm_ = boost::interprocess::file_mapping(
          path.c_str(), boost::interprocess::read_only);
      mr_ = boost::interprocess::mapped_region(
          fm_, boost::interprocess::read_only);
    } catch (boost::interprocess::interprocess_exception& e) {
      Rcpp::stop("Cannot read file %s: %s", path, e.what());
    }

    begin_ = static_cast<char*>(mr_.get_address());
    end_ = begin_ + mr_.get_size();

    // Skip byte order mark, if needed
    begin_ = skipBom(begin_, end_);

    // Skip lines, if needed
    begin_ = skipLines(skip);
  }

  const char* begin() { return begin_; }

  const char* end() { return end_; }
};

#endif
