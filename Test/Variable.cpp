#include <gtest/gtest.h>

#include "ConceptUtil.hpp"

#include <Variable.hpp>

TEST(Variable, Expression) {
    EXPECT_TRUE(IsExpression<grad::Variable<int>>::val);
}

TEST(Variable, Resolve) {
    grad::Variable<int> a{42};
    EXPECT_EQ(a.resolve(), 42);
}

TEST(Variable, Set) {
    grad::Variable<int> a{42};
    a.set(17);
    EXPECT_EQ(a.resolve(), 17);
}

TEST(Variable, GradEqual) {
    grad::Variable<int> a{42};
    EXPECT_EQ(a.grad(a).resolve(), 1);
}

TEST(Variable, GradNEqual) {
    grad::Variable<int> a{42};
    grad::Variable<int> b{42};
    EXPECT_EQ(a.grad(b).resolve(), 0);
}
