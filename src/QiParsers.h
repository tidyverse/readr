#ifndef FASTREAD_QI_PARSERS
#define FASTREAD_QI_PARSERS

#include "boost.h"

struct DecimalCommaPolicy : public boost::spirit::qi::real_policies<long double> {
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
      boost::spirit::qi::long_double, res);
  } else if (decimalMark == ',') {
    return boost::spirit::qi::parse(first, last,
      boost::spirit::qi::real_parser<long double, DecimalCommaPolicy>(), res);
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


// First and last are updated to point to first/last successfully parsed
// character
template <typename Iterator, typename Attr>
inline bool parseNumber(char decimalMark, char groupingMark, Iterator& first,
                        Iterator& last, Attr& res) {

  Iterator cur = first;

  // Advance to first non-character
  for(; cur != last; ++cur) {
    if (*cur == '-' || *cur == decimalMark || (*cur >= '0' && *cur <= '9'))
      break;
  }

  if (cur == last) {
    return false;
  } else { // Move first to start of number
    first = cur;
  }

  double sum = 0, denom = 1;
  NumberState state = STATE_INIT;
  bool seenNumber = false;
  double sign = 1.0;

  for(; cur != last; ++cur) {
    if (state == STATE_FIN)
      break;

    switch(state) {
    case STATE_INIT:
      if (*cur == '-') {
        state = STATE_LHS;
        sign = -1.0;
      } else if (*cur == decimalMark) {
        state = STATE_RHS;
      } else if (*cur >= '0' && *cur <= '9') {
        seenNumber = true;
        state = STATE_LHS;
        sum = *cur - '0';
      } else {
        goto end;
      }
      break;
    case STATE_LHS:
      if (*cur == groupingMark) {
        // do nothing
      } else if (*cur == decimalMark) {
        state = STATE_RHS;
      } else if (*cur >= '0' && *cur <= '9') {
        seenNumber = true;
        sum *= 10;
        sum += *cur - '0';
      } else {
        goto end;
      }
      break;
    case STATE_RHS:
      if (*cur == groupingMark) {
        // do nothing
      } else if (*cur >= '0' && *cur <= '9') {
        seenNumber = true;
        denom *= 10;
        sum += (*cur - '0') / denom;
      } else {
        goto end;
      }
      break;
    case STATE_FIN:
      goto end;
    }
  }

end:

  // Set last to point to final character used
  last = cur;

  res = sign * sum;
  return seenNumber;
}


template <typename Iterator, typename Attr>
inline bool parseInt(Iterator& first, Iterator& last, Attr& res) {
  return boost::spirit::qi::parse(first, last, boost::spirit::qi::int_, res);
}

#endif
