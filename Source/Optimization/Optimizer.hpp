/**
 * @file Optimizer.hpp.h
 * @author paul
 * @date 13.01.21
 * Description here TODO
 */
#ifndef GRADIENTOPTIMIZATION_OPTIMIZER_HPP
#define GRADIENTOPTIMIZATION_OPTIMIZER_HPP

#include "../Symbolic/Expression.hpp"

namespace grad::opt {
    template<typename T>
    concept Optimizer = requires(T t) {
        {t.step()};
    };

    template<typename T>
    struct IsOptimizer {
        static constexpr auto val = false;
    };

    template<Optimizer optimizer>
    struct IsOptimizer<optimizer> {
        static constexpr auto val = true;
    };

} // namespace grad::opt

#endif // GRADIENTOPTIMIZATION_OPTIMIZER_HPP
