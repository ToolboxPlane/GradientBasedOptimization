#include "Optimization/SimpleGradientDescent.hpp"

#include <gtest/gtest.h>

#include "Optimization/Optimizer.hpp"
#include "Symbolic/Operators.hpp"

TEST(SimpleGradientDescent, IsOptimizer) {
    auto x = grad::sym::Variable<double>{10};
    auto opt = grad::opt::make_sgd(x, std::vector{x}, 0.17);
    EXPECT_TRUE(grad::opt::IsOptimizer<decltype(opt)>::val);
}

TEST(SimpleGradientDescent, SquareIterationsSingleStep) {
    auto x = grad::sym::Variable<double>{10};
    auto y = x * x;
    auto opt = grad::opt::make_sgd(y, std::vector{x}, 0.17);
    opt.step();
    EXPECT_DOUBLE_EQ(x.resolve(), 10 - 2 * 10 * 0.17);
}
