#include <gtest/gtest.h>

#include "Symbolic/Add.hpp"
#include "Symbolic/Constant.hpp"

TEST(Add, Expression) {
    using Const = grad::sym::Constant<int, 0>;
    EXPECT_TRUE((grad::sym::IsExpression<grad::sym::Add<Const, Const>>::val));
}

TEST(Add, Resolve) {
    grad::sym::Constant<int, 17> a;
    grad::sym::Constant<int, 42> b;
    grad::sym::Add<decltype(a), decltype(b)> add{a, b};
    EXPECT_EQ(add.resolve(), 17+42);
}

TEST(Add, GradA) {
    grad::sym::Variable<int> a{17};
    grad::sym::Variable<int> b{42};
    grad::sym::Add<decltype(a), decltype(b)> add{a, b};
    EXPECT_EQ(grad::sym::gradient(a, a).resolve(), 1);
}

TEST(Add, GradB) {
    grad::sym::Variable<int> a{17};
    grad::sym::Variable<int> b{42};
    grad::sym::Add<decltype(a), decltype(b)> add{a, b};
    EXPECT_EQ(grad::sym::gradient(add, b).resolve(), 1);
}

TEST(Add, GradNone) {
    grad::sym::Variable<int> a{17};
    grad::sym::Variable<int> b{42};
    grad::sym::Variable<int> c{42};
    grad::sym::Add<decltype(a), decltype(b)> add{a, b};
    EXPECT_EQ(grad::sym::gradient(add, c).resolve(), 0);
}

TEST(Add, GradBoth) {
    grad::sym::Variable<int> a{17};
    grad::sym::Add<decltype(a), decltype(a)> add{a, a};
    EXPECT_EQ(grad::sym::gradient(add, a).resolve(), 2);
}
