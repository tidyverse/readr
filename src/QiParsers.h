#ifndef FASTREAD_QI_PARSERS
#define FASTREAD_QI_PARSERS

#include <boost/spirit/include/qi.hpp>

struct DecimalCommaPolicy : public boost::spirit::qi::real_policies<double> {
  template <typename Iterator>
  static bool parse_dot(Iterator& first, Iterator const& last) {
    if (first == last || *first != ',')
      return false;
    ++first;
    return true;
  }
};

template <typename Iterator>
inline bool parseDouble(const char decimalMark, Iterator& first, Iterator& last,
                        double& res) {

  if (decimalMark == '.') {
    return boost::spirit::qi::parse(first, last,
      boost::spirit::qi::double_, res);
  } else if (decimalMark == ',') {
    return boost::spirit::qi::parse(first, last,
      boost::spirit::qi::real_parser<double, DecimalCommaPolicy>(), res);
  } else {
    return false;
  }
}

template <typename Iterator>
inline bool parseInt(Iterator& first, Iterator& last, int& res) {
  return  boost::spirit::qi::parse(first, last, boost::spirit::qi::int_, res);
}

#endif
