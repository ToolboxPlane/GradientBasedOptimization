/**
 * @file Grad.hpp
 * @author paul
 * @date 03.09.20
 * Description here TODO
 */
#ifndef GRADIENTOPTIMIZATION_GRAD_HPP
#define GRADIENTOPTIMIZATION_GRAD_HPP

#include "Expression.hpp"

#include "Variable.hpp"

namespace grad::sym {
    template <typename T>
    concept Grad =  requires(const T &t) {
        IsExpression<T>::val == true;
        typename T::dtype;
        {t.grad(std::declval<Variable<typename T::type>>())} -> std::same_as<typename T::dtype>;
    };

    template <typename T>
    struct IsGrad {
        static constexpr auto val = false;
    };

    template <Grad grad>
    struct IsGrad<grad> {
        static constexpr auto val = true;
    };
}

#endif //GRADIENTOPTIMIZATION_GRAD_HPP
