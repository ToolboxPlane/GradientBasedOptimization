#include <gtest/gtest.h>
#include <cmath>

#include "Symbolic/Functions/Sin.hpp"

#include "Symbolic/Constant.hpp"

TEST(Sin, Expression) {
    using Const = grad::sym::Constant<int>;
    EXPECT_TRUE((grad::sym::IsExpression<grad::sym::Sin<Const>>::val));
}

TEST(Sin, Resolve) {
    grad::sym::Constant<double> a{17};
    grad::sym::Sin<decltype(a)> sin{a};
    EXPECT_DOUBLE_EQ(sin.resolve(), std::sin(17));
}

TEST(Sin, Gradient) {
    grad::sym::Variable<double> x{0};
    grad::sym::Sin<decltype(x)> y{x};
    EXPECT_DOUBLE_EQ(grad::sym::gradient(y, x).resolve(), 1);
}
