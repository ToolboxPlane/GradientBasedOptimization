/**
 * @file MPC.hpp.h
 * @author paul
 * @date 11.01.21
 * Description here TODO
 */
#ifndef GRADIENTOPTIMIZATION_MPC_HPP
#define GRADIENTOPTIMIZATION_MPC_HPP

#include <utility>
#include <vector>

#include "../Symbolic/Expression.hpp"
#include "../Symbolic/Variable.hpp"
#include "../Symbolic/Constant.hpp"

namespace grad::mpc {
    namespace impl {
        template<std::size_t N, sym::Expression Error>
        class MPC {
            public:
                using T = typename Error::type;
                using U = sym::Variable<T>;

                MPC(Error error, std::vector<sym::Variable<T>> us);

                template<typename Term, typename OptimStep>
                auto update(Term term, OptimStep optimStep);

                auto get(std::size_t t) const -> U;

            private:
                Error error;
                std::vector<U> us;
        };

        template<std::size_t N, sym::Expression Error>
        MPC<N, Error>::MPC(Error error, std::vector<sym::Variable<T>> us) : error{error}, us{std::move(us)} {}

        template<std::size_t N, sym::Expression Error>
        template<typename Term, typename OptimStep>
        auto MPC<N, Error>::update(Term term, OptimStep optimStep) {
            while (not term(error.resolve())) {
                for (auto &u : us) {
                    optimStep(error, u);
                }
            }
            return error.resolve();
        }

        template<std::size_t N, sym::Expression Error>
        auto MPC<N, Error>::get(std::size_t t) const -> U {
            return us.at(t);
        }

        template<std::size_t t, std::size_t steps, typename F, typename J, sym::Expression X>
        auto getError(F f, J j, X x, std::vector<sym::Variable<typename X::type>> us) {
            auto tConst = sym::Constant<typename X::type>{t};
            auto nextX = f(x, us.at(t), tConst);

            if constexpr (t + 1 < steps) {
                return j(nextX, tConst) + getError<t + 1, steps, F, J, decltype(nextX)>(f, j, nextX, us);
            } else {
                return j(nextX, tConst);
            }
        }
    }

    // @TODO type of u
    template<std::size_t steps, typename F, typename J, sym::Expression X>
    auto make_mpc(F f, J j, X x) {
        using T = typename X::type;
        static_assert(std::is_invocable_v<F, X, sym::Variable<T>, sym::Constant<T>>,
                      "f must be of the form f(x, u, t)");
        static_assert(std::is_invocable_v<J, X, sym::Constant<T>>,
                      "j must be of the form j(x, t)");

        std::vector<sym::Variable<T>> us;
        for (auto c = 0U; c < steps; ++c) {
            us.emplace_back(0);
        }
        auto error = impl::getError<0, steps>(f, j, x, us);

        return impl::MPC<steps, decltype(error)>{error, us};
    }
}

#endif //GRADIENTOPTIMIZATION_MPC_HPP
