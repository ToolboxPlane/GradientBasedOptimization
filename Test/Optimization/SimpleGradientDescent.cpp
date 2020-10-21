#include <gtest/gtest.h>

#include "Symbolic/Operators.hpp"

#include "Optimization/SimpleGradientDescent.hpp"


TEST(SimpleGradientDescent, SquareEpsilon) {
    auto x = grad::sym::Variable<double>{10};
    auto y = x * x;
    grad::opt::simple_gradient_descent::optimizeEpsilon(y, x, 0.5, 0.1*0.1);
    EXPECT_NEAR(x.resolve(), 0, 0.1);
}

TEST(SimpleGradientDescent, SquareIterationsConvergence) {
    auto x = grad::sym::Variable<double>{10};
    auto y = x * x;
    grad::opt::simple_gradient_descent::optimizeIterations(y, x, 0.5, 1000);
    EXPECT_NEAR(x.resolve(), 0, 0.1);
}

TEST(SimpleGradientDescent, SquareIterationsSingleStep) {
    auto x = grad::sym::Variable<double>{10};
    auto y = x * x;
    grad::opt::simple_gradient_descent::optimizeIterations(y, x, 0.5, 1);
    EXPECT_DOUBLE_EQ(x.resolve(), 10 - 2 * 10 * 0.5);
}
