#' fit a yapa model
#'
#' @param y a matrix of poll respondent counts.
#' @param n a vector of poll sample sizes.
#' @param dates a vector of poll dates.
#'
#' @import methods
#' @import Rcpp
#' @import ggplot2
#' @import dplyr
#' @importFrom rstan sampling
#' @useDynLib pollagg, .registration = TRUE
#'
#' @export
yapa <- function(y, n, poll_dates, dates = NULL) {

  if(!all.equal(nrow(y), length(n), length(poll_dates))) {
    stop("nrow(y) must equal length(n) and length(poll_dates")
  }
  if(!all(rowSums(y) < n)) {
    stop("rowSums(y) must be less than n")
  }

  if(is.null(dates)) dates <- poll_dates

  model_data <- list(
    n_polls = nrow(y),
    n_options = ncol(y),
    n_days = length(unique(dates)),
    y = y,
    n = n,
    day_id = match(poll_dates, unique(dates))
  )

  # Fit model
  fit <- yapa.fit(model_data)
  ef <- rstan::extract(fit)

  # Extract trend
  trend_temp <- list()
  for(i in 1:model_data$n_options) {
    trend_temp[[i]] <- data.frame(
      date = unique(dates),
      answer = factor(ifelse(!is.null(names(y)[i]), names(y)[i], i)),
      mean = apply(ef$mu[, 1:model_data$n_days, i], 2, mean),
      lower = apply(ef$mu[, 1:model_data$n_days, i], 2, quantile, 0.05),
      upper = apply(ef$mu[, 1:model_data$n_days, i], 2, quantile, 0.95)
    )
  }
  trend <- do.call(rbind, trend_temp)

  # Extract poll averages
  pct_tmp <- list()
  for(i in 1:model_data$n_options) {
    pct_tmp[[i]] <- data.frame(
      date = poll_dates,
      answer = factor(ifelse(!is.null(names(y)[i]), names(y)[i], i)),
      mean = apply(ef$theta[, 1:model_data$n_polls, i], 2, mean),
      lower = apply(ef$theta[, 1:model_data$n_polls, i], 2, quantile, 0.05),
      upper = apply(ef$theta[, 1:model_data$n_polls, i], 2, quantile, 0.95)
    )
  }
  pct <- do.call(rbind, pct_tmp)

  # Format poll data
  polls_tmp <- list()
  for(i in 1:model_data$n_options) {
    polls_tmp[[i]] <- data.frame(
      date = poll_dates,
      answer = factor(ifelse(!is.null(names(y)[i]), names(y)[i], i)),
      n = n,
      y = dplyr::pull(dplyr::as_tibble(y)[, i])
    )
  }
  polls <- do.call(rbind, polls_tmp)
  polls$pct <- polls$y/polls$n

  out <- list(
    stanfit = fit,
    trend = trend,
    pct = pct,
    data = polls

  )
  structure(out, class = 'yapafit')

}


yapa.fit <- function(model_data, ...) {
  suppressWarnings(
    #fit <- stan("inst/stan/yapa.stan", data  = model_data)
    fit <- rstan::sampling(stanmodels$yapa, data = model_data)
  )
  return(fit)
}


plot_yapa <- function(yapafit, size = 1, ...) {

  p <- ggplot() +
    geom_point(data = yapafit$data,
               aes(x = date, y = pct, col = answer),
               alpha = 0.2, size = size) +
    geom_point(data = yapafit$pct,
               aes(x = date, y = mean, col = answer),
               alpha = 1, size = size) +
    geom_line(data = yapafit$trend,
              aes(x = date, y = mean, ymin = lower, ymax = upper, col = answer,
                  fill = answer), lty = 2) +
    geom_ribbon(data = yapafit$trend,
                aes(x = date, y = mean, ymin = lower, ymax = upper, col = answer,
                    fill = answer),
                col = NA, alpha = 0.1) +
    theme_minimal()
  p
}

#' plot a yapa model
#'
#' @param x a yapafit model
#' @export
plot.yapafit <- function(x, ...) {
  suppressWarnings(
    plot_yapa(x, ...)
  )
}
