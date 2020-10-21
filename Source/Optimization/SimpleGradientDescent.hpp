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
    template<sym::Expression Expr, typename TermFunc>
    void optimize(Expr expr, sym::Variable<typename Expr::type> x, typename Expr::type nu,
                         TermFunc termFunc) {
        auto error = expr.resolve();
        auto gradient = sym::gradient(expr, x);

        while (!termFunc(error)) {
            auto update = gradient.resolve() * nu;
            x.set(x.resolve() - update);
            error = expr.resolve();
        }
    }

    template<sym::Expression Expr>
    void optimizeEpsilon(Expr expr, sym::Variable<typename Expr::type> x, typename Expr::type nu, 
                          typename Expr::type epsilon) {
        auto termFunc = [epsilon](typename Expr::type error){ return error < epsilon; };
        optimize(expr, x, nu, termFunc);
    }

    template<sym::Expression Expr>
    void optimizeIterations(Expr expr, sym::Variable<typename Expr::type> x, typename Expr::type nu,
                            std::size_t iterations) {
        iterations += 1; // The termination criteria is checked before the first optimization step
        auto termFunc = [&iterations](typename Expr::type){ 
            iterations -= 1;
            return iterations == 0;
        };

        optimize(expr, x, nu, termFunc);
    }
}


#endif //GRADIENTOPTIMIZATION_SIMPLEGRADIENTDESCENT_HPP
