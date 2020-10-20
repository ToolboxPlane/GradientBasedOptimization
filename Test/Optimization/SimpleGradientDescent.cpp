#include <gtest/gtest.h>

#include "Symbolic/Operators.hpp"

#include "Optimization/SimpleGradientDescent.hpp"


TEST(SimpleGradientDescent, SquareEpsilon) {
    auto x = grad::sym::Variable<double>{10};
    auto y = x * x;
    grad::opt::simple_gradient_descent::optimizeEpsilon(y, x, 0.1*0.1, 0.5);
    EXPECT_NEAR(x.resolve(), 0, 0.1);
}
