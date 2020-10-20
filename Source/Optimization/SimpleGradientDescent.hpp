/**
 * @file SimpleGradientDescent.hpp
 * @author paul
 * @date 20.10.20
 * Description here TODO
 */
#ifndef GRADIENTOPTIMIZATION_SIMPLEGRADIENTDESCENT_HPP
#define GRADIENTOPTIMIZATION_SIMPLEGRADIENTDESCENT_HPP

#include "../Symbolic/Expression.hpp"
#include "../Symbolic/Variable.hpp"

namespace grad::opt::simple_gradient_descent {
    template<sym::Expression Expr>
    void optimizeEpsilon(Expr expr, sym::Variable<typename Expr::type> x, typename Expr::type epsilon,
                         typename Expr::type nu) {
        auto error = expr.resolve();
        auto gradient = sym::gradient(expr, x);

        while (error >= epsilon) {
            auto update = gradient.resolve() * nu;
            x.set(x.resolve() - update);
            error = expr.resolve();
        }
    }
}

#endif //GRADIENTOPTIMIZATION_SIMPLEGRADIENTDESCENT_HPP
