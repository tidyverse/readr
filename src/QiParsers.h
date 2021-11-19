#ifndef FASTREAD_QI_PARSERS
#define FASTREAD_QI_PARSERS

#include "Rinternals.h"

/*
    An STL iterator-based string to floating point number conversion.
    This function was adapted from the C standard library of RetroBSD,
    which is based on Berkeley UNIX.
    This function and this function only is BSD license.

    https://retrobsd.googlecode.com/svn/stable/vroom_time.h|31 col 32| for
   (const autosrc str : info->column.slice(start, end)) {/libc/stdlib/strtod.c
   */
inline double
bsd_strtod(const char* begin, const char** endptr, const char decimal_mark) {
  if (begin == *endptr) {
    return NA_REAL;
  }
  if (*begin == 'n' || *begin == '?') {
    *endptr = begin;
    return NA_REAL;
  }
  int sign = 0, expSign = 0, i;
  double fraction, dblExp;
  const char* p;
  char c;

  /* Exponent read from "EX" field. */
  int exp = 0;

  /* Exponent that derives from the fractional part.  Under normal
   * circumstances, it is the negative of the number of digits in F.
   * However, if I is very long, the last digits of I get dropped
   * (otherwise a long I with a large negative exponent could cause an
   * unnecessary overflow on I alone).  In this case, fracExp is
   * incremented one for each dropped digit. */
  int fracExp = 0;

  /* Number of digits in mantissa. */
  int mantSize;

  /* Number of mantissa digits BEFORE decimal point. */
  int decPt;

  /* Temporarily holds location of exponent in str. */
  const char* pExp;

  /* Largest possible base 10 exponent.
   * Any exponent larger than this will already
   * produce underflow or overflow, so there's
   * no need to worry about additional digits. */
  static int maxExponent = 307;

  /* Table giving binary powers of 10.
   * Entry is 10^2^i.  Used to convert decimal
   * exponents into floating-point numbers. */
  static double powersOf10[] = {
      1e1,
      1e2,
      1e4,
      1e8,
      1e16,
      1e32,
      1e64,
      1e128,
      1e256,
  };
#if 0
        static double powersOf2[] = {
                2, 4, 16, 256, 65536, 4.294967296e9, 1.8446744073709551616e19,
                //3.4028236692093846346e38, 1.1579208923731619542e77, 1.3407807929942597099e154,
        };
        static double powersOf8[] = {
                8, 64, 4096, 2.81474976710656e14, 7.9228162514264337593e28,
                //6.2771017353866807638e57, 3.9402006196394479212e115, 1.5525180923007089351e231,
        };
        static double powersOf16[] = {
                16, 256, 65536, 1.8446744073709551616e19,
                //3.4028236692093846346e38, 1.1579208923731619542e77, 1.3407807929942597099e154,
        };
#endif

  /*
   * Strip off leading blanks and check for a sign.
   */
  p = begin;
  while (p != *endptr && (*p == ' ' || *p == '\t'))
    ++p;
  if (p != *endptr && *p == '-') {
    sign = 1;
    ++p;
  } else if (p != *endptr && *p == '+')
    ++p;

  /* If we don't have a digit or decimal point something is wrong, so return an
   * NA */
  if (!(isdigit(*p) || *p == decimal_mark)) {
    *endptr = p;
    return NA_REAL;
  }

  /*
   * Count the number of digits in the mantissa (including the decimal
   * point), and also locate the decimal point.
   */
  decPt = -1;
  for (mantSize = 0; p != *endptr; ++mantSize) {
    c = *p;
    if (!isdigit(c)) {
      if (c != decimal_mark || decPt >= 0)
        break;
      decPt = mantSize;
    }
    ++p;
  }

  /*
   * Now suck up the digits in the mantissa.  Use two integers to
   * collect 9 digits each (this is faster than using floating-point).
   * If the mantissa has more than 18 digits, ignore the extras, since
   * they can't affect the value anyway.
   */
  pExp = p;
  p -= mantSize;
  if (decPt < 0)
    decPt = mantSize;
  else
    --mantSize; /* One of the digits was the point. */

  if (mantSize > 2 * 9)
    mantSize = 2 * 9;
  fracExp = decPt - mantSize;
  if (mantSize == 0) {
    fraction = 0.0;
    p = begin;
    goto done;
  } else {
    int frac1, frac2;

    for (frac1 = 0; mantSize > 9 && p != *endptr; --mantSize) {
      c = *p++;
      if (c == decimal_mark)
        c = *p++;
      frac1 = frac1 * 10 + (c - '0');
    }
    for (frac2 = 0; mantSize > 0 && p != *endptr; --mantSize) {
      c = *p++;
      if (c == decimal_mark)
        c = *p++;
      frac2 = frac2 * 10 + (c - '0');
    }
    fraction = (double)1000000000 * frac1 + frac2;
  }

  /*
   * Skim off the exponent.
   */
  p = pExp;
  if (p != *endptr &&
      (*p == 'E' || *p == 'e' || *p == 'S' || *p == 's' || *p == 'F' ||
       *p == 'f' || *p == 'D' || *p == 'd' || *p == 'L' || *p == 'l')) {
    ++p;
    if (p != *endptr && *p == '-') {
      expSign = 1;
      ++p;
    } else if (p != *endptr && *p == '+')
      ++p;
    else if (!isdigit(*p)) {
      --p;
      goto done;
    }
    while (p != *endptr && isdigit(*p))
      exp = exp * 10 + (*p++ - '0');
  }
  if (expSign)
    exp = fracExp - exp;
  else
    exp = fracExp + exp;

  /*
   * Generate a floating-point number that represents the exponent.
   * Do this by processing the exponent one bit at a time to combine
   * many powers of 2 of 10. Then combine the exponent with the
   * fraction.
   */
  if (exp < 0) {
    expSign = 1;
    exp = -exp;
  } else
    expSign = 0;
  if (exp > maxExponent)
    exp = maxExponent;
  dblExp = 1.0;
  for (i = 0; exp; exp >>= 1, ++i)
    if (exp & 01)
      dblExp *= powersOf10[i];
  if (expSign)
    fraction /= dblExp;
  else
    fraction *= dblExp;

done:
  if (p != *endptr) {
    *endptr = p;
  }
  return sign ? -fraction : fraction;
}

template <typename Iterator, typename Attr>
inline bool parseDouble(
    const char decimalMark, Iterator& first, Iterator& last, Attr& res) {

  res = bsd_strtod(first, &last, decimalMark);
  return !ISNA(res);
}

enum NumberState { STATE_INIT, STATE_LHS, STATE_RHS, STATE_EXP, STATE_FIN };

// First and last are updated to point to first/last successfully parsed
// character
template <typename Iterator, typename Attr>
inline bool parseNumber(
    char decimalMark,
    char groupingMark,
    Iterator& first,
    Iterator& last,
    Attr& res) {

  Iterator cur = first;

  // Advance to first non-character
  for (; cur != last; ++cur) {
    if (*cur == '-' || *cur == decimalMark || (*cur >= '0' && *cur <= '9'))
      break;
  }

  if (cur == last) {
    return false;
  } else { // Move first to start of number
    first = cur;
  }

  double sum = 0, denom = 1, exponent = 0;
  NumberState state = STATE_INIT;
  bool seenNumber = false, exp_init = true;
  double sign = 1.0, exp_sign = 1.0;

  for (; cur != last; ++cur) {
    if (state == STATE_FIN)
      break;

    switch (state) {
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
      } else if (seenNumber && (*cur == 'e' || *cur == 'E')) {
        state = STATE_EXP;
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
      } else if (seenNumber && (*cur == 'e' || *cur == 'E')) {
        state = STATE_EXP;
      } else if (*cur >= '0' && *cur <= '9') {
        seenNumber = true;
        denom *= 10;
        sum += (*cur - '0') / denom;
      } else {
        goto end;
      }
      break;
    case STATE_EXP:
      // negative/positive sign only allowed immediately after 'e' or 'E'
      if (*cur == '-' && exp_init) {
        exp_sign = -1.0;
        exp_init = false;
      } else if (*cur == '+' && exp_init) {
        // sign defaults to positive
        exp_init = false;
      } else if (*cur >= '0' && *cur <= '9') {
        exponent *= 10.0;
        exponent += *cur - '0';
        exp_init = false;
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

  // If the number was in scientific notation, multiply by 10^exponent
  if (exponent) {
    res *= pow(10.0, exp_sign * exponent);
  }

  return seenNumber;
}

template <typename Iterator, typename Attr>
inline bool parseInt(Iterator& first, Iterator& last, Attr& res) {

  char buf[64];

  size_t expected_size = last - first;

  if (expected_size > sizeof(buf) - 1) {
    res = NA_INTEGER;
    return false;
  }

  std::copy(first, last, buf);
  buf[expected_size] = '\0';

  long lres;
  char* endp;

  errno = 0;
  lres = strtol(buf, &endp, 10);
  size_t parsed_size = endp - buf;
  /* next can happen on a 64-bit platform */
  if (res > INT_MAX || res < INT_MIN)
    lres = NA_INTEGER;
  if (errno == ERANGE)
    lres = NA_INTEGER;

  res = static_cast<int>(lres);

  first += parsed_size;

  return res != NA_INTEGER;
}

#endif
