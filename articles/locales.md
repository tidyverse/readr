# Locales

The goal of readr’s locales is to encapsulate common options that vary
between languages and localities. This includes:

- The names of months and days, used when parsing dates.
- The default time zone, used when parsing datetimes.
- The character encoding, used when reading non-ASCII strings.
- Default date format, used when guessing column types.
- The decimal and grouping marks, used when reading numbers.

(Strictly speaking these are not locales in the usual technical sense of
the word because they also contain information about time zones and
encoding.)

To create a new locale, you use the
[`locale()`](https://readr.tidyverse.org/reference/locale.md) function:

``` r
locale()
#> <locale>
#> Numbers:  123,456.78
#> Formats:  %AD / %AT
#> Timezone: UTC
#> Encoding: UTF-8
#> <date_names>
#> Days:   Sunday (Sun), Monday (Mon), Tuesday (Tue), Wednesday (Wed),
#>         Thursday (Thu), Friday (Fri), Saturday (Sat)
#> Months: January (Jan), February (Feb), March (Mar), April (Apr), May
#>         (May), June (Jun), July (Jul), August (Aug), September
#>         (Sep), October (Oct), November (Nov), December (Dec)
#> AM/PM:  AM/PM
```

This rest of this vignette will explain what each of the options do.

All of the parsing function in readr take a `locale` argument. You’ll
most often use it with
[`read_csv()`](https://readr.tidyverse.org/reference/read_delim.md),
[`read_fwf()`](https://readr.tidyverse.org/reference/read_fwf.md) or
[`read_table()`](https://readr.tidyverse.org/reference/read_table.md).
Readr is designed to work the same way across systems, so the default
locale is English centric like R. If you’re not in an English speaking
country, this makes initial import a little harder, because you have to
override the defaults. But the payoff is big: you can share your code
and know that it will work on any other system. Base R takes a different
philosophy. It uses system defaults, so typical data import is a little
easier, but sharing code is harder.

Rather than demonstrating the use of locales with
[`read_csv()`](https://readr.tidyverse.org/reference/read_delim.md) and
fields, in this vignette I’m going to use the `parse_*()` functions.
These work with a character vector instead of a file on disk, so they’re
easier to use in examples. They’re also useful in their own right if you
need to do custom parsing. See
[`type_convert()`](https://readr.tidyverse.org/reference/type_convert.md)
if you need to apply multiple parsers to a data frame.

## Dates and times

### Names of months and days

The first argument to
[`locale()`](https://readr.tidyverse.org/reference/locale.md) is
`date_names`, and it controls what values are used for month and day
names. The easiest way to specify it is with a ISO 639 language code:

``` r
locale("ko") # Korean
#> <locale>
#> Numbers:  123,456.78
#> Formats:  %AD / %AT
#> Timezone: UTC
#> Encoding: UTF-8
#> <date_names>
#> Days:   일요일 (일), 월요일 (월), 화요일 (화), 수요일 (수), 목요일
#>         (목), 금요일 (금), 토요일 (토)
#> Months: 1월, 2월, 3월, 4월, 5월, 6월, 7월, 8월, 9월, 10월, 11월, 12월
#> AM/PM:  오전/오후
locale("fr") # French
#> <locale>
#> Numbers:  123,456.78
#> Formats:  %AD / %AT
#> Timezone: UTC
#> Encoding: UTF-8
#> <date_names>
#> Days:   dimanche (dim.), lundi (lun.), mardi (mar.), mercredi (mer.),
#>         jeudi (jeu.), vendredi (ven.), samedi (sam.)
#> Months: janvier (janv.), février (févr.), mars (mars), avril (avr.),
#>         mai (mai), juin (juin), juillet (juil.), août (août),
#>         septembre (sept.), octobre (oct.), novembre (nov.),
#>         décembre (déc.)
#> AM/PM:  AM/PM
```

If you don’t already know the code for your language,
[Wikipedia](https://en.wikipedia.org/wiki/List_of_ISO_639-1_codes) has a
good list. Currently readr has 185 languages available. You can list
them all with
[`date_names_langs()`](https://readr.tidyverse.org/reference/date_names.md).

Specifying a locale allows you to parse dates in other languages:

``` r
parse_date("1 janvier 2015", "%d %B %Y", locale = locale("fr"))
#> [1] "2015-01-01"
parse_date("14 oct. 1979", "%d %b %Y", locale = locale("fr"))
#> [1] "1979-10-14"
```

For many languages, it’s common to find that diacritics have been
stripped so they can be stored as ASCII. You can tell the locale that
with the `asciify` option:

``` r
parse_date("1 août 2015", "%d %B %Y", locale = locale("fr"))
#> [1] "2015-08-01"
parse_date("1 aout 2015", "%d %B %Y", locale = locale("fr", asciify = TRUE))
#> [1] "2015-08-01"
```

Note that the quality of the translations is variable, especially for
the rarer languages. If you discover that they’re not quite right for
your data, you can create your own with
[`date_names()`](https://readr.tidyverse.org/reference/date_names.md).
The following example creates a locale with Māori date names:

``` r
maori <- locale(date_names(
  day = c("Rātapu", "Rāhina", "Rātū", "Rāapa", "Rāpare", "Rāmere", "Rāhoroi"),
  mon = c("Kohi-tātea", "Hui-tanguru", "Poutū-te-rangi", "Paenga-whāwhā",
    "Haratua", "Pipiri", "Hōngongoi", "Here-turi-kōkā", "Mahuru",
    "Whiringa-ā-nuku", "Whiringa-ā-rangi", "Hakihea")
))
```

### Timezones

Unless otherwise specified, readr assumes that times are in UTC, the
Universal Coordinated Time (this is a successor to GMT and for almost
all intents is identical). UTC is most suitable for data because it
doesn’t have daylight savings - this avoids a whole class of potential
problems. If your data isn’t already in UTC, you’ll need to supply a
`tz` in the locale:

``` r
parse_datetime("2001-10-10 20:10")
#> [1] "2001-10-10 20:10:00 UTC"
parse_datetime("2001-10-10 20:10", locale = locale(tz = "Pacific/Auckland"))
#> [1] "2001-10-10 20:10:00 NZDT"
parse_datetime("2001-10-10 20:10", locale = locale(tz = "Europe/Dublin"))
#> [1] "2001-10-10 20:10:00 IST"
```

You can see a complete list of time zones with
[`OlsonNames()`](https://rdrr.io/r/base/timezones.html).

If you’re American, note that “EST” is a Canadian time zone that does
not have DST. It’s not Eastern Standard Time! Instead use:

- PST/PDT = “US/Pacific”
- CST/CDT = “US/Central”
- MST/MDT = “US/Mountain”
- EST/EDT = “US/Eastern”

(Note that there are more specific time zones for smaller areas that
don’t follow the same rules. For example, “US/Arizona”, which follows
mostly follows mountain time, but doesn’t have daylight savings. If
you’re dealing with historical data, you might need an even more
specific zone like “America/North_Dakota/New_Salem” - that will get you
the most accurate time zones.)

Note that these are only used as defaults. If individual times have
timezones and you’re using “%Z” (as name, e.g. “America/Chicago”) or
“%z” (as offset from UTC, e.g. “+0800”), they’ll override the defaults.
There’s currently no good way to parse times that use US abbreviations.

Note that once you have the date in R, changing the time zone just
changes its printed representation - it still represents the same
instants of time. If you’ve loaded non-UTC data, and want to display it
as UTC, try this snippet of code:

``` r
is_datetime <- sapply(df, inherits, "POSIXct")
df[is_datetime] <- lapply(df[is_datetime], function(x) {
  attr(x, "tzone") <- "UTC"
  x
})
```

### Default formats

Locales also provide default date and time formats. The date format is
used when guessing column types. The default date format is `%AD`, a
flexible YMD parser (see
[`?parse_date`](https://readr.tidyverse.org/reference/parse_datetime.md)):

``` r
str(parse_guess("2010-10-10"))
#>  Date[1:1], format: "2010-10-10"
str(parse_guess("2010/10/10"))
#>  Date[1:1], format: "2010-10-10"
```

If you’re an American, you might want to use your illogical date
system::

``` r
str(parse_guess("01/31/2013"))
#>  chr "01/31/2013"
str(parse_guess("01/31/2013", locale = locale(date_format = "%m/%d/%Y")))
#>  Date[1:1], format: "2013-01-31"
```

The time format is also used when guessing column types. The default
time format is `%AT`, a flexible HMS parser (see
[`?parse_time`](https://readr.tidyverse.org/reference/parse_datetime.md)):

``` r
str(parse_guess("17:55:14"))
#>  'hms' num 17:55:14
#>  - attr(*, "units")= chr "secs"
str(parse_guess("5:55:14 PM"))
#>  'hms' num 17:55:14
#>  - attr(*, "units")= chr "secs"
# Example of a non-standard time
str(parse_guess("h5m55s14 PM"))
#>  chr "h5m55s14 PM"
str(parse_guess("h5m55s14 PM", locale = locale(time_format = "h%Hm%Ms%S %p")))
#>  'hms' num 17:55:14
#>  - attr(*, "units")= chr "secs"
```

## Character

All readr functions yield strings encoded in UTF-8. This encoding is the
most likely to give good results in the widest variety of settings. By
default, readr assumes that your input is also in UTF-8. This is less
likely to be the case, especially when you’re working with older
datasets.

The following code illustrates the problems with encodings:

``` r
library(stringi)
x <- "Émigré cause célèbre déjà vu.\n"
y <- stri_conv(x, "UTF-8", "latin1")

# These strings look like they're identical:
x
#> [1] "Émigré cause célèbre déjà vu.\n"
y
#> [1] "Émigré cause célèbre déjà vu.\n"
identical(x, y)
#> [1] TRUE

# But they have different encodings:
Encoding(x)
#> [1] "UTF-8"
Encoding(y)
#> [1] "latin1"

# That means while they print the same, their raw (binary)
# representation is actually quite different:
charToRaw(x)
#>  [1] c3 89 6d 69 67 72 c3 a9 20 63 61 75 73 65 20 63 c3 a9 6c c3 a8 62
#> [23] 72 65 20 64 c3 a9 6a c3 a0 20 76 75 2e 0a
charToRaw(y)
#>  [1] c9 6d 69 67 72 e9 20 63 61 75 73 65 20 63 e9 6c e8 62 72 65 20 64
#> [23] e9 6a e0 20 76 75 2e 0a

# readr expects strings to be encoded as UTF-8. If they're
# not, you'll get weird characters
parse_character(x)
#> [1] "Émigré cause célèbre déjà vu.\n"
parse_character(y)
#> [1] "\xc9migr\xe9 cause c\xe9l\xe8bre d\xe9j\xe0 vu.\n"

# If you know the encoding, supply it:
parse_character(y, locale = locale(encoding = "latin1"))
#> [1] "Émigré cause célèbre déjà vu.\n"
```

If you don’t know what encoding the file uses, try
[`guess_encoding()`](https://readr.tidyverse.org/reference/encoding.html).
It’s not 100% perfect (as it’s fundamentally a heuristic), but should at
least get you pointed in the right direction:

``` r
guess_encoding(x)
#> # A tibble: 3 × 2
#>   encoding     confidence
#>   <chr>             <dbl>
#> 1 UTF-8              1   
#> 2 windows-1250       0.34
#> 3 windows-1252       0.26
guess_encoding(y)
#> # A tibble: 2 × 2
#>   encoding   confidence
#>   <chr>           <dbl>
#> 1 ISO-8859-2        0.4
#> 2 ISO-8859-1        0.3

# Note that the first guess produces a valid string, but isn't correct:
parse_character(y, locale = locale(encoding = "ISO-8859-2"))
#> [1] "Émigré cause célčbre déjŕ vu.\n"
# But ISO-8859-1 is another name for latin1
parse_character(y, locale = locale(encoding = "ISO-8859-1"))
#> [1] "Émigré cause célèbre déjà vu.\n"
```

## Numbers

Some countries use the decimal point, while others use the decimal
comma. The `decimal_mark` option controls which readr uses when parsing
doubles:

``` r
parse_double("1,23", locale = locale(decimal_mark = ","))
#> [1] 1.23
```

Additionally, when writing out big numbers, you might have `1,000,000`,
`1.000.000`, `1 000 000`, or `1'000'000`. The grouping mark is ignored
by the more flexible number parser:

``` r
parse_number("$1,234.56")
#> [1] 1234.56
parse_number("$1.234,56", 
  locale = locale(decimal_mark = ",", grouping_mark = ".")
)
#> [1] 1234.56

# readr is smart enough to guess that if you're using , for decimals then
# you're probably using . for grouping:
parse_number("$1.234,56", locale = locale(decimal_mark = ","))
#> [1] 1234.56
```
