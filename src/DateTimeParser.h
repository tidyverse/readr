#ifndef FASTREAD_DATE_TIME_PARSER_H_
#define FASTREAD_DATE_TIME_PARSER_H_

#include "DateTime.h"
#include "LocaleInfo.h"
#include "QiParsers.h"
#include "cpp11/protect.hpp"

#include "utils.h"
#include <ctime>

// Parsing ---------------------------------------------------------------------

class DateTimeParser {
  int sign_, year_, mon_, day_, hour_, min_, sec_;
  double psec_;
  int amPm_;
  bool compactDate_; // used for guessing

  int tzOffsetHours_, tzOffsetMinutes_;
  std::string tz_;

  LocaleInfo* pLocale_;
  std::string tzDefault_;

  const char* dateItr_;
  const char* dateEnd_;

public:
  DateTimeParser(LocaleInfo* pLocale)
      : pLocale_(pLocale),
        tzDefault_(pLocale->tz_),
        dateItr_(NULL),
        dateEnd_(NULL) {
    reset();
  }

  // Parse ISO8601 date time. In benchmarks this only seems ~30% faster than
  // parsing with a format string so it doesn't seem necessary to add individual
  // parsers for other common formats.
  bool parseISO8601(bool partial = true) {
    // Date: YYYY-MM-DD, YYYYMMDD
    if (!consumeInteger(4, &year_))
      return false;
    if (consumeThisChar('-'))
      compactDate_ = false;
    if (!consumeInteger(2, &mon_))
      return false;
    if (!compactDate_ && !consumeThisChar('-'))
      return false;
    if (!consumeInteger(2, &day_))
      return false;

    if (isComplete())
      return true;

    // Spec requires T, but common to use space instead
    char next;
    if (!consumeChar(&next))
      return false;
    if (next != 'T' && next != ' ')
      return false;

    // hh:mm:ss.sss, hh:mm:ss, hh:mm, hh
    // hhmmss.sss, hhmmss, hhmm
    if (!consumeInteger(2, &hour_))
      return false;
    consumeThisChar(':');
    consumeInteger(2, &min_);
    consumeThisChar(':');
    consumeSeconds(&sec_, &psec_);

    if (isComplete())
      return true;

    // Has a timezone
    tz_ = "UTC";
    if (!consumeTzOffset(&tzOffsetHours_, &tzOffsetMinutes_))
      return false;

    return isComplete();
  }

  bool parseLocaleTime() { return parse(pLocale_->timeFormat_); }

  bool parseLocaleDate() { return parse(pLocale_->dateFormat_); }

  // A flexible time parser for the most common formats
  bool parseTime() {
    if (!consumeInteger(2, &hour_, false))
      return false;
    if (!consumeThisChar(':'))
      return false;
    if (!consumeInteger(2, &min_))
      return false;
    consumeThisChar(':');
    consumeSeconds(&sec_, NULL);

    consumeWhiteSpace();
    consumeString(pLocale_->amPm_, &amPm_);
    consumeWhiteSpace();

    return isComplete();
  }

  bool parseDate() {
    // Date: YYYY-MM-DD, YYYY/MM/DD
    if (!consumeInteger(4, &year_))
      return false;
    if (!consumeThisChar('-') && !consumeThisChar('/'))
      return false;
    if (!consumeInteger(2, &mon_))
      return false;
    if (!consumeThisChar('-') && !consumeThisChar('/'))
      return false;
    if (!consumeInteger(2, &day_))
      return false;

    return isComplete();
  }

  bool isComplete() { return dateItr_ == dateEnd_; }

  void setDate(const char* date) {
    reset();
    dateItr_ = date;
    dateEnd_ = date + strlen(date);
  }

  bool parse(const std::string& format) {
    consumeWhiteSpace(); // always consume leading whitespace

    std::string::const_iterator formatItr, formatEnd = format.end();
    for (formatItr = format.begin(); formatItr != formatEnd; ++formatItr) {
      // Whitespace in format matches 0 or more whitespace in date
      if (std::isspace(*formatItr)) {
        consumeWhiteSpace();
        continue;
      }

      // Any other characters must much exactly.
      if (*formatItr != '%') {
        if (!consumeThisChar(*formatItr))
          return false;
        continue;
      }

      if (formatItr + 1 == formatEnd)
        cpp11::stop("Invalid format: trailing %%");
      formatItr++;

      switch (*formatItr) {
      case 'Y': // year with century
        if (!consumeInteger(4, &year_))
          return false;
        break;
      case 'y': // year without century
        if (!consumeInteger(2, &year_))
          return false;
        year_ += (year_ < 69) ? 2000 : 1900;
        break;
      case 'm': // month
        if (!consumeInteger(2, &mon_, false))
          return false;
        break;
      case 'b': // abbreviated month name
        if (!consumeString(pLocale_->monAb_, &mon_))
          return false;
        break;
      case 'B': // month name
        if (!consumeString(pLocale_->mon_, &mon_))
          return false;
        break;
      case 'd': // day
        if (!consumeInteger(2, &day_, false))
          return false;
        break;
      case 'a': // abbreviated day of week
        if (!consumeString(pLocale_->dayAb_, &day_))
          return false;
        break;
      case 'e': // day with optional leading space
        if (!consumeIntegerWithSpace(2, &day_))
          return false;
        break;
      case 'h': // hour, unrestricted
        if (!consumeHours(&hour_, &sign_))
          return false;
        break;
      case 'H': // hour, 0-23
        if (!consumeInteger(2, &hour_, false))
          return false;
        if (hour_ < 0 || hour_ > 23) {
          return false;
        }
        break;
      case 'I': // hour
        if (!consumeInteger(2, &hour_, false))
          return false;
        if (hour_ < 1 || hour_ > 12) {
          return false;
        }
        hour_ %= 12;
        break;
      case 'M': // minute
        if (!consumeInteger(2, &min_))
          return false;
        break;
      case 'S': // seconds (integer)
        if (!consumeSeconds(&sec_, NULL))
          return false;
        break;
      case 'O': // seconds (double)
        if (formatItr + 1 == formatEnd || *(formatItr + 1) != 'S')
          cpp11::stop("Invalid format: %%O must be followed by %%S");
        formatItr++;
        if (!consumeSeconds(&sec_, &psec_))
          return false;
        break;

      case 'p': // AM/PM
        if (!consumeString(pLocale_->amPm_, &amPm_))
          return false;
        break;

      case 'z': // time zone specification
        tz_ = "UTC";
        if (!consumeTzOffset(&tzOffsetHours_, &tzOffsetMinutes_))
          return false;
        break;
      case 'Z': // time zone name
        if (!consumeTzName(&tz_))
          return false;
        break;

      // Extensions
      case '.':
        if (!consumeNonDigit())
          return false;
        break;

      case '+':
        if (!consumeNonDigits())
          return false;
        break;

      case '*':
        consumeNonDigits();
        break;

      case 'A': // auto date / time
        if (formatItr + 1 == formatEnd)
          cpp11::stop("Invalid format: %%A must be followed by another letter");
        formatItr++;
        switch (*formatItr) {
        case 'D':
          if (!parseDate())
            return false;
          break;
        case 'T':
          if (!parseTime())
            return false;
          break;
        default:
          cpp11::stop("Invalid %%A auto parser");
        }
        break;

      // Compound formats
      case 'D':
        parse("%m/%d/%y");
        break;
      case 'F':
        parse("%Y-%m-%d");
        break;
      case 'R':
        parse("%H:%M");
        break;
      case 'X':
      case 'T':
        parse("%H:%M:%S");
        break;
      case 'x':
        parse("%y/%m/%d");
        break;

      default:
        cpp11::stop("Unsupported format %%%s", formatItr);
      }
    }

    consumeWhiteSpace(); // always consume trailing whitespace

    return isComplete();
  }

  DateTime makeDateTime() {
    DateTime dt(year_, mon_, day_, hour(), min_, sec_, psec_, tz_);
    if (tz_ == "UTC")
      dt.setOffset(-tzOffsetHours_ * 3600 - tzOffsetMinutes_ * 60);

    return dt;
  }
  DateTime makeDate() {
    DateTime dt(year_, mon_, day_, 0, 0, 0, 0, "UTC");
    return dt;
  }
  DateTime makeTime() {
    DateTime dt(
        0,
        1,
        1,
        sign_ * hour(),
        sign_ * min_,
        sign_ * sec_,
        sign_ * psec_,
        "UTC");
    return dt;
  }

  bool compactDate() { return compactDate_; }

  int year() { return year_; }

private:
  int hour() {
    if (hour_ == 12) {

      // 12 AM
      if (amPm_ == 1) {
        return hour_ - 12;
      }

      // 12 PM
      return hour_;
    }

    // Rest of PM
    if (amPm_ == 2) {
      return hour_ + 12;
    }

    // 24 hour time
    return hour_;
  }

  inline bool consumeHours(int* pHour, int* pSign) {
    if (dateItr_ == dateEnd_)
      return false;

    int sign = 1;

    if (*dateItr_ == '-') {
      sign = -1;
      ++dateItr_;
    } else if (*dateItr_ == '+') {
      ++dateItr_;
    }

    if (!consumeInteger(10, pHour, false))
      return false;

    *pSign = sign;
    return true;
  }

  inline bool consumeSeconds(int* pSec, double* pPartialSec) {
    double sec;
    if (!consumeDouble(&sec))
      return false;

    *pSec = (int)sec;
    if (pPartialSec != NULL)
      *pPartialSec = sec - *pSec;
    return true;
  }

  inline bool
  consumeString(const std::vector<std::string>& haystack, int* pOut) {
    // Assumes `pOut` is 1-indexed
    // haystack is always in UTF-8
    std::string needleUTF8 = pLocale_->encoder_.makeString(dateItr_, dateEnd_);

    for (size_t i = 0; i < haystack.size(); ++i) {
      if (istarts_with(needleUTF8, haystack[i])) {
        *pOut = i + 1;
        dateItr_ += haystack[i].size();
        return true;
      }
    }

    return false;
  }

  inline bool consumeInteger(int n, int* pOut, bool exact = true) {
    if (dateItr_ == dateEnd_ || *dateItr_ == '-' || *dateItr_ == '+')
      return false;

    const char* start = dateItr_;
    const char* end = std::min(dateItr_ + n, dateEnd_);
    bool ok = parseInt(dateItr_, end, *pOut);

    return ok && (!exact || (dateItr_ - start) == n);
  }

  // Integer indexed from 1 with optional space
  inline bool consumeIntegerWithSpace(int n, int* pOut) {
    if (consumeThisChar(' '))
      n--;

    return consumeInteger(n, pOut);
  }

  inline bool consumeDouble(double* pOut) {
    if (dateItr_ == dateEnd_ || *dateItr_ == '-' || *dateItr_ == '+')
      return false;
    const char* end = dateEnd_;
    bool ok = parseDouble(pLocale_->decimalMark_, dateItr_, end, *pOut);
    dateItr_ = end;
    return ok;
  }

  inline bool consumeWhiteSpace() {
    while (dateItr_ != dateEnd_ && std::isspace(*dateItr_))
      dateItr_++;

    return true;
  }

  inline bool consumeNonDigit() {
    if (dateItr_ == dateEnd_ || std::isdigit(*dateItr_))
      return false;

    dateItr_++;
    return true;
  }

  inline bool consumeNonDigits() {
    if (!consumeNonDigit())
      return false;

    while (dateItr_ != dateEnd_ && !std::isdigit(*dateItr_))
      dateItr_++;

    return true;
  }

  inline bool consumeChar(char* pOut) {
    if (dateItr_ == dateEnd_)
      return false;

    *pOut = *dateItr_++;
    return true;
  }

  inline bool consumeThisChar(char needed) {
    if (dateItr_ == dateEnd_ || *dateItr_ != needed)
      return false;

    dateItr_++;
    return true;
  }

  inline bool consumeAMPM(bool* pIsPM) {
    if (dateItr_ == dateEnd_)
      return false;

    if (consumeThisChar('A') || consumeThisChar('a')) {
      *pIsPM = false;
    } else if (consumeThisChar('P') || consumeThisChar('p')) {
      *pIsPM = true;
    } else {
      return false;
    }

    if (!(consumeThisChar('M') || consumeThisChar('m')))
      return false;

    return true;
  }

  // ISO8601 style
  // Z
  // ±hh:mm
  // ±hhmm
  // ±hh
  inline bool consumeTzOffset(int* pHours, int* pMinutes) {
    if (consumeThisChar('Z'))
      return true;

    // Optional +/- (required for ISO8601 but we'll let it slide)
    int mult = 1;
    if (*dateItr_ == '+' || *dateItr_ == '-') {
      mult = (*dateItr_ == '-') ? -1 : 1;
      dateItr_++;
    }

    // Required hours
    if (!consumeInteger(2, pHours))
      return false;

    // Optional colon and minutes
    consumeThisChar(':');
    consumeInteger(2, pMinutes);

    *pHours *= mult;
    *pMinutes *= mult;

    return true;
  }

  inline bool consumeTzName(std::string* pOut) {
    const char* tzStart = dateItr_;
    while (dateItr_ != dateEnd_ && !std::isspace(*dateItr_))
      dateItr_++;

    pOut->assign(tzStart, dateItr_);
    return tzStart != dateItr_;
  }

  void reset() {
    sign_ = 1;
    year_ = -1;
    mon_ = 1;
    day_ = 1;
    hour_ = 0;
    min_ = 0;
    sec_ = 0;
    psec_ = 0;
    amPm_ = -1;
    compactDate_ = true;

    tzOffsetHours_ = 0;
    tzOffsetMinutes_ = 0;
    tz_ = tzDefault_;
  }
};

#endif
