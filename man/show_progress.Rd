% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/utils.R
\name{show_progress}
\alias{show_progress}
\title{Determine whether progress bars should be shown}
\usage{
show_progress()
}
\description{
By default, readr shows progress bars. However, progress reporting is
suppressed if any of the following conditions hold:
\itemize{
\item The bar is explicitly disabled by setting
\code{options(readr.show_progress = FALSE)}.
\item The code is run in a non-interactive session, as determined by
\code{\link[rlang:is_interactive]{rlang::is_interactive()}}.
\item The code is run in an RStudio notebook chunk, as determined by
\code{getOption("rstudio.notebook.executing")}.
}
}
