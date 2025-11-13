# Create locales

A locale object tries to capture all the defaults that can vary between
countries. You set the locale in once, and the details are automatically
passed on down to the columns parsers. The defaults have been chosen to
match R (i.e. US English) as closely as possible. See
[`vignette("locales")`](https://readr.tidyverse.org/dev/articles/locales.md)
for more details.

## Usage

``` r
locale(
  date_names = "en",
  date_format = "%AD",
  time_format = "%AT",
  decimal_mark = ".",
  grouping_mark = ",",
  tz = "UTC",
  encoding = "UTF-8",
  asciify = FALSE
)

default_locale()
```

## Arguments

- date_names:

  Character representations of day and month names. Either the language
  code as string (passed on to
  [`date_names_lang()`](https://readr.tidyverse.org/dev/reference/date_names.md))
  or an object created by
  [`date_names()`](https://readr.tidyverse.org/dev/reference/date_names.md).

- date_format, time_format:

  Default date and time formats.

- decimal_mark, grouping_mark:

  Symbols used to indicate the decimal place, and to chunk larger
  numbers. Decimal mark can only be `,` or `.`.

- tz:

  Default tz. This is used both for input (if the time zone isn't
  present in individual strings), and for output (to control the default
  display). The default is to use "UTC", a time zone that does not use
  daylight savings time (DST) and hence is typically most useful for
  data. The absence of time zones makes it approximately 50x faster to
  generate UTC times than any other time zone.

  Use `""` to use the system default time zone, but beware that this
  will not be reproducible across systems.

  For a complete list of possible time zones, see
  [`OlsonNames()`](https://rdrr.io/r/base/timezones.html). Americans,
  note that "EST" is a Canadian time zone that does not have DST. It is
  *not* Eastern Standard Time. It's better to use "US/Eastern",
  "US/Central" etc.

- encoding:

  Default encoding. This only affects how the file is read - readr
  always converts the output to UTF-8.

- asciify:

  Should diacritics be stripped from date names and converted to ASCII?
  This is useful if you're dealing with ASCII data where the correct
  spellings have been lost. Requires the stringi package.

## Examples

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
locale("fr")
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

# A South American locale
locale("es", decimal_mark = ",")
#> <locale>
#> Numbers:  123.456,78
#> Formats:  %AD / %AT
#> Timezone: UTC
#> Encoding: UTF-8
#> <date_names>
#> Days:   domingo (dom.), lunes (lun.), martes (mar.), miércoles (mié.),
#>         jueves (jue.), viernes (vie.), sábado (sáb.)
#> Months: enero (ene.), febrero (feb.), marzo (mar.), abril (abr.), mayo
#>         (may.), junio (jun.), julio (jul.), agosto (ago.),
#>         septiembre (sept.), octubre (oct.), noviembre (nov.),
#>         diciembre (dic.)
#> AM/PM:  a. m./p. m.
```
