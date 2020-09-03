#include <gtest/gtest.h>

#include "ConceptUtil.hpp"

#include "Add.hpp"
#include "Constant.hpp"

TEST(Add, Expression) {
    using Const = grad::Constant<int, 0>;
    EXPECT_TRUE((IsExpression<grad::Add<Const, Const>>::val));
}

TEST(Add, Resolve) {
    grad::Constant<int, 17> a;
    grad::Constant<int, 42> b;
    grad::Add<decltype(a), decltype(b)> add{a, b};
    EXPECT_EQ(add.resolve(), 17+42);
}

TEST(Add, GradA) {
    grad::Variable<int> a{17};
    grad::Variable<int> b{42};
    grad::Add<decltype(a), decltype(b)> add{a, b};
    EXPECT_EQ(add.grad(a).resolve(), 1);
}

TEST(Add, GradB) {
    grad::Variable<int> a{17};
    grad::Variable<int> b{42};
    grad::Add<decltype(a), decltype(b)> add{a, b};
    EXPECT_EQ(add.grad(b).resolve(), 1);
}

TEST(Add, GradNone) {
    grad::Variable<int> a{17};
    grad::Variable<int> b{42};
    grad::Variable<int> c{42};
    grad::Add<decltype(a), decltype(b)> add{a, b};
    EXPECT_EQ(add.grad(c).resolve(), 0);
}

TEST(Add, GradBoth) {
    grad::Variable<int> a{17};
    grad::Add<decltype(a), decltype(a)> add{a, a};
    EXPECT_EQ(add.grad(a).resolve(), 2);
}
