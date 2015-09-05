#ifndef FASTREAD_QI_EURODOUBLE
#define FASTREAD_QI_EURODOUBLE

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>

struct DoubleEuroPolicy : public boost::spirit::qi::real_policies<double> {
  template <typename Iterator>
  static bool parse_dot(Iterator& first, Iterator const& last) {
    if (first == last || *first != ',')
      return false;
    ++first;
    return true;
  }
};

#endif
