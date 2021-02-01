#include "Optimization/Momentum.hpp"

#include <gtest/gtest.h>

#include "Symbolic/Operators.hpp"

TEST(Momentum, SquareIterationsSingleStep) {
    auto x = grad::sym::Variable<double>{10};
    auto y = x * x;
    auto opt = grad::opt::make_momentum(y, std::vector{x}, 0.17, 0.37);
    opt.step();
    EXPECT_DOUBLE_EQ(x.resolve(), 10 - 2 * 10 * 0.17);
}
