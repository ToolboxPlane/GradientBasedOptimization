#include <gtest/gtest.h>

#include "Util/EnableOr.hpp"

TEST(EnableOr, TrueType) {
    EXPECT_TRUE((std::same_as<grad::util::EnableOrType<true, int, double>, int>));
}

TEST(EnableOr, FalseType) {
    EXPECT_TRUE((std::same_as<grad::util::EnableOrType<false, int, double>, double>));
}
