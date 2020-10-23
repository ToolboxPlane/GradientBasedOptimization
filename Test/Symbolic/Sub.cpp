#include <gtest/gtest.h>

#include "Symbolic/Sub.hpp"
#include "Symbolic/Constant.hpp"

TEST(Sub, Expression) {
    using Const = grad::sym::Constant<int>;
    EXPECT_TRUE((grad::sym::IsExpression<grad::sym::Sub<Const, Const>>::val));
}

TEST(Sub, Resolve) {
    grad::sym::Constant<int> a{17};
    grad::sym::Constant<int> b{42};
    grad::sym::Sub<decltype(a), decltype(b)> sub{a, b};
    EXPECT_EQ(sub.resolve(), 17-42);
}

TEST(Sub, GradA) {
    grad::sym::Variable<int> a{17};
    grad::sym::Variable<int> b{42};
    grad::sym::Sub<decltype(a), decltype(b)> sub{a, b};
    EXPECT_EQ(grad::sym::gradient(a, a).resolve(), 1);
}

TEST(Sub, GradB) {
    grad::sym::Variable<int> a{17};
    grad::sym::Variable<int> b{42};
    grad::sym::Sub<decltype(a), decltype(b)> sub{a, b};
    EXPECT_EQ(grad::sym::gradient(sub, b).resolve(), -1);
}

TEST(Sub, GradNone) {
    grad::sym::Variable<int> a{17};
    grad::sym::Variable<int> b{42};
    grad::sym::Variable<int> c{42};
    grad::sym::Sub<decltype(a), decltype(b)> sub{a, b};
    EXPECT_EQ(grad::sym::gradient(sub, c).resolve(), 0);
}

TEST(Sub, GradBoth) {
    grad::sym::Variable<int> a{17};
    grad::sym::Sub<decltype(a), decltype(a)> sub{a, a};
    EXPECT_EQ(grad::sym::gradient(sub, a).resolve(), 0);
}
