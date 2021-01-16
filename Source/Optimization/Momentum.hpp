/**
 * @file Momentum.hpp.h
 * @author paul
 * @date 16.01.21
 * Description here TODO
 */
#ifndef GRADIENTOPTIMIZATION_MOMENTUM_HPP
#define GRADIENTOPTIMIZATION_MOMENTUM_HPP

#include <vector>

#include "../Symbolic/Expression.hpp"
#include "../Symbolic/Variable.hpp"
#include "../Symbolic/Operators.hpp"

namespace grad::opt {
    template<sym::Expression Expr, typename X, typename Param = double>
    class Momentum {
        public:
            using T = typename Expr::type;
            using XVar = sym::Variable<X>;
            using Grad = decltype(sym::gradient(std::declval<Expr>(), std::declval<XVar>()));
            using DeltaX = sym::Sub<sym::Mul<sym::Constant<Param>, XVar>, sym::Mul<sym::Constant<Param>, Grad>>;
            using Update = sym::Add<XVar, DeltaX>;

            Momentum(Expr expr, std::vector<XVar> xs, Param nu, Param alpha);

            void step();

        private:
            std::vector<Update> updateExprs;
            std::vector<XVar> lastDeltaX;
            std::vector<XVar> xs;
    };

    template<sym::Expression Expr, typename X, typename Param>
    Momentum<Expr, X, Param>::Momentum(Expr expr, std::vector<XVar> xs, Param nu, Param alpha) : xs{xs} {
        for (const auto &x : xs) {
            lastDeltaX.emplace_back(0);
            updateExprs.emplace_back(x + (alpha * lastDeltaX.back() - nu * sym::gradient(expr, x)));
        }
    }

    template<sym::Expression Expr, typename X, typename Param>
    void Momentum<Expr, X, Param>::step() {
        std::vector<typename Update::type> updates;
        for (const auto &updateExpr : updateExprs) {
            updates.emplace_back(updateExpr.resolve());
        }

        for (auto c=0U; c<xs.size(); ++c) {
            lastDeltaX[c].set(updates[c] - xs[c].resolve());
            xs[c].set(updates[c]);
        }
    }

    struct {
        template<sym::Expression Expr, typename X, typename Param>
        auto operator()(Expr expr, std::vector<sym::Variable<X>> x, Param nu, Param alpha) {
            return Momentum<Expr, X, Param>{expr, x, nu, alpha};
        }
    } make_momentum;
}

#endif //GRADIENTOPTIMIZATION_MOMENTUM_HPP
