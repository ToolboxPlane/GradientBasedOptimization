#include <gtest/gtest.h>

#include "Symbolic/Grad.hpp"

#include "Symbolic/Add.hpp"
#include "Symbolic/Constant.hpp"

TEST(Add, Expression) {
    using Const = grad::sym::Constant<int, 0>;
    EXPECT_TRUE((grad::sym::IsExpression<grad::sym::Add<Const, Const>>::val));
}

TEST(Add, Grad) {
    using Const = grad::sym::Constant<int, 0>;
    EXPECT_TRUE((grad::sym::IsGrad<grad::sym::Add<Const, Const>>::val));
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
    EXPECT_EQ(add.grad(a).resolve(), 1);
}

TEST(Add, GradB) {
    grad::sym::Variable<int> a{17};
    grad::sym::Variable<int> b{42};
    grad::sym::Add<decltype(a), decltype(b)> add{a, b};
    EXPECT_EQ(add.grad(b).resolve(), 1);
}

TEST(Add, GradNone) {
    grad::sym::Variable<int> a{17};
    grad::sym::Variable<int> b{42};
    grad::sym::Variable<int> c{42};
    grad::sym::Add<decltype(a), decltype(b)> add{a, b};
    EXPECT_EQ(add.grad(c).resolve(), 0);
}

TEST(Add, GradBoth) {
    grad::sym::Variable<int> a{17};
    grad::sym::Add<decltype(a), decltype(a)> add{a, a};
    EXPECT_EQ(add.grad(a).resolve(), 2);
}
