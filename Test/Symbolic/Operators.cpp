#include "Symbolic/Operators.hpp"

#include <gtest/gtest.h>

#include "Symbolic/Constant.hpp"

TEST(Operators, OperatorPlus) {
    grad::sym::Constant<int> c{42};
    auto res = c + c;
    EXPECT_TRUE((std::same_as<decltype(res), grad::sym::Add<decltype(c), decltype(c)>>) );
    EXPECT_EQ(res.resolve(), 42 + 42);
}

TEST(Operators, OperatorTimes) {
    grad::sym::Constant<int> c{42};
    auto res = c * c;
    EXPECT_TRUE((std::same_as<decltype(res), grad::sym::Mul<decltype(c), decltype(c)>>) );
    EXPECT_EQ(res.resolve(), 42 * 42);
}

TEST(Operators, OperatorDiv) {
    grad::sym::Constant<double> c{42};
    grad::sym::Constant<double> d{17};
    auto res = c / d;
    EXPECT_TRUE((std::same_as<decltype(res), grad::sym::Div<decltype(c), decltype(d)>>) );
    EXPECT_DOUBLE_EQ(res.resolve(), 42.0 / 17);
}

TEST(Operators, OperatorSub) {
    grad::sym::Constant<int> c{42};
    grad::sym::Constant<int> d{17};
    auto res = c - d;
    EXPECT_TRUE((std::same_as<decltype(res), grad::sym::Sub<decltype(c), decltype(d)>>) );
    EXPECT_DOUBLE_EQ(res.resolve(), 42 - 17);
}
