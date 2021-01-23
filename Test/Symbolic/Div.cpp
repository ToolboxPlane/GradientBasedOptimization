#include <gtest/gtest.h>

#include "Symbolic/Constant.hpp"

#include "Symbolic/Div.hpp"

TEST(Div, Expression) {
    using Const = grad::sym::Constant<int>;
    EXPECT_TRUE((grad::sym::IsExpression<grad::sym::Div<Const, Const>>::val));
}

TEST(Div, Resolve) {
    grad::sym::Constant<int> a{42};
    grad::sym::Constant<int> b{2};
    grad::sym::Div<decltype(a), decltype(b)> div{a, b};
    EXPECT_EQ(div.resolve(), 21);
}

TEST(Div, GradA) {
    grad::sym::Variable<double> a{42};
    grad::sym::Variable<double> b{2};
    grad::sym::Div<decltype(a), decltype(b)> div{a, b};
    EXPECT_DOUBLE_EQ(grad::sym::gradient(div, a).resolve(), 0.5);
}

TEST(Div, GradB) {
    grad::sym::Variable<int> a{17};
    grad::sym::Variable<int> b{42};
    grad::sym::Div<decltype(a), decltype(b)> div{a, b};
    EXPECT_EQ(grad::sym::gradient(div, b).resolve(), 17/(42*42));
}

TEST(Div, GradNone) {
    grad::sym::Variable<int> a{17};
    grad::sym::Variable<int> b{42};
    grad::sym::Variable<int> c{42};
    grad::sym::Div<decltype(a), decltype(b)> div{a, b};
    EXPECT_EQ(grad::sym::gradient(div, c).resolve(), 0);
}

TEST(Div, GradBoth) {
    grad::sym::Variable<int> a{17};
    grad::sym::Div<decltype(a), decltype(a)> div{a, a};
    EXPECT_EQ(grad::sym::gradient(div, a).resolve(), 0);
}


TEST(Div, IsConstantCC) {
    using C = grad::sym::Constant<int>;
    EXPECT_TRUE((grad::sym::Div<C, C>::isConstant()));
}

TEST(Div, IsConstantCV) {
    using C = grad::sym::Constant<int>;
    using V = grad::sym::Variable<int>;
    EXPECT_FALSE((grad::sym::Div<C, V>::isConstant()));
}

TEST(Div, IsConstantVC) {
    using C = grad::sym::Constant<int>;
    using V = grad::sym::Variable<int>;
    EXPECT_FALSE((grad::sym::Div<V, C>::isConstant()));
}

TEST(Div, IsConstantVV) {
    using V = grad::sym::Variable<int>;
    EXPECT_FALSE((grad::sym::Div<V, V>::isConstant()));
}

