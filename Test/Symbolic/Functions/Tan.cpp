#include <gtest/gtest.h>
#include <cmath>

#include "Symbolic/Functions/Tan.hpp"

#include "Symbolic/Constant.hpp"

TEST(Tan, Expression) {
    using Const = grad::sym::Constant<int>;
    EXPECT_TRUE((grad::sym::IsExpression<grad::sym::Tan<Const>>::val));
}

TEST(Tan, Resolve) {
    grad::sym::Constant<double> a{17};
    grad::sym::Tan<decltype(a)> tan{a};
    EXPECT_DOUBLE_EQ(tan.resolve(), std::tan(17));
}

TEST(Tan, Gradient) {
    grad::sym::Variable<double> x{0};
    grad::sym::Tan<decltype(x)> y{x};
    EXPECT_DOUBLE_EQ(grad::sym::gradient(y, x).resolve(), 1);
}

TEST(Tan, IsConstantC) {
    using C = grad::sym::Constant<int>;
    EXPECT_TRUE((grad::sym::Tan<C>::isConstant()));
}

TEST(Tan, IsConstantV) {
    using V = grad::sym::Variable<int>;
    EXPECT_FALSE((grad::sym::Tan<V>::isConstant()));
}
