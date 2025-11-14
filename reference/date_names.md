# Create or retrieve date names

When parsing dates, you often need to know how weekdays of the week and
months are represented as text. This pair of functions allows you to
either create your own, or retrieve from a standard list. The standard
list is derived from ICU (`http://site.icu-project.org`) via the stringi
package.

## Usage

``` r
date_names(mon, mon_ab = mon, day, day_ab = day, am_pm = c("AM", "PM"))

date_names_lang(language)

date_names_langs()
```

## Arguments

- mon, mon_ab:

  Full and abbreviated month names.

- day, day_ab:

  Full and abbreviated week day names. Starts with Sunday.

- am_pm:

  Names used for AM and PM.

- language:

  A BCP 47 locale, made up of a language and a region, e.g. `"en"` for
  American English. See `date_names_langs()` for a complete list of
  available locales.

## Examples

``` r
date_names_lang("en")
#> <date_names>
#> Days:   Sunday (Sun), Monday (Mon), Tuesday (Tue), Wednesday (Wed),
#>         Thursday (Thu), Friday (Fri), Saturday (Sat)
#> Months: January (Jan), February (Feb), March (Mar), April (Apr), May
#>         (May), June (Jun), July (Jul), August (Aug), September
#>         (Sep), October (Oct), November (Nov), December (Dec)
#> AM/PM:  AM/PM
date_names_lang("ko")
#> <date_names>
#> Days:   일요일 (일), 월요일 (월), 화요일 (화), 수요일 (수), 목요일
#>         (목), 금요일 (금), 토요일 (토)
#> Months: 1월, 2월, 3월, 4월, 5월, 6월, 7월, 8월, 9월, 10월, 11월, 12월
#> AM/PM:  오전/오후
date_names_lang("fr")
#> <date_names>
#> Days:   dimanche (dim.), lundi (lun.), mardi (mar.), mercredi (mer.),
#>         jeudi (jeu.), vendredi (ven.), samedi (sam.)
#> Months: janvier (janv.), février (févr.), mars (mars), avril (avr.),
#>         mai (mai), juin (juin), juillet (juil.), août (août),
#>         septembre (sept.), octobre (oct.), novembre (nov.),
#>         décembre (déc.)
#> AM/PM:  AM/PM
```
