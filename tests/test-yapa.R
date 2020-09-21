library(pollagg)

y <- matrix(c(10, 900, 50, 50), ncol = 2, byrow = TRUE)
n <- rowSums(y)
fit <- yapa(y = y, n = n, dates = NULL, iter = 1000, chains = 3)

if(!all(dim(fit$params$theta) == c(1500, 2, 2))) {
  stop("yapa is not returning results as expected")
}
