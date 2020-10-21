#include <gtest/gtest.h>
#include <cmath>

#include "Symbolic/Functions/Cos.hpp"

#include "Symbolic/Constant.hpp"

TEST(Cos, Expression) {
    using Const = grad::sym::Constant<int>;
    EXPECT_TRUE((grad::sym::IsExpression<grad::sym::Cos<Const>>::val));
}

TEST(Cos, Resolve) {
    grad::sym::Constant<double> a{17};
    grad::sym::Cos<decltype(a)> cos{a};
    EXPECT_DOUBLE_EQ(cos.resolve(), std::cos(17));
}

TEST(Cos, Gradient) {
    grad::sym::Variable<double> x{0};
    grad::sym::Cos<decltype(x)> y{x};
    EXPECT_DOUBLE_EQ(grad::sym::gradient(y, x).resolve(), 0);
}
