/**
 * @file Constant.cpp
 * @author paul
 * @date 25.08.20
 * Description here TODO
 */

#include <gtest/gtest.h>

#include "Symbolic/Constant.hpp"

TEST(Constant, Expression) {
    EXPECT_TRUE((grad::sym::IsExpression<grad::sym::Constant<int, 0>>::val));
}

TEST(Constant, Resolve) {
    grad::sym::Constant<int, 42> c;

    EXPECT_EQ(c.resolve(), 42);
}

TEST(Constant, Grad) {
    grad::sym::Constant<int, 42> c;

    EXPECT_EQ(c.grad(grad::sym::Variable<int>{0}).resolve(), 0);
}
