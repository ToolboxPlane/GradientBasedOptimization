/**
 * @file ConceptUtil.hpp
 * @author paul
 * @date 03.09.20
 * Description here TODO
 */
#ifndef GRADIENTOPTIMIZATION_CONCEPTUTIL_HPP
#define GRADIENTOPTIMIZATION_CONCEPTUTIL_HPP

#include "Expression.hpp"

template <typename T>
struct IsExpression {
    static constexpr auto val = false;
};

template <grad::Expression expr>
struct IsExpression<expr> {
    static constexpr auto val = true;
};

#endif //GRADIENTOPTIMIZATION_CONCEPTUTIL_HPP
