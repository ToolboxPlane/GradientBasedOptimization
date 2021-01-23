/**
 * @file Constant.cpp
 * @author paul
 * @date 25.08.20
 * Description here TODO
 */

#include <gtest/gtest.h>

#include "Symbolic/Constant.hpp"

TEST(Constant, Expression) {
    EXPECT_TRUE((grad::sym::IsExpression<grad::sym::Constant<int>>::val));
}

TEST(Constant, Resolve) {
    grad::sym::Constant<int> c{42};

    EXPECT_EQ(c.resolve(), 42);
}

TEST(Constant, GradResolve) {
    grad::sym::Constant<int> c{42};

    EXPECT_EQ(grad::sym::gradient(c, grad::sym::Variable<int>{0}).resolve(), 0);
}

TEST(Constant, IsConstant) {
    EXPECT_TRUE(grad::sym::Constant<int>::isConstant());
}
