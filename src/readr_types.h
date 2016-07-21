#pragma once

#include "Rcpp.h"
#include "TokenizerLine.h"
#include "Source.h"

typedef Rcpp::XPtr<TokenizerLine,Rcpp::PreserveStorage> XPtrTokenizerLine;
typedef Rcpp::XPtr<Source, Rcpp::PreserveStorage> XPtrSource;
