#include <string>

#include <gtest/gtest.h>
#include "solution.hpp"

TEST(BasicExamples, am) {
    EXPECT_EQ(convertTo24HourFormat(8, 30, "am"), "0830");
}

TEST(BasicExamples, em) {
    EXPECT_EQ(convertTo24HourFormat(8, 30, "pm"), "2030");
}

TEST(Additional, AMTimes) {
    EXPECT_EQ(convertTo24HourFormat(1, 5, "am"), "0105");
    EXPECT_EQ(convertTo24HourFormat(12, 0, "am"), "0000");
    EXPECT_EQ(convertTo24HourFormat(4, 15, "am"), "0415");
}

TEST(Additional, PMTimes) {
    EXPECT_EQ(convertTo24HourFormat(1, 5, "pm"), "1305");
    EXPECT_EQ(convertTo24HourFormat(12, 0, "pm"), "1200");
    EXPECT_EQ(convertTo24HourFormat(4, 15, "pm"), "1615");
}

TEST(Additional, EdgeCases) {
    EXPECT_EQ(convertTo24HourFormat(12, 59, "am"), "0059");
    EXPECT_EQ(convertTo24HourFormat(12, 59, "pm"), "1259");
    EXPECT_EQ(convertTo24HourFormat(11, 59, "am"), "1159");
    EXPECT_EQ(convertTo24HourFormat(11, 59, "pm"), "2359");
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
