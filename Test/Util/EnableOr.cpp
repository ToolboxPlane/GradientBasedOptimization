#include <gtest/gtest.h>

#include "Util/EnableOr.hpp"

TEST(EnableOr, TrueType) {
    EXPECT_TRUE((std::same_as<grad::util::TernaryType<true, int, double>, int>));
}

TEST(EnableOr, FalseType) {
    EXPECT_TRUE((std::same_as<grad::util::TernaryType<false, int, double>, double>));
}
