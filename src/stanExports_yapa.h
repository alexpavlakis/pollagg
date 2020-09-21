// Generated by rstantools.  Do not edit by hand.

/*
    yapar is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    yapar is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with yapar.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef MODELS_HPP
#define MODELS_HPP
#define STAN__SERVICES__COMMAND_HPP
#include <rstan/rstaninc.hpp>
// Code generated by Stan version 2.21.0
#include <stan/model/model_header.hpp>
namespace model_yapa_namespace {
using std::istream;
using std::string;
using std::stringstream;
using std::vector;
using stan::io::dump;
using stan::math::lgamma;
using stan::model::prob_grad;
using namespace stan::math;
static int current_statement_begin__;
stan::io::program_reader prog_reader__() {
    stan::io::program_reader reader;
    reader.add_event(0, 0, "start", "model_yapa");
    reader.add_event(45, 43, "end", "model_yapa");
    return reader;
}
#include <stan_meta_header.hpp>
class model_yapa
  : public stan::model::model_base_crtp<model_yapa> {
private:
        int n_days;
        int n_polls;
        int n_options;
        std::vector<std::vector<int> > y;
        std::vector<int> n;
        std::vector<int> day_id;
        std::vector<double> prior_pct;
public:
    model_yapa(stan::io::var_context& context__,
        std::ostream* pstream__ = 0)
        : model_base_crtp(0) {
        ctor_body(context__, 0, pstream__);
    }
    model_yapa(stan::io::var_context& context__,
        unsigned int random_seed__,
        std::ostream* pstream__ = 0)
        : model_base_crtp(0) {
        ctor_body(context__, random_seed__, pstream__);
    }
    void ctor_body(stan::io::var_context& context__,
                   unsigned int random_seed__,
                   std::ostream* pstream__) {
        typedef double local_scalar_t__;
        boost::ecuyer1988 base_rng__ =
          stan::services::util::create_rng(random_seed__, 0);
        (void) base_rng__;  // suppress unused var warning
        current_statement_begin__ = -1;
        static const char* function__ = "model_yapa_namespace::model_yapa";
        (void) function__;  // dummy to suppress unused var warning
        size_t pos__;
        (void) pos__;  // dummy to suppress unused var warning
        std::vector<int> vals_i__;
        std::vector<double> vals_r__;
        local_scalar_t__ DUMMY_VAR__(std::numeric_limits<double>::quiet_NaN());
        (void) DUMMY_VAR__;  // suppress unused var warning
        try {
            // initialize data block variables from context__
            current_statement_begin__ = 2;
            context__.validate_dims("data initialization", "n_days", "int", context__.to_vec());
            n_days = int(0);
            vals_i__ = context__.vals_i("n_days");
            pos__ = 0;
            n_days = vals_i__[pos__++];
            current_statement_begin__ = 3;
            context__.validate_dims("data initialization", "n_polls", "int", context__.to_vec());
            n_polls = int(0);
            vals_i__ = context__.vals_i("n_polls");
            pos__ = 0;
            n_polls = vals_i__[pos__++];
            current_statement_begin__ = 4;
            context__.validate_dims("data initialization", "n_options", "int", context__.to_vec());
            n_options = int(0);
            vals_i__ = context__.vals_i("n_options");
            pos__ = 0;
            n_options = vals_i__[pos__++];
            current_statement_begin__ = 5;
            validate_non_negative_index("y", "n_polls", n_polls);
            validate_non_negative_index("y", "n_options", n_options);
            context__.validate_dims("data initialization", "y", "int", context__.to_vec(n_polls,n_options));
            y = std::vector<std::vector<int> >(n_polls, std::vector<int>(n_options, int(0)));
            vals_i__ = context__.vals_i("y");
            pos__ = 0;
            size_t y_k_0_max__ = n_polls;
            size_t y_k_1_max__ = n_options;
            for (size_t k_1__ = 0; k_1__ < y_k_1_max__; ++k_1__) {
                for (size_t k_0__ = 0; k_0__ < y_k_0_max__; ++k_0__) {
                    y[k_0__][k_1__] = vals_i__[pos__++];
                }
            }
            current_statement_begin__ = 6;
            validate_non_negative_index("n", "n_polls", n_polls);
            context__.validate_dims("data initialization", "n", "int", context__.to_vec(n_polls));
            n = std::vector<int>(n_polls, int(0));
            vals_i__ = context__.vals_i("n");
            pos__ = 0;
            size_t n_k_0_max__ = n_polls;
            for (size_t k_0__ = 0; k_0__ < n_k_0_max__; ++k_0__) {
                n[k_0__] = vals_i__[pos__++];
            }
            current_statement_begin__ = 7;
            validate_non_negative_index("day_id", "n_polls", n_polls);
            context__.validate_dims("data initialization", "day_id", "int", context__.to_vec(n_polls));
            day_id = std::vector<int>(n_polls, int(0));
            vals_i__ = context__.vals_i("day_id");
            pos__ = 0;
            size_t day_id_k_0_max__ = n_polls;
            for (size_t k_0__ = 0; k_0__ < day_id_k_0_max__; ++k_0__) {
                day_id[k_0__] = vals_i__[pos__++];
            }
            current_statement_begin__ = 8;
            validate_non_negative_index("prior_pct", "n_options", n_options);
            context__.validate_dims("data initialization", "prior_pct", "double", context__.to_vec(n_options));
            prior_pct = std::vector<double>(n_options, double(0));
            vals_r__ = context__.vals_r("prior_pct");
            pos__ = 0;
            size_t prior_pct_k_0_max__ = n_options;
            for (size_t k_0__ = 0; k_0__ < prior_pct_k_0_max__; ++k_0__) {
                prior_pct[k_0__] = vals_r__[pos__++];
            }
            size_t prior_pct_i_0_max__ = n_options;
            for (size_t i_0__ = 0; i_0__ < prior_pct_i_0_max__; ++i_0__) {
                check_greater_or_equal(function__, "prior_pct[i_0__]", prior_pct[i_0__], 0);
                check_less_or_equal(function__, "prior_pct[i_0__]", prior_pct[i_0__], 1);
            }
            // initialize transformed data variables
            // execute transformed data statements
            // validate transformed data
            // validate, set parameter ranges
            num_params_r__ = 0U;
            param_ranges_i__.clear();
            current_statement_begin__ = 11;
            validate_non_negative_index("theta", "n_polls", n_polls);
            validate_non_negative_index("theta", "n_options", n_options);
            num_params_r__ += (n_polls * n_options);
            current_statement_begin__ = 12;
            validate_non_negative_index("delta", "n_days", n_days);
            validate_non_negative_index("delta", "n_options", n_options);
            num_params_r__ += (n_days * n_options);
            current_statement_begin__ = 13;
            validate_non_negative_index("alpha", "n_options", n_options);
            num_params_r__ += (1 * n_options);
            current_statement_begin__ = 14;
            num_params_r__ += 1;
            current_statement_begin__ = 15;
            num_params_r__ += 1;
        } catch (const std::exception& e) {
            stan::lang::rethrow_located(e, current_statement_begin__, prog_reader__());
            // Next line prevents compiler griping about no return
            throw std::runtime_error("*** IF YOU SEE THIS, PLEASE REPORT A BUG ***");
        }
    }
    ~model_yapa() { }
    void transform_inits(const stan::io::var_context& context__,
                         std::vector<int>& params_i__,
                         std::vector<double>& params_r__,
                         std::ostream* pstream__) const {
        typedef double local_scalar_t__;
        stan::io::writer<double> writer__(params_r__, params_i__);
        size_t pos__;
        (void) pos__; // dummy call to supress warning
        std::vector<double> vals_r__;
        std::vector<int> vals_i__;
        current_statement_begin__ = 11;
        if (!(context__.contains_r("theta")))
            stan::lang::rethrow_located(std::runtime_error(std::string("Variable theta missing")), current_statement_begin__, prog_reader__());
        vals_r__ = context__.vals_r("theta");
        pos__ = 0U;
        validate_non_negative_index("theta", "n_polls", n_polls);
        validate_non_negative_index("theta", "n_options", n_options);
        context__.validate_dims("parameter initialization", "theta", "matrix_d", context__.to_vec(n_polls,n_options));
        Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> theta(n_polls, n_options);
        size_t theta_j_2_max__ = n_options;
        size_t theta_j_1_max__ = n_polls;
        for (size_t j_2__ = 0; j_2__ < theta_j_2_max__; ++j_2__) {
            for (size_t j_1__ = 0; j_1__ < theta_j_1_max__; ++j_1__) {
                theta(j_1__, j_2__) = vals_r__[pos__++];
            }
        }
        try {
            writer__.matrix_lub_unconstrain(0, 1, theta);
        } catch (const std::exception& e) {
            stan::lang::rethrow_located(std::runtime_error(std::string("Error transforming variable theta: ") + e.what()), current_statement_begin__, prog_reader__());
        }
        current_statement_begin__ = 12;
        if (!(context__.contains_r("delta")))
            stan::lang::rethrow_located(std::runtime_error(std::string("Variable delta missing")), current_statement_begin__, prog_reader__());
        vals_r__ = context__.vals_r("delta");
        pos__ = 0U;
        validate_non_negative_index("delta", "n_days", n_days);
        validate_non_negative_index("delta", "n_options", n_options);
        context__.validate_dims("parameter initialization", "delta", "matrix_d", context__.to_vec(n_days,n_options));
        Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> delta(n_days, n_options);
        size_t delta_j_2_max__ = n_options;
        size_t delta_j_1_max__ = n_days;
        for (size_t j_2__ = 0; j_2__ < delta_j_2_max__; ++j_2__) {
            for (size_t j_1__ = 0; j_1__ < delta_j_1_max__; ++j_1__) {
                delta(j_1__, j_2__) = vals_r__[pos__++];
            }
        }
        try {
            writer__.matrix_unconstrain(delta);
        } catch (const std::exception& e) {
            stan::lang::rethrow_located(std::runtime_error(std::string("Error transforming variable delta: ") + e.what()), current_statement_begin__, prog_reader__());
        }
        current_statement_begin__ = 13;
        if (!(context__.contains_r("alpha")))
            stan::lang::rethrow_located(std::runtime_error(std::string("Variable alpha missing")), current_statement_begin__, prog_reader__());
        vals_r__ = context__.vals_r("alpha");
        pos__ = 0U;
        validate_non_negative_index("alpha", "n_options", n_options);
        context__.validate_dims("parameter initialization", "alpha", "double", context__.to_vec(n_options));
        std::vector<double> alpha(n_options, double(0));
        size_t alpha_k_0_max__ = n_options;
        for (size_t k_0__ = 0; k_0__ < alpha_k_0_max__; ++k_0__) {
            alpha[k_0__] = vals_r__[pos__++];
        }
        size_t alpha_i_0_max__ = n_options;
        for (size_t i_0__ = 0; i_0__ < alpha_i_0_max__; ++i_0__) {
            try {
                writer__.scalar_lub_unconstrain(0, 1, alpha[i_0__]);
            } catch (const std::exception& e) {
                stan::lang::rethrow_located(std::runtime_error(std::string("Error transforming variable alpha: ") + e.what()), current_statement_begin__, prog_reader__());
            }
        }
        current_statement_begin__ = 14;
        if (!(context__.contains_r("theta_sigma")))
            stan::lang::rethrow_located(std::runtime_error(std::string("Variable theta_sigma missing")), current_statement_begin__, prog_reader__());
        vals_r__ = context__.vals_r("theta_sigma");
        pos__ = 0U;
        context__.validate_dims("parameter initialization", "theta_sigma", "double", context__.to_vec());
        double theta_sigma(0);
        theta_sigma = vals_r__[pos__++];
        try {
            writer__.scalar_lb_unconstrain(0, theta_sigma);
        } catch (const std::exception& e) {
            stan::lang::rethrow_located(std::runtime_error(std::string("Error transforming variable theta_sigma: ") + e.what()), current_statement_begin__, prog_reader__());
        }
        current_statement_begin__ = 15;
        if (!(context__.contains_r("delta_sigma")))
            stan::lang::rethrow_located(std::runtime_error(std::string("Variable delta_sigma missing")), current_statement_begin__, prog_reader__());
        vals_r__ = context__.vals_r("delta_sigma");
        pos__ = 0U;
        context__.validate_dims("parameter initialization", "delta_sigma", "double", context__.to_vec());
        double delta_sigma(0);
        delta_sigma = vals_r__[pos__++];
        try {
            writer__.scalar_lb_unconstrain(0, delta_sigma);
        } catch (const std::exception& e) {
            stan::lang::rethrow_located(std::runtime_error(std::string("Error transforming variable delta_sigma: ") + e.what()), current_statement_begin__, prog_reader__());
        }
        params_r__ = writer__.data_r();
        params_i__ = writer__.data_i();
    }
    void transform_inits(const stan::io::var_context& context,
                         Eigen::Matrix<double, Eigen::Dynamic, 1>& params_r,
                         std::ostream* pstream__) const {
      std::vector<double> params_r_vec;
      std::vector<int> params_i_vec;
      transform_inits(context, params_i_vec, params_r_vec, pstream__);
      params_r.resize(params_r_vec.size());
      for (int i = 0; i < params_r.size(); ++i)
        params_r(i) = params_r_vec[i];
    }
    template <bool propto__, bool jacobian__, typename T__>
    T__ log_prob(std::vector<T__>& params_r__,
                 std::vector<int>& params_i__,
                 std::ostream* pstream__ = 0) const {
        typedef T__ local_scalar_t__;
        local_scalar_t__ DUMMY_VAR__(std::numeric_limits<double>::quiet_NaN());
        (void) DUMMY_VAR__;  // dummy to suppress unused var warning
        T__ lp__(0.0);
        stan::math::accumulator<T__> lp_accum__;
        try {
            stan::io::reader<local_scalar_t__> in__(params_r__, params_i__);
            // model parameters
            current_statement_begin__ = 11;
            Eigen::Matrix<local_scalar_t__, Eigen::Dynamic, Eigen::Dynamic> theta;
            (void) theta;  // dummy to suppress unused var warning
            if (jacobian__)
                theta = in__.matrix_lub_constrain(0, 1, n_polls, n_options, lp__);
            else
                theta = in__.matrix_lub_constrain(0, 1, n_polls, n_options);
            current_statement_begin__ = 12;
            Eigen::Matrix<local_scalar_t__, Eigen::Dynamic, Eigen::Dynamic> delta;
            (void) delta;  // dummy to suppress unused var warning
            if (jacobian__)
                delta = in__.matrix_constrain(n_days, n_options, lp__);
            else
                delta = in__.matrix_constrain(n_days, n_options);
            current_statement_begin__ = 13;
            std::vector<local_scalar_t__> alpha;
            size_t alpha_d_0_max__ = n_options;
            alpha.reserve(alpha_d_0_max__);
            for (size_t d_0__ = 0; d_0__ < alpha_d_0_max__; ++d_0__) {
                if (jacobian__)
                    alpha.push_back(in__.scalar_lub_constrain(0, 1, lp__));
                else
                    alpha.push_back(in__.scalar_lub_constrain(0, 1));
            }
            current_statement_begin__ = 14;
            local_scalar_t__ theta_sigma;
            (void) theta_sigma;  // dummy to suppress unused var warning
            if (jacobian__)
                theta_sigma = in__.scalar_lb_constrain(0, lp__);
            else
                theta_sigma = in__.scalar_lb_constrain(0);
            current_statement_begin__ = 15;
            local_scalar_t__ delta_sigma;
            (void) delta_sigma;  // dummy to suppress unused var warning
            if (jacobian__)
                delta_sigma = in__.scalar_lb_constrain(0, lp__);
            else
                delta_sigma = in__.scalar_lb_constrain(0);
            // transformed parameters
            current_statement_begin__ = 18;
            validate_non_negative_index("mu", "n_days", n_days);
            validate_non_negative_index("mu", "n_options", n_options);
            Eigen::Matrix<local_scalar_t__, Eigen::Dynamic, Eigen::Dynamic> mu(n_days, n_options);
            stan::math::initialize(mu, DUMMY_VAR__);
            stan::math::fill(mu, DUMMY_VAR__);
            // transformed parameters block statements
            current_statement_begin__ = 19;
            for (int o = 1; o <= n_options; ++o) {
                current_statement_begin__ = 20;
                stan::model::assign(mu, 
                            stan::model::cons_list(stan::model::index_omni(), stan::model::cons_list(stan::model::index_uni(o), stan::model::nil_index_list())), 
                            add(cumulative_sum(stan::model::rvalue(delta, stan::model::cons_list(stan::model::index_omni(), stan::model::cons_list(stan::model::index_uni(o), stan::model::nil_index_list())), "delta")), get_base1(alpha, o, "alpha", 1)), 
                            "assigning variable mu");
                current_statement_begin__ = 22;
                for (int i = 1; i <= n_days; ++i) {
                    current_statement_begin__ = 23;
                    if (as_bool(logical_lt(get_base1(mu, i, o, "mu", 1), 0))) {
                        current_statement_begin__ = 23;
                        stan::model::assign(mu, 
                                    stan::model::cons_list(stan::model::index_uni(i), stan::model::cons_list(stan::model::index_uni(o), stan::model::nil_index_list())), 
                                    0, 
                                    "assigning variable mu");
                    }
                    current_statement_begin__ = 24;
                    if (as_bool(logical_gt(get_base1(mu, i, o, "mu", 1), 1))) {
                        current_statement_begin__ = 24;
                        stan::model::assign(mu, 
                                    stan::model::cons_list(stan::model::index_uni(i), stan::model::cons_list(stan::model::index_uni(o), stan::model::nil_index_list())), 
                                    1, 
                                    "assigning variable mu");
                    }
                }
            }
            // validate transformed parameters
            const char* function__ = "validate transformed params";
            (void) function__;  // dummy to suppress unused var warning
            current_statement_begin__ = 18;
            size_t mu_j_1_max__ = n_days;
            size_t mu_j_2_max__ = n_options;
            for (size_t j_1__ = 0; j_1__ < mu_j_1_max__; ++j_1__) {
                for (size_t j_2__ = 0; j_2__ < mu_j_2_max__; ++j_2__) {
                    if (stan::math::is_uninitialized(mu(j_1__, j_2__))) {
                        std::stringstream msg__;
                        msg__ << "Undefined transformed parameter: mu" << "(" << j_1__ << ", " << j_2__ << ")";
                        stan::lang::rethrow_located(std::runtime_error(std::string("Error initializing variable mu: ") + msg__.str()), current_statement_begin__, prog_reader__());
                    }
                }
            }
            // model body
            current_statement_begin__ = 30;
            lp_accum__.add(normal_log<propto__>(alpha, prior_pct, 0.1));
            current_statement_begin__ = 31;
            lp_accum__.add(normal_log<propto__>(theta_sigma, 0, 0.05));
            current_statement_begin__ = 32;
            lp_accum__.add(normal_log<propto__>(delta_sigma, 0, 0.05));
            current_statement_begin__ = 33;
            for (int o = 1; o <= n_options; ++o) {
                current_statement_begin__ = 34;
                lp_accum__.add(normal_log<propto__>(stan::model::rvalue(delta, stan::model::cons_list(stan::model::index_omni(), stan::model::cons_list(stan::model::index_uni(o), stan::model::nil_index_list())), "delta"), 0, delta_sigma));
            }
            current_statement_begin__ = 37;
            for (int o = 1; o <= n_options; ++o) {
                current_statement_begin__ = 38;
                for (int p = 1; p <= n_polls; ++p) {
                    current_statement_begin__ = 39;
                    lp_accum__.add(binomial_log<propto__>(get_base1(get_base1(y, p, "y", 1), o, "y", 2), get_base1(n, p, "n", 1), get_base1(theta, p, o, "theta", 1)));
                    current_statement_begin__ = 40;
                    lp_accum__.add(normal_log<propto__>(get_base1(theta, p, o, "theta", 1), get_base1(mu, get_base1(day_id, p, "day_id", 1), o, "mu", 1), theta_sigma));
                }
            }
        } catch (const std::exception& e) {
            stan::lang::rethrow_located(e, current_statement_begin__, prog_reader__());
            // Next line prevents compiler griping about no return
            throw std::runtime_error("*** IF YOU SEE THIS, PLEASE REPORT A BUG ***");
        }
        lp_accum__.add(lp__);
        return lp_accum__.sum();
    } // log_prob()
    template <bool propto, bool jacobian, typename T_>
    T_ log_prob(Eigen::Matrix<T_,Eigen::Dynamic,1>& params_r,
               std::ostream* pstream = 0) const {
      std::vector<T_> vec_params_r;
      vec_params_r.reserve(params_r.size());
      for (int i = 0; i < params_r.size(); ++i)
        vec_params_r.push_back(params_r(i));
      std::vector<int> vec_params_i;
      return log_prob<propto,jacobian,T_>(vec_params_r, vec_params_i, pstream);
    }
    void get_param_names(std::vector<std::string>& names__) const {
        names__.resize(0);
        names__.push_back("theta");
        names__.push_back("delta");
        names__.push_back("alpha");
        names__.push_back("theta_sigma");
        names__.push_back("delta_sigma");
        names__.push_back("mu");
    }
    void get_dims(std::vector<std::vector<size_t> >& dimss__) const {
        dimss__.resize(0);
        std::vector<size_t> dims__;
        dims__.resize(0);
        dims__.push_back(n_polls);
        dims__.push_back(n_options);
        dimss__.push_back(dims__);
        dims__.resize(0);
        dims__.push_back(n_days);
        dims__.push_back(n_options);
        dimss__.push_back(dims__);
        dims__.resize(0);
        dims__.push_back(n_options);
        dimss__.push_back(dims__);
        dims__.resize(0);
        dimss__.push_back(dims__);
        dims__.resize(0);
        dimss__.push_back(dims__);
        dims__.resize(0);
        dims__.push_back(n_days);
        dims__.push_back(n_options);
        dimss__.push_back(dims__);
    }
    template <typename RNG>
    void write_array(RNG& base_rng__,
                     std::vector<double>& params_r__,
                     std::vector<int>& params_i__,
                     std::vector<double>& vars__,
                     bool include_tparams__ = true,
                     bool include_gqs__ = true,
                     std::ostream* pstream__ = 0) const {
        typedef double local_scalar_t__;
        vars__.resize(0);
        stan::io::reader<local_scalar_t__> in__(params_r__, params_i__);
        static const char* function__ = "model_yapa_namespace::write_array";
        (void) function__;  // dummy to suppress unused var warning
        // read-transform, write parameters
        Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> theta = in__.matrix_lub_constrain(0, 1, n_polls, n_options);
        size_t theta_j_2_max__ = n_options;
        size_t theta_j_1_max__ = n_polls;
        for (size_t j_2__ = 0; j_2__ < theta_j_2_max__; ++j_2__) {
            for (size_t j_1__ = 0; j_1__ < theta_j_1_max__; ++j_1__) {
                vars__.push_back(theta(j_1__, j_2__));
            }
        }
        Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> delta = in__.matrix_constrain(n_days, n_options);
        size_t delta_j_2_max__ = n_options;
        size_t delta_j_1_max__ = n_days;
        for (size_t j_2__ = 0; j_2__ < delta_j_2_max__; ++j_2__) {
            for (size_t j_1__ = 0; j_1__ < delta_j_1_max__; ++j_1__) {
                vars__.push_back(delta(j_1__, j_2__));
            }
        }
        std::vector<double> alpha;
        size_t alpha_d_0_max__ = n_options;
        alpha.reserve(alpha_d_0_max__);
        for (size_t d_0__ = 0; d_0__ < alpha_d_0_max__; ++d_0__) {
            alpha.push_back(in__.scalar_lub_constrain(0, 1));
        }
        size_t alpha_k_0_max__ = n_options;
        for (size_t k_0__ = 0; k_0__ < alpha_k_0_max__; ++k_0__) {
            vars__.push_back(alpha[k_0__]);
        }
        double theta_sigma = in__.scalar_lb_constrain(0);
        vars__.push_back(theta_sigma);
        double delta_sigma = in__.scalar_lb_constrain(0);
        vars__.push_back(delta_sigma);
        double lp__ = 0.0;
        (void) lp__;  // dummy to suppress unused var warning
        stan::math::accumulator<double> lp_accum__;
        local_scalar_t__ DUMMY_VAR__(std::numeric_limits<double>::quiet_NaN());
        (void) DUMMY_VAR__;  // suppress unused var warning
        if (!include_tparams__ && !include_gqs__) return;
        try {
            // declare and define transformed parameters
            current_statement_begin__ = 18;
            validate_non_negative_index("mu", "n_days", n_days);
            validate_non_negative_index("mu", "n_options", n_options);
            Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> mu(n_days, n_options);
            stan::math::initialize(mu, DUMMY_VAR__);
            stan::math::fill(mu, DUMMY_VAR__);
            // do transformed parameters statements
            current_statement_begin__ = 19;
            for (int o = 1; o <= n_options; ++o) {
                current_statement_begin__ = 20;
                stan::model::assign(mu, 
                            stan::model::cons_list(stan::model::index_omni(), stan::model::cons_list(stan::model::index_uni(o), stan::model::nil_index_list())), 
                            add(cumulative_sum(stan::model::rvalue(delta, stan::model::cons_list(stan::model::index_omni(), stan::model::cons_list(stan::model::index_uni(o), stan::model::nil_index_list())), "delta")), get_base1(alpha, o, "alpha", 1)), 
                            "assigning variable mu");
                current_statement_begin__ = 22;
                for (int i = 1; i <= n_days; ++i) {
                    current_statement_begin__ = 23;
                    if (as_bool(logical_lt(get_base1(mu, i, o, "mu", 1), 0))) {
                        current_statement_begin__ = 23;
                        stan::model::assign(mu, 
                                    stan::model::cons_list(stan::model::index_uni(i), stan::model::cons_list(stan::model::index_uni(o), stan::model::nil_index_list())), 
                                    0, 
                                    "assigning variable mu");
                    }
                    current_statement_begin__ = 24;
                    if (as_bool(logical_gt(get_base1(mu, i, o, "mu", 1), 1))) {
                        current_statement_begin__ = 24;
                        stan::model::assign(mu, 
                                    stan::model::cons_list(stan::model::index_uni(i), stan::model::cons_list(stan::model::index_uni(o), stan::model::nil_index_list())), 
                                    1, 
                                    "assigning variable mu");
                    }
                }
            }
            if (!include_gqs__ && !include_tparams__) return;
            // validate transformed parameters
            const char* function__ = "validate transformed params";
            (void) function__;  // dummy to suppress unused var warning
            // write transformed parameters
            if (include_tparams__) {
                size_t mu_j_2_max__ = n_options;
                size_t mu_j_1_max__ = n_days;
                for (size_t j_2__ = 0; j_2__ < mu_j_2_max__; ++j_2__) {
                    for (size_t j_1__ = 0; j_1__ < mu_j_1_max__; ++j_1__) {
                        vars__.push_back(mu(j_1__, j_2__));
                    }
                }
            }
            if (!include_gqs__) return;
        } catch (const std::exception& e) {
            stan::lang::rethrow_located(e, current_statement_begin__, prog_reader__());
            // Next line prevents compiler griping about no return
            throw std::runtime_error("*** IF YOU SEE THIS, PLEASE REPORT A BUG ***");
        }
    }
    template <typename RNG>
    void write_array(RNG& base_rng,
                     Eigen::Matrix<double,Eigen::Dynamic,1>& params_r,
                     Eigen::Matrix<double,Eigen::Dynamic,1>& vars,
                     bool include_tparams = true,
                     bool include_gqs = true,
                     std::ostream* pstream = 0) const {
      std::vector<double> params_r_vec(params_r.size());
      for (int i = 0; i < params_r.size(); ++i)
        params_r_vec[i] = params_r(i);
      std::vector<double> vars_vec;
      std::vector<int> params_i_vec;
      write_array(base_rng, params_r_vec, params_i_vec, vars_vec, include_tparams, include_gqs, pstream);
      vars.resize(vars_vec.size());
      for (int i = 0; i < vars.size(); ++i)
        vars(i) = vars_vec[i];
    }
    std::string model_name() const {
        return "model_yapa";
    }
    void constrained_param_names(std::vector<std::string>& param_names__,
                                 bool include_tparams__ = true,
                                 bool include_gqs__ = true) const {
        std::stringstream param_name_stream__;
        size_t theta_j_2_max__ = n_options;
        size_t theta_j_1_max__ = n_polls;
        for (size_t j_2__ = 0; j_2__ < theta_j_2_max__; ++j_2__) {
            for (size_t j_1__ = 0; j_1__ < theta_j_1_max__; ++j_1__) {
                param_name_stream__.str(std::string());
                param_name_stream__ << "theta" << '.' << j_1__ + 1 << '.' << j_2__ + 1;
                param_names__.push_back(param_name_stream__.str());
            }
        }
        size_t delta_j_2_max__ = n_options;
        size_t delta_j_1_max__ = n_days;
        for (size_t j_2__ = 0; j_2__ < delta_j_2_max__; ++j_2__) {
            for (size_t j_1__ = 0; j_1__ < delta_j_1_max__; ++j_1__) {
                param_name_stream__.str(std::string());
                param_name_stream__ << "delta" << '.' << j_1__ + 1 << '.' << j_2__ + 1;
                param_names__.push_back(param_name_stream__.str());
            }
        }
        size_t alpha_k_0_max__ = n_options;
        for (size_t k_0__ = 0; k_0__ < alpha_k_0_max__; ++k_0__) {
            param_name_stream__.str(std::string());
            param_name_stream__ << "alpha" << '.' << k_0__ + 1;
            param_names__.push_back(param_name_stream__.str());
        }
        param_name_stream__.str(std::string());
        param_name_stream__ << "theta_sigma";
        param_names__.push_back(param_name_stream__.str());
        param_name_stream__.str(std::string());
        param_name_stream__ << "delta_sigma";
        param_names__.push_back(param_name_stream__.str());
        if (!include_gqs__ && !include_tparams__) return;
        if (include_tparams__) {
            size_t mu_j_2_max__ = n_options;
            size_t mu_j_1_max__ = n_days;
            for (size_t j_2__ = 0; j_2__ < mu_j_2_max__; ++j_2__) {
                for (size_t j_1__ = 0; j_1__ < mu_j_1_max__; ++j_1__) {
                    param_name_stream__.str(std::string());
                    param_name_stream__ << "mu" << '.' << j_1__ + 1 << '.' << j_2__ + 1;
                    param_names__.push_back(param_name_stream__.str());
                }
            }
        }
        if (!include_gqs__) return;
    }
    void unconstrained_param_names(std::vector<std::string>& param_names__,
                                   bool include_tparams__ = true,
                                   bool include_gqs__ = true) const {
        std::stringstream param_name_stream__;
        size_t theta_j_2_max__ = n_options;
        size_t theta_j_1_max__ = n_polls;
        for (size_t j_2__ = 0; j_2__ < theta_j_2_max__; ++j_2__) {
            for (size_t j_1__ = 0; j_1__ < theta_j_1_max__; ++j_1__) {
                param_name_stream__.str(std::string());
                param_name_stream__ << "theta" << '.' << j_1__ + 1 << '.' << j_2__ + 1;
                param_names__.push_back(param_name_stream__.str());
            }
        }
        size_t delta_j_2_max__ = n_options;
        size_t delta_j_1_max__ = n_days;
        for (size_t j_2__ = 0; j_2__ < delta_j_2_max__; ++j_2__) {
            for (size_t j_1__ = 0; j_1__ < delta_j_1_max__; ++j_1__) {
                param_name_stream__.str(std::string());
                param_name_stream__ << "delta" << '.' << j_1__ + 1 << '.' << j_2__ + 1;
                param_names__.push_back(param_name_stream__.str());
            }
        }
        size_t alpha_k_0_max__ = n_options;
        for (size_t k_0__ = 0; k_0__ < alpha_k_0_max__; ++k_0__) {
            param_name_stream__.str(std::string());
            param_name_stream__ << "alpha" << '.' << k_0__ + 1;
            param_names__.push_back(param_name_stream__.str());
        }
        param_name_stream__.str(std::string());
        param_name_stream__ << "theta_sigma";
        param_names__.push_back(param_name_stream__.str());
        param_name_stream__.str(std::string());
        param_name_stream__ << "delta_sigma";
        param_names__.push_back(param_name_stream__.str());
        if (!include_gqs__ && !include_tparams__) return;
        if (include_tparams__) {
            size_t mu_j_2_max__ = n_options;
            size_t mu_j_1_max__ = n_days;
            for (size_t j_2__ = 0; j_2__ < mu_j_2_max__; ++j_2__) {
                for (size_t j_1__ = 0; j_1__ < mu_j_1_max__; ++j_1__) {
                    param_name_stream__.str(std::string());
                    param_name_stream__ << "mu" << '.' << j_1__ + 1 << '.' << j_2__ + 1;
                    param_names__.push_back(param_name_stream__.str());
                }
            }
        }
        if (!include_gqs__) return;
    }
}; // model
}  // namespace
typedef model_yapa_namespace::model_yapa stan_model;
#ifndef USING_R
stan::model::model_base& new_model(
        stan::io::var_context& data_context,
        unsigned int seed,
        std::ostream* msg_stream) {
  stan_model* m = new stan_model(data_context, seed, msg_stream);
  return *m;
}
#endif
#endif
