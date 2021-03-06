% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/edition.R
\name{with_edition}
\alias{with_edition}
\alias{local_edition}
\title{Temporarily change the active readr edition}
\usage{
with_edition(edition, code)

local_edition(edition, env = parent.frame())
}
\arguments{
\item{edition}{Should be a single integer.}

\item{code}{Code to run with the changed edition.}

\item{env}{Environment that controls scope of changes. For expert use only.}
}
\description{
\code{with_edition()} allows you to change the active edition of readr for a given block of code.
\code{local_edition()} allows you to change the active edition of readr until the end of the current function or file.
}
