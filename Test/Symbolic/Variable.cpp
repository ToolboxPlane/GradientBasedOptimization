#include "Symbolic/Variable.hpp"

#include <gtest/gtest.h>

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
    EXPECT_EQ(grad::sym::gradient(a, a).resolve(), 1);
}

TEST(Variable, GradNEqual) {
    grad::sym::Variable<int> a{42};
    grad::sym::Variable<int> b{42};
    EXPECT_EQ(grad::sym::gradient(a, b).resolve(), 0);
}

TEST(Variable, IsConstant) {
    EXPECT_FALSE(grad::sym::Variable<int>::isConstant());
}
