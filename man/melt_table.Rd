% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/melt_table.R
\name{melt_table}
\alias{melt_table}
\alias{melt_table2}
\title{Return melted data for each token in a whitespace-separated file}
\usage{
melt_table(
  file,
  locale = default_locale(),
  na = "NA",
  skip = 0,
  n_max = Inf,
  guess_max = min(n_max, 1000),
  progress = show_progress(),
  comment = "",
  skip_empty_rows = FALSE
)

melt_table2(
  file,
  locale = default_locale(),
  na = "NA",
  skip = 0,
  n_max = Inf,
  progress = show_progress(),
  comment = "",
  skip_empty_rows = FALSE
)
}
\arguments{
\item{file}{Either a path to a file, a connection, or literal data
(either a single string or a raw vector).

Files ending in \code{.gz}, \code{.bz2}, \code{.xz}, or \code{.zip} will
be automatically uncompressed. Files starting with \verb{http://},
\verb{https://}, \verb{ftp://}, or \verb{ftps://} will be automatically
downloaded. Remote gz files can also be automatically downloaded and
decompressed.

Literal data is most useful for examples and tests. To be recognised as
literal data, the input must be either wrapped with \code{I()}, be a string
containing at least one new line, or be a vector containing at least one
string with a new line.

Using a value of \code{\link[=clipboard]{clipboard()}} will read from the system clipboard.}

\item{locale}{The locale controls defaults that vary from place to place.
The default locale is US-centric (like R), but you can use
\code{\link[=locale]{locale()}} to create your own locale that controls things like
the default time zone, encoding, decimal mark, big mark, and day/month
names.}

\item{na}{Character vector of strings to interpret as missing values. Set this
option to \code{character()} to indicate no missing values.}

\item{skip}{Number of lines to skip before reading data.}

\item{n_max}{Maximum number of lines to read.}

\item{guess_max}{Maximum number of lines to use for guessing column types.
Will never use more than the number of lines read.
See \code{vignette("column-types", package = "readr")} for more details.}

\item{progress}{Display a progress bar? By default it will only display
in an interactive session and not while knitting a document. The automatic
progress bar can be disabled by setting option \code{readr.show_progress} to
\code{FALSE}.}

\item{comment}{A string used to identify comments. Any text after the
comment characters will be silently ignored.}

\item{skip_empty_rows}{Should blank rows be ignored altogether? i.e. If this
option is \code{TRUE} then blank rows will not be represented at all.  If it is
\code{FALSE} then they will be represented by \code{NA} values in all the columns.}
}
\description{
\ifelse{html}{\href{https://lifecycle.r-lib.org/articles/stages.html#superseded}{\figure{lifecycle-superseded.svg}{options: alt='[Superseded]'}}}{\strong{[Superseded]}}
This function has been superseded in readr and moved to \href{https://r-lib.github.io/meltr/}{the meltr package}.

For certain non-rectangular data formats, it can be useful to parse the data
into a melted format where each row represents a single token.

\code{melt_table()} and \code{melt_table2()} are designed to read the type of textual
data where each column is separated by one (or more) columns of space.

\code{melt_table2()} allows any number of whitespace characters between columns,
and the lines can be of different lengths.

\code{melt_table()} is more strict, each line must be the same length,
and each field is in the same position in every line. It first finds empty
columns and then parses like a fixed width file.
}
\examples{
fwf <- readr_example("fwf-sample.txt")
writeLines(read_lines(fwf))
melt_table(fwf)

ws <- readr_example("whitespace-sample.txt")
writeLines(read_lines(ws))
melt_table2(ws)
}
\seealso{
\code{\link[=melt_fwf]{melt_fwf()}} to melt fixed width files where each column
is not separated by whitespace. \code{melt_fwf()} is also useful for reading
tabular data with non-standard formatting.  \code{\link[=read_table]{read_table()}} is the
conventional way to read tabular data from whitespace-separated files.
}
