#include <gtest/gtest.h>

#include <Variable.hpp>

TEST(Variable, Resolve) {
    grad::Variable<int, 42> a;
    EXPECT_EQ(a.resolve(), 42);
}

TEST(Variable, Set) {
    grad::Variable<int, 42> a;
    a.set(17);
    EXPECT_EQ(a.resolve(), 17);
}
