/**
 * @file SimpleGradientDescent.hpp
 * @author paul
 * @date 20.10.20
 * Description here TODO
 */
#ifndef GRADIENTOPTIMIZATION_SIMPLEGRADIENTDESCENT_HPP
#define GRADIENTOPTIMIZATION_SIMPLEGRADIENTDESCENT_HPP

#include <vector>

#include "../Symbolic/Expression.hpp"
#include "../Symbolic/Variable.hpp"
#include "../Symbolic/Operators.hpp"

namespace grad::opt {

    template<sym::Expression Expr, typename X, typename Nu = double>
    class SimpleGradientDescent {
        public:
            using T = typename Expr::type;
            using Grad = decltype(sym::gradient(std::declval<Expr>(), std::declval<sym::Variable<X>>()));
            using Update = sym::Sub<sym::Variable<X>, sym::Mul<Grad, sym::Constant<Nu>>>;

            SimpleGradientDescent(Expr expr, std::vector<sym::Variable<X>> xs, Nu nu);

            void step();

        private:
            Expr expr;
            std::vector<Update> updateExprs;
            std::vector<sym::Variable<X>> xs;
            double nu;

    };


    template<sym::Expression Expr, typename X, typename Nu>
    SimpleGradientDescent<Expr, X, Nu>::SimpleGradientDescent(Expr expr, std::vector<sym::Variable<X>> xs, Nu nu)
        : expr{expr}, xs{xs}, nu{nu} {
        for (const auto &x : xs) {
            updateExprs.emplace_back(x - sym::gradient(expr, x) * nu);
        }
    }

    template<sym::Expression Expr, typename X, typename Nu>
    void SimpleGradientDescent<Expr, X, Nu>::step() {
        std::vector<typename Update::type> updates;
        for (const auto &updateExpr : updateExprs) {
            updates.emplace_back(updateExpr.resolve());
        }

        for (auto c=0U; c<xs.size(); ++c) {
            xs[c].set(updates[c]);
        }
    }


}


#endif //GRADIENTOPTIMIZATION_SIMPLEGRADIENTDESCENT_HPP
