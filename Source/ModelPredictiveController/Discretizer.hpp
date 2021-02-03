/**
 * @file Discretizer.hpp.h
 * @author paul
 * @date 03.02.21
 * Description here TODO
 */
#ifndef GRADIENTOPTIMIZATION_DISCRETIZER_HPP
#define GRADIENTOPTIMIZATION_DISCRETIZER_HPP

#include "Symbolic/Variable.hpp"

namespace grad::mpc::helper {
    template<typename F, typename IntegratorFactory, typename... Args>
    class Discretizer {
      public:
        using Integrator = decltype(std::declval<IntegratorFactory>().make());

        Discretizer(F f, double dt, Args &&...args);

        template<typename X, typename U, typename T>
        auto operator()(X x, U u, T t);

      private:
        Integrator integrator;
        sym::Variable<double> min;
    };


    struct make_discretizer_impl {
        template<typename F, typename IntegratorFactory, typename... Args>
        auto make(F f, double dt, IntegratorFactory integratorFactory, Args &&...args) {
            return Discretizer<F, IntegratorFactory, Args...>{f, integratorFactory, std::forward<Args>(args)...};
        }
    } make_discretizer;
} // namespace grad::mpc::helper

#endif // GRADIENTOPTIMIZATION_DISCRETIZER_HPP
