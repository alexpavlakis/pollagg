% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/yapa.R
\name{yapa}
\alias{yapa}
\title{fit a yapa model}
\usage{
yapa(
  y,
  n,
  dates = NULL,
  all_dates = NULL,
  prior_pct = NULL,
  chains = 4,
  iter = 2000,
  ...
)
}
\arguments{
\item{y}{a matrix of poll respondent counts.}

\item{n}{a vector of poll sample sizes.}

\item{dates}{a vector of poll dates.}

\item{all_dates}{a vector of all dates to estimate the trend for. The default is the unique poll dates.}

\item{prior_pct}{a vector of prior percents on the trend for each option. The default is NULL and estimated from the first poll in the series.}

\item{chains}{mcmc chains passed to stan.}

\item{iter}{iter passed to stan.}

\item{...}{other arguments}
}
\description{
fit a yapa model
}
\section{Model Output}{
 Yapa returns an object of class yapafit, which is a list containing:
\itemize{
\item \code{trend} a \code{data.frame} of the underlying trend and it's 90\% uncertainty interval;
\item \code{pct} a \code{data.frame} of the smoothed poll averages and their 90\% uncertainty intervals;
\item \code{polls} a \code{data.frame} of the raw polling data on which the model is built;
\item \code{stanfit} the result of the call to Stan;
\item \code{params} the extracted stanfit object;
\item other elements from the model arguments and results.
}

\code{plot.yapafit} plots the fitted trend along with raw polls (faint dots) and smoothed polls (solid dots).
}

