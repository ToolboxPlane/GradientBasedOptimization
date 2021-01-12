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
        template<std::size_t N, sym::Expression Error, typename U>
        class MPC {
            public:
                using T = typename Error::type;

                MPC(Error error, std::vector<sym::Variable<T>> us);

                template<typename Term, typename OptimStep>
                auto update(Term term, OptimStep optimStep);

                auto get(std::size_t t) const -> U;

            private:
                Error error;
                std::vector<U> us;
        };

        template<std::size_t N, sym::Expression Error, typename U>
        MPC<N, Error, U>::MPC(Error error, std::vector<sym::Variable<T>> us) : error{error}, us{std::move(us)} {}

        template<std::size_t N, sym::Expression Error, typename U>
        template<typename Term, typename OptimStep>
        auto MPC<N, Error, U>::update(Term term, OptimStep optimStep) {
            while (not term(error.resolve())) {
                for (auto &u : us) {
                    optimStep(error, u);
                }
            }
            return error.resolve();
        }

        template<std::size_t N, sym::Expression Error, typename U>
        auto MPC<N, Error, U>::get(std::size_t t) const -> U {
            return us.at(t);
        }

        template<std::size_t t, std::size_t steps, typename F, typename J, sym::Expression X, typename U>
        auto getError(F f, J j, X x, std::vector<U> us) {
            auto u = us.at(t);
            auto nextX = f(x, u, t);

            if constexpr (t + 1 < steps) {
                return j(nextX, u, t) + getError<t + 1, steps, F, J, decltype(nextX)>(f, j, nextX, us);
            } else {
                return j(nextX, u, t);
            }
        }
    }

    // @TODO type of u
    template<std::size_t steps, typename U, typename F, typename J, sym::Expression X>
    auto make_mpc(F f, J j, X x) {
        using UVar = sym::Variable<U>;
        static_assert(std::is_invocable_v<F, X, UVar, std::size_t>,
                      "f must be of the form f(x, u, t)");
        static_assert(std::is_invocable_v<J, X, UVar, std::size_t>,
                      "j must be of the form j(x, u, t)");

        std::vector<UVar> us;
        for (auto c = 0U; c < steps; ++c) {
            us.emplace_back(0);
        }
        auto error = impl::getError<0, steps>(f, j, x, us);

        return impl::MPC<steps, decltype(error), UVar>{error, us};
    }
}

#endif //GRADIENTOPTIMIZATION_MPC_HPP
