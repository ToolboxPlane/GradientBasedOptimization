/**
 * @file Constant.cpp
 * @author paul
 * @date 25.08.20
 * Description here TODO
 */

#include <gtest/gtest.h>

#include "Constant.hpp"

TEST(Constant, Resolve) {
    grad::Constant<int, 42> c;

    EXPECT_EQ(c.resolve(), 42);
}
