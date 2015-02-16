#ifndef FASTREAD_get_int_naive_H
#define FASTREAD_get_int_naive_H

// TO DO: Is it a duplicate with respect to the get_int_naive
// function declared in Source.h ?

namespace fastread {

    inline bool valid_digit(char c){
        static char before_zero = '0' - 1 ;
        static char after_nine = '9' + 1 ;
        return c > before_zero && c < after_nine ;
    }

    inline int get_int_naive(char*& p) {
        int sign, value ;

        // Skip leading white space, if any.
        while ( *p == ' ' ) {
            ++p ;
        }

        // Get sign, if any.
        sign = 1;
        if (*p == '-') {
            sign = -1;
            ++p ;
        } else if (*p == '+') {
            ++p ;
        }

        // Exception needed because if the first character is not a
        // valid digit, then the function returns 0, which is not a
        // nice way to handle NA
        if (!valid_digit(*p))
          return -1;

        // Get digits before decimal point or exponent, if any.
        for (value = 0; valid_digit(*p); ++p ) {
            value = value * 10 + (*p - '0');
        }

        return sign * value ;
    }

}

#endif
