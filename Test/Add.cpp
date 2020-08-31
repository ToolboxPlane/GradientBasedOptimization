#include <gtest/gtest.h>

#include "Add.hpp"
#include "Constant.hpp"

TEST(Add, Resolve) {
    grad::Constant<int, 17> a;
    grad::Constant<int, 42> b;
    grad::Add<decltype(a), decltype(b)> add{std::move(a), std::move(b)};
    EXPECT_EQ(add.resolve(), 17+42);
}
