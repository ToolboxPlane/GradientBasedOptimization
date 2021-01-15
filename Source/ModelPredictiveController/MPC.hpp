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
#include <iostream>

#include "../Symbolic/Expression.hpp"
#include "../Optimization/Optimizer.hpp"

#include "../Symbolic/Variable.hpp"

namespace grad::mpc {
    namespace impl {
        template<std::size_t N, sym::Expression Error, typename U, sym::Expression X,
                opt::Optimizer Opt>
        class MPC {
            public:
                using T = typename Error::type;
                using UVar = sym::Variable<U>;

                MPC(Error error, std::vector<UVar> us, X x, Opt opt);

                template<typename Term>
                auto update(Term term);

                auto getU(std::size_t t = 0) const -> UVar;

                auto getX() const -> X;

            private:
                Error error;
                std::vector<UVar> us;
                X x;
                Opt opt;
        };

        template<std::size_t N, sym::Expression Error, typename U, sym::Expression X, opt::Optimizer Opt>
        MPC<N, Error, U, X, Opt>::MPC(Error error, std::vector<UVar> us, X x, Opt opt) : error{error}, us{std::move(us)},
                                                                                       x{x}, opt{opt} {}

        template<std::size_t N, sym::Expression Error, typename U, sym::Expression X, opt::Optimizer Opt>
        template<typename Term>
        auto MPC<N, Error, U, X, Opt>::update(Term term) {
            while (not term(error.resolve())) {
                opt.step();
            }
            return error.resolve();
        }

        template<std::size_t N, sym::Expression Error, typename U, sym::Expression X, opt::Optimizer Opt>
        auto MPC<N, Error, U, X, Opt>::getU(std::size_t t) const -> UVar {
            return us.at(t);
        }

        template<std::size_t N, sym::Expression Error, typename U, sym::Expression X, opt::Optimizer Opt>
        auto MPC<N, Error, U, X, Opt>::getX() const -> X {
            return x;
        }

        template<std::size_t t, std::size_t steps, typename F, typename J, sym::Expression X, typename UVar>
        auto getError(F f, J j, X x, std::vector<UVar> us) {
            auto u = us.at(t);
            auto nextX = f(x, u, t);

            if constexpr (t + 1 < steps) {
                return j(nextX, u, t) + getError<t + 1, steps, F, J, decltype(nextX)>(f, j, nextX, us);
            } else {
                return j(nextX, u, t);
            }
        }
    }

    template<std::size_t steps, typename U, typename F, typename J, sym::Expression X,
            typename MakeOptim, typename... OptimArgs>
    auto make_mpc(F f, J j, X x, MakeOptim makeOptim, OptimArgs&&... optimArgs) {
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

        auto optim = makeOptim(error, us, std::forward<OptimArgs>(optimArgs)...);

        return impl::MPC<steps, decltype(error), U, X, decltype(optim)>{error, us, x, optim};
    }

    template<std::size_t steps, typename U, typename X, typename F, typename J,
            typename MakeOptim, typename... OptimArgs>
    auto make_mpc(F f, J j, MakeOptim makeOptim, OptimArgs&&... optimArgs) {
        auto x = sym::Variable<X>{0};
        return make_mpc<steps, U>(f, j, x, makeOptim, std::forward<OptimArgs>(optimArgs)...);
    }
}

#endif //GRADIENTOPTIMIZATION_MPC_HPP
