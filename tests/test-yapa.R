library(pollagg)

# Fit a model
y <- matrix(c(10, 900, 50, 50), ncol = 2, byrow = TRUE)
n <- rowSums(y)
fit <- yapa(y = y, n = n, dates = NULL, iter = 1000, chains = 3)

# Test model fit
if(!all(dim(fit$params$theta) == c(1500, 2, 2))) {
  stop("yapa is not returning results as expected")
}

# Test plot
p <- plot(fit)
if(!"ggplot" %in% class(p)) {
  stop("plot.yapafit is not returning an object of class ggplot2")
}

# Test summary
sf <- summary(fit)
if(!identical(names(sf), c("delta", "polls", "pct", "trend"))) {
  stop("summary.fit is not summarising the four output data.frames (delta, polls, pct, and trend)")
}
