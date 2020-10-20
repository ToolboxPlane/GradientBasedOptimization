#include <gtest/gtest.h>

#include "Symbolic/Operators.hpp"

#include "Symbolic/Constant.hpp"

TEST(Operators, OperatorPlus) {
    grad::sym::Constant<int, 42> c;
    auto res = c + c;
    EXPECT_TRUE((std::same_as<decltype(res), grad::sym::Add<decltype(c), decltype(c)>>));
    EXPECT_EQ(res.resolve(), 42+42);
}

TEST(Operators, OperatorTimes) {
    grad::sym::Constant<int, 42> c;
    auto res = c * c;
    EXPECT_TRUE((std::same_as<decltype(res), grad::sym::Mul<decltype(c), decltype(c)>>));
    EXPECT_EQ(res.resolve(), 42*42);
}
