#' fit a yapa model
#'
#' @param y a matrix of poll respondent counts.
#' @param n a vector of poll sample sizes.
#' @param dates a vector of poll dates.
#' @param all_dates a vector of all dates to estimate the trend for. The default is the unique poll dates.
#' @param prior_pct a vector of prior percents on the trend for each option.
#' @param chains mcmc chains passed to stan.
#' @param iter iter passed to stan.
#' @param ... Other arguments
#'
#' @import methods
#' @import Rcpp
#' @import ggplot2
#' @importFrom rstan sampling
#' @importFrom stats quantile
#' @useDynLib pollagg, .registration = TRUE
#'
#' @export
yapa <- function(y, n, dates = NULL, all_dates = NULL, prior_pct = NULL,
                 chains = 4, iter = 2000, ...) {
  m <- list(
    y = as.matrix(y),
    n = as.matrix(n),
    dates = dates,
    all_dates = all_dates,
    prior_pct = prior_pct,
    chains = chains,
    iter = iter
  )
  m <- validate(m)
  m <- fit.yapa(m)
  return(m)
}

#' Validates input to yapa model
#'
#' @param m list of inputs.
#'
#' @return list of inputs if they have passed validation
#'
#' @keywords internal
validate <- function(m) {
  if(is.null(m$dates)) m$dates <- rep(1, nrow(m$y))
  if(is.null(m$all_dates)) m$all_dates <- unique(m$dates)
  if(is.null(m$prior_pct)) m$prior_pct <- m$y[1, ]/m$n[1]
  if(!all.equal(nrow(m$y), length(m$n), length(m$dates))) {
    stop("nrow(y) must equal length(n) and length(dates")
  }
  if(!all(rowSums(m$y) <= m$n)) {
    stop("rowSums(y) must be less than or equal to n")
  }
  if(!(length(m$prior_pct) == ncol(m$y))) {
    stop("prior_pct (prior on trend) must be NULL or equal to ncol(y)")
  }
  return(m)
}

#' Fit the model
#'
#' This sets m$params to contain the fitted model parameters.
#'
#' @param m list of inputs to the model
#' @param ... Additional arguments
#'
#' @export
fit.yapa <- function(m, ...) {

  model_data <- list(
    n_polls = nrow(m$y),
    n_options = ncol(m$y),
    n_days = length(unique(m$all_dates)),
    y = m$y,
    n = m$n,
    prior_pct = m$prior_pct,
    day_id = as.matrix(match(m$dates, unique(m$dates)))
  )
  args <- list(
    object = stanmodels$yapa,
    data = model_data,
    iter = m$iter,
    chains = m$chains
  )
  args <- utils::modifyList(args, list(...))
  m$stan.fit <- suppressWarnings(
    do.call(rstan::sampling, args)
  )

  m$params <- rstan::extract(m$stan.fit)
  m$trend <- make_output_dataframe(var = m$params$mu,
                                   nrow = model_data$n_days,
                                   ncol = model_data$n_options,
                                   y = m$y, dates = m$all_dates)
  m$pct <- make_output_dataframe(var = m$params$theta,
                                 nrow = model_data$n_polls,
                                 ncol = model_data$n_options,
                                 y = m$y, dates = m$dates)
  m$delta <- make_output_dataframe(var = m$params$delta,
                                   nrow = model_data$n_days,
                                   ncol = model_data$n_options,
                                   y = m$y, dates = m$all_dates)
  m$polls <- tidy_polls(m$y, m$n, m$dates)
  structure(m, class = 'yapafit')
}

#' Helper function for formatting output
#'
#' @param var the outcome variable.
#' @param nrow the number of observations.
#' @param ncol the number of options.
#' @param y the poll counts matrix.
#' @param dates the dates variable.
#'
#' @return dataframe of tidied outputs
#'
#' @keywords internal
make_output_dataframe <- function(var, nrow, ncol, y, dates) {
  tmp <- list()
  for(i in 1:ncol) {
    samples <- matrix(var[, 1:nrow, i], ncol = nrow)
    tmp[[i]] <- data.frame(
      date = dates,
      answer = factor(ifelse(!is.null(colnames(y)[i]), colnames(y)[i], i)),
      mean = apply(samples, 2, mean),
      lower = apply(samples, 2, 'quantile', 0.05),
      upper = apply(samples, 2, 'quantile', 0.95),
      row.names = NULL
    )
  }
  res <- do.call(rbind, tmp)
  res
}

#' Helper function for formatting output
#'
#' @param y the poll counts matrix.
#' @param n the poll sample sizes.
#' @param dates the dates variable.
#'
#' @return dataframe of tidied outputs
#'
#' @keywords internal
tidy_polls <- function(y, n, dates) {
  tmp <- list()
  for(i in 1:ncol(y)) {
    tmp[[i]] <- data.frame(
      date = dates,
      answer = factor(ifelse(!is.null(colnames(y)[i]), colnames(y)[i], i)),
      n = n,
      y = y[, i],
      row.names = NULL
    )
  }
  polls <- do.call(rbind, tmp)
  polls$pct <- polls$y/polls$n
  polls[order(polls$answer, polls$date), ]
}

#' Function to plot yapa trend, modeled averages, and raw data.
#'
#' @param yapafit an object of class yapafit
#'
#' @return a ggplot
#'
#' @keywords internal
plot_yapa <- function(yapafit, size = 1, se = TRUE,
                      poll_alpha = 0.2, model_alpha = 1,
                      se_alpha = 0.1, ...) {
  if(!se) se_alpha <- 0
  p <- ggplot() +
    geom_point(data = yapafit$polls,
               aes(x = date, y = pct, col = answer),
               alpha = poll_alpha, size = size) +
    geom_point(data = yapafit$pct,
               aes(x = date, y = mean, col = answer),
               alpha = model_alpha, size = size) +
    geom_line(data = yapafit$trend,
              aes(x = date, y = mean, col = answer), lty = 2) +
    geom_ribbon(data = yapafit$trend,
                aes(x = date, y = mean, ymin = lower, ymax = upper,
                    col = answer, fill = answer),
                col = NA, alpha = se_alpha) +
    theme_minimal() +
    guides(fill = FALSE)
  p
}

#' plot a yapa model
#'
#' @param x a yapafit model.
#' @param ... additional arguments.
#'
#' @export
plot.yapafit <- function(x, ...) {
  suppressWarnings(
    plot_yapa(x, ...)
  )
}

