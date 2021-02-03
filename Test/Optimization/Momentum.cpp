#include "Optimization/Momentum.hpp"
#include "Optimization/Optimizer.hpp"

#include <gtest/gtest.h>

#include "Symbolic/Operators.hpp"

TEST(Momentum, IsOptimizer) {
    auto x = grad::sym::Variable<double>{10};
    auto opt = grad::opt::make_momentum(x, std::vector{x}, 0.17, 0.37);
    EXPECT_TRUE(grad::opt::IsOptimizer<decltype(opt)>::val);
}

TEST(Momentum, SquareIterationsSingleStep) {
    auto x = grad::sym::Variable<double>{10};
    auto y = x * x;
    auto opt = grad::opt::make_momentum(y, std::vector{x}, 0.17, 0.37);
    opt.step();
    EXPECT_DOUBLE_EQ(x.resolve(), 10 - 2 * 10 * 0.17);
}
