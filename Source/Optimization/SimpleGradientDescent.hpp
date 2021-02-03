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
#include "../Symbolic/Operators.hpp"
#include "../Symbolic/Variable.hpp"

namespace grad::opt {
    template<sym::Expression Expr, typename X, typename Nu = double>
    class SimpleGradientDescent {
      public:
        using T = typename Expr::type;
        using XVar = sym::Variable<X>;
        using Grad = decltype(sym::gradient(std::declval<Expr>(), std::declval<XVar>()));
        using Update = sym::Sub<XVar, sym::Mul<Grad, sym::Constant<Nu>>>;

        SimpleGradientDescent(Expr expr, std::vector<XVar> xs, Nu nu);

        void step();

      private:
        std::vector<Update> updateExprs;
        std::vector<XVar> xs;
    };


    template<sym::Expression Expr, typename X, typename Nu>
    SimpleGradientDescent<Expr, X, Nu>::SimpleGradientDescent(Expr expr, std::vector<XVar> xs, Nu nu) : xs{xs} {
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

        for (auto c = 0U; c < xs.size(); ++c) {
            xs[c].set(updates[c]);
        }
    }

    struct make_sgd_impl {
        template<sym::Expression Expr, typename X, typename Nu>
        auto operator()(Expr expr, std::vector<sym::Variable<X>> x, Nu nu) {
            return SimpleGradientDescent<Expr, X, Nu>{expr, x, nu};
        }
    } make_sgd;

} // namespace grad::opt


#endif // GRADIENTOPTIMIZATION_SIMPLEGRADIENTDESCENT_HPP
