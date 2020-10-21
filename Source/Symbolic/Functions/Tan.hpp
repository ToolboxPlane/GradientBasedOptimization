/**
 * @file Tan.hpp
 * @author paul
 * @date 21.10.20
 * Description here TODO
 */
#ifndef GRADIENTOPTIMIZATION_TAN_HPP
#define GRADIENTOPTIMIZATION_TAN_HPP

#include "../Expression.hpp"

#include "../Div.hpp"
#include "Sin.hpp"

namespace grad::sym {
    template <Expression Expr>
    class Tan {
        public:
            using type = typename Expr::type;

            explicit Tan(Expr expr);

            auto resolve() const -> type;

            template<Expression Expr_>
            friend auto gradient(const Tan<Expr_> &x, const Variable<typename Expr_::type> &d);

        private:
            Expr expr;
    };

    template<Expression Expr>
    Tan<Expr>::Tan(Expr expr) : expr{expr} {}

    template<Expression Expr>
    auto Tan<Expr>::resolve() const -> type {
        return std::tan(expr.resolve());
    }

    template<Expression Expr_>
    auto gradient(const Tan<Expr_> &x, const Variable<typename Expr_::type> &d) {
        return Div{gradient(x.expr, d), Mul{Cos{x}, Cos{x}}};
    }
}

#endif //GRADIENTOPTIMIZATION_TAN_HPP
