data {
  int n_days;
  int n_polls;
  int n_options;
  int y[n_polls, n_options];
  int n[n_polls];
  int day_id[n_polls];
  real<lower = 0, upper = 1> prior_pct[n_options];
}
parameters {
  matrix<lower = 0, upper = 1>[n_polls, n_options] theta;
  matrix[n_days, n_options] delta;
  real<lower = 0, upper = 1> alpha[n_options];
  real<lower = 0> theta_sigma;
  real<lower = 0> delta_sigma;
}
transformed parameters {
  matrix[n_days, n_options] mu;
  for(o in 1:n_options) {
    mu[, o] = cumulative_sum(delta[, o]) + alpha[o];
    // enforce <lower = 0, upper = 1>
    for(i in 1:n_days) {
      if(mu[i, o] < 0) mu[i, o] = 0;
      if(mu[i, o] > 1) mu[i, o] = 1;
    }
  }
}
model {
  // priors
  alpha ~ normal(prior_pct, 0.1);
  theta_sigma  ~ normal(0, 0.05);
  delta_sigma ~ normal(0, 0.05);
  for(o in 1:n_options) {
    delta[, o] ~ normal(0, delta_sigma);
  }
  // model
  for(o in 1:n_options) {
    for(p in 1:n_polls) {
      y[p, o] ~ binomial(n[p], theta[p, o]);
      theta[p, o] ~ normal(mu[day_id[p], o], theta_sigma);
    }
  }
}

