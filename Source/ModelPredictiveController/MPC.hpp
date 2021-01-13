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
        template<std::size_t N, sym::Expression Error, typename U, sym::Expression X>
        class MPC {
            public:
                using T = typename Error::type;

                MPC(Error error, std::vector<sym::Variable<T>> us, X x);

                template<typename Term, typename OptimStep>
                auto update(Term term, OptimStep optimStep);

                auto getU(std::size_t t = 0) const -> U;

                auto getX() const -> X;

            private:
                Error error;
                std::vector<U> us;
                X x;
        };

        template<std::size_t N, sym::Expression Error, typename U, sym::Expression X>
        MPC<N, Error, U, X>::MPC(Error error, std::vector<sym::Variable<T>> us, X x) : error{error}, us{std::move(us)},
            x{x} {}

        template<std::size_t N, sym::Expression Error, typename U, sym::Expression X>
        template<typename Term, typename OptimStep>
        auto MPC<N, Error, U, X>::update(Term term, OptimStep optimStep) {
            while (not term(error.resolve())) {
                for (auto &u : us) {
                    optimStep(error, u);
                }
            }
            return error.resolve();
        }

        template<std::size_t N, sym::Expression Error, typename U, sym::Expression X>
        auto MPC<N, Error, U, X>::getU(std::size_t t) const -> U {
            return us.at(t);
        }

        template<std::size_t N, sym::Expression Error, typename U, sym::Expression X>
        auto MPC<N, Error, U, X>::getX() const -> X {
            return x;
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

        return impl::MPC<steps, decltype(error), UVar, X>{error, us, x};
    }

    template<std::size_t steps, typename U, typename X, typename F, typename J>
    auto make_mpc(F f, J j) {
        auto x = sym::Variable<X>{0};
        return make_mpc<steps, U>(f, j, x);
    }
}

#endif //GRADIENTOPTIMIZATION_MPC_HPP
