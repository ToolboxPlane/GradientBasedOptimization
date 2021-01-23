#include <gtest/gtest.h>

#include "Symbolic/Constant.hpp"

#include "Symbolic/Mul.hpp"

TEST(Mul, Expression) {
    using Const = grad::sym::Constant<int>;
    EXPECT_TRUE((grad::sym::IsExpression<grad::sym::Mul<Const, Const>>::val));
}

TEST(Mul, Resolve) {
    grad::sym::Constant<int> a{17};
    grad::sym::Constant<int> b{42};
    grad::sym::Mul<decltype(a), decltype(b)> mul{a, b};
    EXPECT_EQ(mul.resolve(), 17*42);
}

TEST(Mul, GradA) {
    grad::sym::Variable<int> a{17};
    grad::sym::Variable<int> b{42};
    grad::sym::Mul<decltype(a), decltype(b)> mul{a, b};
    EXPECT_EQ(grad::sym::gradient(mul, a).resolve(), 42);
}

TEST(Mul, GradB) {
    grad::sym::Variable<int> a{17};
    grad::sym::Variable<int> b{42};
    grad::sym::Mul<decltype(a), decltype(b)> mul{a, b};
    EXPECT_EQ(grad::sym::gradient(mul, b).resolve(), 17);
}

TEST(Mul, GradNone) {
    grad::sym::Variable<int> a{17};
    grad::sym::Variable<int> b{42};
    grad::sym::Variable<int> c{42};
    grad::sym::Mul<decltype(a), decltype(b)> mul{a, b};
    EXPECT_EQ(grad::sym::gradient(mul, c).resolve(), 0);
}

TEST(Mul, GradBoth) {
    grad::sym::Variable<int> a{17};
    grad::sym::Mul<decltype(a), decltype(a)> mul{a, a};
    EXPECT_EQ(grad::sym::gradient(mul, a).resolve(), 2*17);
}


TEST(Mul, IsConstantCC) {
    using C = grad::sym::Constant<int>;
    EXPECT_TRUE((grad::sym::Mul<C, C>::isConstant()));
}

TEST(Mul, IsConstantCV) {
    using C = grad::sym::Constant<int>;
    using V = grad::sym::Variable<int>;
    EXPECT_FALSE((grad::sym::Mul<C, V>::isConstant()));
}

TEST(Mul, IsConstantVC) {
    using C = grad::sym::Constant<int>;
    using V = grad::sym::Variable<int>;
    EXPECT_FALSE((grad::sym::Mul<V, C>::isConstant()));
}

TEST(Mul, IsConstantVV) {
    using V = grad::sym::Variable<int>;
    EXPECT_FALSE((grad::sym::Mul<V, V>::isConstant()));
}
