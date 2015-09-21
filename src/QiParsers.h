#ifndef FASTREAD_QI_PARSERS
#define FASTREAD_QI_PARSERS

#include "boost.h"

struct DecimalCommaPolicy : public boost::spirit::qi::real_policies<double> {
  template <typename Iterator>
  static bool parse_dot(Iterator& first, Iterator const& last) {
    if (first == last || *first != ',')
      return false;
    ++first;
    return true;
  }
};

template <typename Iterator, typename Attr>
inline bool parseDouble(const char decimalMark, Iterator& first, Iterator& last,
                        Attr& res) {

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

enum NumberState {
  STATE_INIT,
  STATE_LHS,
  STATE_RHS,
  STATE_FIN
};


template <typename Iterator, typename Attr>
inline bool parseNumber(char decimalMark, char groupingMark, Iterator& first,
                        Iterator& last, Attr& res) {

  // Advance to first non-character
  for(; first != last; ++first) {
    if (*first == '-' || *first == decimalMark || (*first >= '0' && *first <= '9'))
      break;
  }

  if (first == last)
    return false;

  int sign = 1;
  double sum = 0, denom = 1;
  NumberState state = STATE_INIT;

  Iterator cur = first;
  for(; cur != last; ++cur) {
    switch(state) {
    case STATE_INIT:
      if (*cur == '-') {
        state = STATE_LHS;
        sign = -1;
      } else if (*cur == decimalMark) {
        state = STATE_RHS;
      } else if (*cur >= '0' && *cur <= '9') {
        state = STATE_LHS;
        sum = *cur - '0';
      } else {
        return false;
      }
      break;
    case STATE_LHS:
      if (*cur == groupingMark) {
        // do nothing
      } else if (*cur == decimalMark) {
        state = STATE_RHS;
      } else if (*cur >= '0' && *cur <= '9') {
        sum *= 10;
        sum += *cur - '0';
      } else if (*cur == '-') {
        return false;
      } else {
        state = STATE_FIN;
        break;
      }
      break;
    case STATE_RHS:
      if (*cur == groupingMark) {
        // do nothing
      } else if (*cur == decimalMark) {
        return false;
      } else if (*cur >= '0' && *cur <= '9') {
        denom *= 10;
        sum += (*cur - '0') / denom;
      } else {
        state = STATE_FIN;
      }
      break;
    case STATE_FIN:
      last = cur++;
      res = sum;
      return true;
    }
  }

  // Hit the end of the string, so must be done
  last = cur;
  res = sum;
  return true;
}


template <typename Iterator, typename Attr>
inline bool parseInt(Iterator& first, Iterator& last, Attr& res) {
  return  boost::spirit::qi::parse(first, last, boost::spirit::qi::int_, res);
}

#endif
