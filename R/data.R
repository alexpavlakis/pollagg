#' Polls for the 2008 presidential race between Obama and McCain.
#'
#' A dataset containing the pollster, date, sample size, and results for Obama and McCain in 292 polls.
#'
#' @format A data frame with 292 rows and 5 variables:
#' \describe{
#'   \item{pollster}{pollster}
#'   \item{poll_end}{the end date}
#'   \item{n}{sample size}
#'   \item{`McCain (R)`}{total respondents who said McCain}
#'   \item{`Obama (D)`}{total respondents who said Obama}
#' }
#' @source \url{www.realclearpolitics.com}
"obama_mccain_polls"



#' GSS results for the "grass" question.
#'
#' A dataset containing the responses to the General Social Survey for the question "Should marijuana be made legal?"
#'
#' @format A data frame with 292 rows and 5 variables:
#' \describe{
#'   \item{year}{year}
#'   \item{n}{sample size}
#'   \item{legal}{total respondents who said legal}
#'   \item{illegal}{total respondents who said illegal}
#' }
#' @source \url{www.https://gss.norc.org/}
"grass_gss"
