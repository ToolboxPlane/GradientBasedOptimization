/**
 * @file Operators.hpp
 * @author paul
 * @date 05.09.20
 * Description here TODO
 */
#ifndef GRADIENTOPTIMIZATION_OPERATORS_HPP
#define GRADIENTOPTIMIZATION_OPERATORS_HPP

#include "Add.hpp"
#include "Mul.hpp"

namespace grad::sym {
    template<Expression Lhs, Expression Rhs>
    auto operator+(Lhs lhs, Rhs rhs) -> Add<Lhs, Rhs> {
        return Add<Lhs, Rhs>{lhs, rhs};
    }

    template<Expression Lhs, Expression Rhs>
    auto operator*(Lhs lhs, Rhs rhs) -> Mul<Lhs, Rhs> {
        return Mul<Lhs, Rhs>{lhs, rhs};
    }
}

#endif //GRADIENTOPTIMIZATION_OPERATORS_HPP
