#include <gtest/gtest.h>

#include "Symbolic/Variable.hpp"

TEST(Variable, Expression) {
    EXPECT_TRUE(grad::sym::IsExpression<grad::sym::Variable<int>>::val);
}

TEST(Variable, Resolve) {
    grad::sym::Variable<int> a{42};
    EXPECT_EQ(a.resolve(), 42);
}

TEST(Variable, Set) {
    grad::sym::Variable<int> a{42};
    a.set(17);
    EXPECT_EQ(a.resolve(), 17);
}

TEST(Variable, GradEqual) {
    grad::sym::Variable<int> a{42};
    EXPECT_EQ(a.grad(a).resolve(), 1);
}

TEST(Variable, GradNEqual) {
    grad::sym::Variable<int> a{42};
    grad::sym::Variable<int> b{42};
    EXPECT_EQ(a.grad(b).resolve(), 0);
}
