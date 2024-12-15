#include <string>

#include <gtest/gtest.h>
#include "solution.hpp"

TEST(Constructors, Default) {
    Thirteen num;
    EXPECT_EQ(num.toString(), "0");
}

TEST(Constructors, InitializerList) {
    Thirteen num = {1, 'A', 2, 'C'};
    EXPECT_EQ(num.toString(), "1A2C");

    Thirteen num1 = {12, 5, 'A', 0};
    EXPECT_EQ(num1.toString(), "C5A0");
}

TEST(Constructor, Copy) {
    Thirteen num = {3, 'B', 1, 'C'};
    Thirteen num1 = num;
    EXPECT_EQ(num.toString(), num1.toString());
}

TEST(Constructor, Move) {
    Thirteen num = {3, 'B', 1, 'C'};
    Thirteen num1 = std::move(num);
    EXPECT_EQ(num.toString(), "0");
    EXPECT_EQ(num1.toString(), "3B1C");
}

TEST(Operator, Copy) {
    Thirteen num = {4, 'A', 3, 2, 'A', 'B'};
    Thirteen num1 = {2, 1, 'B', 5, 12, 9};
    num1 = num;
    EXPECT_EQ(num.toString(), "4A32AB");
    EXPECT_EQ(num1.toString(), "4A32AB");
}

TEST(Operator, Plus) {
    Thirteen num = {1, 2, 3, 4};
    Thirteen num1 = {1, 2, 3, 4, 5};
    EXPECT_EQ((num + num1).toString(), "13579");

    Thirteen num2 = {4, 5, 'A', 1, 3, 'B'};
    Thirteen num3 = {'C', 3, 2, 'B', 1, 2, 1, 'B', 'C'};
    EXPECT_EQ((num2 + num3).toString(), "C3326C32A");
}

TEST(Operator, PlusEquals) {
    Thirteen num = {4, 5, 10, 1, 3, 11};
    Thirteen num1 = {12, 3, 2, 11, 1, 2, 1, 11, 12};
    num += num1;
    EXPECT_EQ(num.toString(), "C3326C32A");
}

TEST(Operator, Minus) {
    Thirteen num = {12, 3, 3, 2, 6, 12, 3, 2, 10};
    Thirteen num1 = {12, 3, 2, 11, 1, 2, 1, 11, 12};
    EXPECT_EQ((num - num1).toString(), "45A13B");
}

TEST(Operator, MinusEquals) {   
    Thirteen num = {1, 2, 3, 4, 5};
    Thirteen num1 = {3};
    num -= num1;
    EXPECT_EQ(num.toString(), "12342");
}

TEST(Operator, Equal) {
    Thirteen num = {12, 3, 3, 2, 6, 12, 3, 2, 10};
    Thirteen num1 = {12, 3, 3, 2, 6, 12, 3, 2, 10};
    Thirteen num2 = {11, 4, 5, 10, 6, 7 ,8};
    EXPECT_EQ(num1 == num, true);
    EXPECT_EQ(num2 == num, false);
}


TEST(Operator, GreaterThan) {
    Thirteen num = {10, 3, 2, 1};
    Thirteen num1 = {11, 4, 5, 6};
    Thirteen num2 = {10, 3, 2, 0};
    EXPECT_EQ(num1 > num, true);
    EXPECT_EQ(num2 > num, false);
}

TEST(Operator, LessThan) {
    Thirteen num = {10, 3, 2, 1};
    Thirteen num1 = {11, 4, 5, 6};
    Thirteen num2 = {10, 3, 2, 0};
    EXPECT_EQ(num1 < num, false);
    EXPECT_EQ(num2 < num, true);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}