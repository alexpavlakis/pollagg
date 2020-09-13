
<!-- README.md is generated from README.Rmd. Please edit that file -->

# pollagg

<!-- badges: start -->

<!-- badges: end -->

`pollagg` is a tool for researchers who want to understand trends in
public opinion from many noisy polls or surveys.

## Installation

You can install the development version of `pollagg` with

``` r
devtools::install_github("alexpavlakis/pollagg")
```

# Examples

The function `yapa` (yet another poll aggregator) takes three main
arguments:

1.  `y` is a matrix of counts for responses (columns) for each poll or
    survey (rows);
2.  `n` is a vector of the total counts for each poll or survey;
3.  `poll_dates` is a vector of dates (can be days or integers) for when
    each poll or survey was conducted;

An additional argument `dates` is available if you want to produce
specific estimates for dates other than survey dates. For example, if
you conduct surveys on the first of each month but want to estimate
hypothetical results if you had conducted them on the 15th instead.

``` r
library(pollagg)
suppressMessages(library(dplyr))
library(ggplot2)

options(mc.cores = parallel::detectCores())
rstan::rstan_options(auto_write = TRUE)

# General election polls - Obama vs McCain 2008
head(obama_mccain_polls)
#> # A tibble: 6 x 5
#>   pollster         poll_end       n `McCain (R)` `Obama (D)`
#>   <chr>            <date>     <dbl>        <dbl>       <dbl>
#> 1 IBD/TIPP         2008-01-04   951          456         342
#> 2 Rasmussen        2008-01-06   800          368         344
#> 3 CNN              2008-01-10   840          403         412
#> 4 Battleground     2008-01-11   500          255         195
#> 5 Hotline/FD       2008-01-12   803          313         329
#> 6 USA Today/Gallup 2008-01-13  1106          553         498
```

In this example we aggregate all polls conducted of the 2008
presidential race between January 1st and election day 2008.

``` r

y <- select(obama_mccain_polls, `McCain (R)`, `Obama (D)`)
n <- obama_mccain_polls$n
poll_dates <- obama_mccain_polls$poll_end

fit_polls <- yapa(y = y, n = n, poll_dates = poll_dates)
```

``` r
plot(fit_polls, size = 0.5) + 
  ylim(0.3, 0.6) +
  scale_x_date(date_breaks = '1 month') +
  scale_fill_manual(values = c('red', 'blue')) +
  scale_color_manual(values = c('red', 'blue')) +
  theme(axis.text.x = element_text(angle = 45, hjust = 1),
        plot.subtitle = element_text(size = 9),
        legend.position = 'bottom') +
  labs(x = NULL, y = NULL, title = 'General Election: McCain vs. Obama',
       subtitle = 'polls (faint dots), modeled polls (bold dots), trend (line), and trend uncertainty (faded ribbon)', col = NULL, fill = NULL)
```

<img src="man/figures/README-obama_mccain_res-1.png" width="100%" />

In this example we analyze the trends in responses to the General Social
Survey question regarding the legality of marijuana between 1973 and
2018, and we estimate what responses might be in 2022 based on those
trends.

``` r
head(grass_gss)
#> # A tibble: 6 x 4
#>    year illegal legal     n
#>   <int>   <dbl> <dbl> <dbl>
#> 1  1973    1184   290  1474
#> 2  1975    1111   303  1414
#> 3  1976    1033   417  1450
#> 4  1978    1029   447  1476
#> 5  1980    1064   365  1429
#> 6  1983    1230   322  1552
```

``` r
y <- select(grass_gss, legal, illegal)
n <- grass_gss$n
poll_dates <- grass_gss$year

fit_gss <- yapa(y = y, n = n, poll_dates = poll_dates, dates = c(poll_dates, 2022))
```

``` r
plot(fit_gss) + 
  ylim(0, 1) +
  scale_fill_manual(values = c('darkgrey', 'darkgreen')) +
  scale_color_manual(values = c('darkgrey', 'darkgreen')) +
  theme(axis.text.x = element_text(angle = 45, hjust = 1),
        plot.subtitle = element_text(size = 9),
        legend.position = 'bottom') +
  labs(x = NULL, y = NULL, title = 'Should marijuana be made legal?',
       subtitle = 'survey results (faint dots), modeled survey results (bold dots), trend (line), and trend uncertainty (faded ribbon)', col = NULL, fill = NULL)
```

<img src="man/figures/README-gss_res-1.png" width="100%" />

# Model

  
![
\\begin{align\*}
y\_{p, o} &\\sim Binomial(n\_p, \\theta\_{p, o}) \\\\
\\theta\_{p, o} &\\sim Normal(\\mu\_{d(p), o}, \\sigma^\\theta) \\\\
\\mu\_{d, o} &= \\sum\_{t \< d} \\delta\_{t, o} + \\alpha\_o \\\\
\\delta\_{d, o} &\\sim Normal(\\delta\_{d-1, o}, \\sigma^\\delta)
\\end{align\*}
](https://latex.codecogs.com/png.latex?%0A%5Cbegin%7Balign%2A%7D%0Ay_%7Bp%2C%20o%7D%20%26%5Csim%20Binomial%28n_p%2C%20%5Ctheta_%7Bp%2C%20o%7D%29%20%5C%5C%0A%5Ctheta_%7Bp%2C%20o%7D%20%26%5Csim%20Normal%28%5Cmu_%7Bd%28p%29%2C%20o%7D%2C%20%5Csigma%5E%5Ctheta%29%20%5C%5C%0A%5Cmu_%7Bd%2C%20o%7D%20%26%3D%20%5Csum_%7Bt%20%3C%20d%7D%20%5Cdelta_%7Bt%2C%20o%7D%20%2B%20%5Calpha_o%20%5C%5C%0A%5Cdelta_%7Bd%2C%20o%7D%20%26%5Csim%20Normal%28%5Cdelta_%7Bd-1%2C%20o%7D%2C%20%5Csigma%5E%5Cdelta%29%0A%5Cend%7Balign%2A%7D%0A
"
\\begin{align*}
y_{p, o} &\\sim Binomial(n_p, \\theta_{p, o}) \\\\
\\theta_{p, o} &\\sim Normal(\\mu_{d(p), o}, \\sigma^\\theta) \\\\
\\mu_{d, o} &= \\sum_{t \< d} \\delta_{t, o} + \\alpha_o \\\\
\\delta_{d, o} &\\sim Normal(\\delta_{d-1, o}, \\sigma^\\delta)
\\end{align*}
")
