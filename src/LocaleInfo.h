#ifndef FASTREAD_LOCALINFO
#define FASTREAD_LOCALINFO

class LocaleInfo {

public:
  // LC_TIME
  std::vector<std::string> mon_, monAb_, day_, dayAb_, amPm_;
  std::string dateFormat_, timeFormat_;

  // LC_NUMERIC
  char decimalMark_, groupingMark_;

  // LC_MISC
  std::string tz_;
  std::string encoding_;

  LocaleInfo(Rcpp::List);

};

#endif
