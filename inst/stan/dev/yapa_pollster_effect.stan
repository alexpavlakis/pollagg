data {
  int n_days;
  int n_polls;
  int n_options;
  int n_pollsters;
  int y[n_polls, n_options];
  int n[n_polls];
  int day_id[n_polls];
  int pollster_id[n_polls];
  matrix[n_pollsters, n_options] pollster_effect_prior;
  real<lower = 0> poll_dev_sigma;
  real<lower = 0> trend_dev_sigma;
}
parameters {
  matrix<lower = 0, upper = 1>[n_polls, n_options] theta;
  matrix[n_days, n_options] delta;
  matrix[n_pollsters, n_options] pollster_effect;
  real<lower = 0, upper = 1> intercept[n_options];
  real<lower = 0> theta_sigma;
  real<lower = 0> delta_sigma;
}
transformed parameters {
  matrix[n_days, n_options] mu;
  for(o in 1:n_options) {
    mu[, o] = cumulative_sum(delta[, o]) + intercept[o];
    // enforce <lower = 0, upper = 1>
    for(i in 1:n_days) {
      if(mu[i, o] < 0) mu[i, o] = 0;
      if(mu[i, o] > 1) mu[i, o] = 1;
    }
  }
}
model {
  // priors
  intercept ~ normal(0.5, 1);
  theta_sigma  ~ normal(0, poll_dev_sigma);
  delta_sigma ~ normal(0, trend_dev_sigma);
  for(o in 1:n_options) {
    delta[1, o] ~ normal(0, 1);
    for(i in 2:n_days) {
      delta[i, o] ~ normal(delta[i-1, o], delta_sigma);
    }
  }
  for(p in 1:n_pollsters) {
    for(o in 1:n_options) {
      pollster_effect[p, o] ~ normal(pollster_effect_prior[p, o], 0.01);
    }
  }
  // model
  for(o in 1:n_options) {
    for(p in 1:n_polls) {
      y[p, o] ~ binomial(n[p], theta[p, o]);
      theta[p, o] ~ normal(mu[day_id[p], o] + pollster_effect[pollster_id[p], o], theta_sigma);
    }
  }
}
