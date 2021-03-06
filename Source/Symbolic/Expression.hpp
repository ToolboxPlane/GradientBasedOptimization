/**
 * @file Expression.hpp
 * @author paul
 * @date 25.08.20
 * Description here TODO
 */
#ifndef GRADIENTOPTIMIZATION_EXPRESSION_HPP
#define GRADIENTOPTIMIZATION_EXPRESSION_HPP

#include <concepts>
#include <string>

namespace grad::sym {
    template<typename T>
    concept Expression = requires(const T t) {
        typename T::type;
        { t.resolve() }
        ->std::same_as<typename T::type>;
        { T::isConstant() }
        ->std::same_as<bool>;
    };

    template<typename T>
    struct IsExpression {
        static constexpr auto val = false;
    };

    template<Expression expr>
    struct IsExpression<expr> {
        static constexpr auto val = true;
    };
} // namespace grad::sym

#endif // GRADIENTOPTIMIZATION_EXPRESSION_HPP
