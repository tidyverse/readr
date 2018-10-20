#' Read a Google Sheet into a tibble
#'
#' @description
#' Export a Google Sheet as `.csv` and read with [read_csv()].
#'
#' @param url URL (address) of the Google Sheet to read. To read a specific
#'   sheet, switch to this sheet and copy its full URL from the address bar;
#'   it will include a sheet identifier (that looks like `gid=12345`) and
#'   read that sheet only.
#' @param range A character string defining a range of data to read. All
#'   valid Google Sheet ranges are acceptable: "A1:C5" reads lines 1 to 5 in
#'   columns A to C; "A3:C" or "A:C3" read from line 3 onwards, in columnes
#'   A to C; "A:C" reads all lines in columns A to C.
#' @param ... Passed to [read_csv()].
#'
#' @details For this to work, the Google Sheet needs to be either public or
#'   accessible through its link: `File > Share > Anyone with the link can
#'   view` (at least).
#'
#'   The link to export the sheet as `.csv` is built from the URL (by
#'   substituting `/export?format=csv` to `/edit` in the URL) and the data
#'   is read from there. This does not use the "Google Visualization API"
#'   and therefore cannot read data resulting from SQL-like queries built
#'   with its [Query
#'   Language](https://developers.google.com/chart/interactive/docs/querylanguage).
#'   Using this API would be more powerful but requires to provide the name
#'   of the sheet rather than extracting the sheet identifier from the URL.
#'
#' @return A [tibble()]. If there are parsing problems, a warning tells you
#'   how many, and you can retrieve the details with
#'   \code{\link{problems}()}.
#'
#' @export
#' @examples
#' # An example Google Sheet with two sheets is used.
#' # The sheets respectively contain the `mtcars` and `iris` datasets
#'
#' # URL to the first sheet
#' url <- "https://docs.google.com/spreadsheets/d/1bkLTSMLobkBjIPY0HaLJjW2J_shER3kTXP6SoXdER0k/edit#gid=0"
#' # Read it in full
#' read_googlesheet(url)
#' # or just a piece of it
#' read_googlesheet(url, range="A1:C5")
#' # and pass additional arguments to read_csv()
#' read_googlesheet(url, col_types=cols())
#' read_googlesheet(url, skip=10, col_names=FALSE)
#'
#' # Read the second sheet
#' url <- "https://docs.google.com/spreadsheets/d/1bkLTSMLobkBjIPY0HaLJjW2J_shER3kTXP6SoXdER0k/edit#gid=670137368"
#' read_googlesheet(url, col_types=cols())
#'
#' # You can also use the shorthand
#' read_gs(url, col_types=cols())
read_googlesheet <- function(url, range=NULL, ...) {
  # check that the URL is from Google Docs
  if ( ! grepl("^http(s){0,1}://docs.google.com/spreadsheets", url) ) {
    stop("The provided URL does not look like a Google Sheet URL.
  It should start with docs.google.com/spreadsheets")
  }

  # convert the URL into the csv export URL
  # NB: the original URL may include the sheet id,
  #     which is therefore propagated to the export URL
  if ( grepl("/edit", url) ) {
    # regular "edit" / "share" URLs
    url <- sub("/edit(#|\\?){0,1}", "/export?format=csv&", url)
  } else {
    # plain URLs, with or without ending /
    url <- paste0(url, "/export?format=csv")
    # in case the ending / was already present
    url <- gsub("//export", "/export", url)
  }

  # add a range to export, if needed
  if (! is.null(range)) {
    url <- paste0(url , "&range=", range)
  }

  # read the data
  read_csv(url, ...)
}

#' @rdname read_googlesheet
#' @export
read_gs <- read_googlesheet
