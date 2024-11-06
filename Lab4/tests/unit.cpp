#include <string>

#include <gtest/gtest.h>
#include "solution.hpp"

TEST(PointTest, OpEquality) {
    Point<int> p1(1, 2);
    Point<int> p2(1, 2);
    Point<int> p3(2, 3);

    EXPECT_TRUE(p1 == p2);

    EXPECT_FALSE(p1 == p3);
}

TEST(RhombusTest, AreaAndCenter) {
    Point<int> center(0, 0);
    Rhombus<int> rhombus(center, 4, 6);

    EXPECT_DOUBLE_EQ(rhombus.Area(), 12.0);

    EXPECT_EQ(rhombus.GeometricCenter(), center);
}

TEST(RhombusTest, OpEquality) {
    Point<int> center(0, 0);
    Rhombus<int> rhombus1(center, 4, 6);
    Rhombus<int> rhombus2(center, 4, 6);
    Rhombus<int> rhombus3(center, 3, 5);

    EXPECT_TRUE(rhombus1 == rhombus2);

    EXPECT_FALSE(rhombus1 == rhombus3);
}

TEST(PentagonTest, AreaAndCenter) {
    Point<int> center(0, 0);
    Pentagon<int> pentagon(center, 4);

    double expected_area = (5 * 4 * 4) / (4 * tan(M_PI / 5));
    EXPECT_DOUBLE_EQ(pentagon.Area(), expected_area);

    EXPECT_EQ(pentagon.GeometricCenter(), center);
}

TEST(PentagonTest, OpEquality) {
    Point<int> center(0, 0);
    Pentagon<int> pentagon1(center, 4);
    Pentagon<int> pentagon2(center, 4);
    Pentagon<int> pentagon3(center, 5);

    EXPECT_TRUE(pentagon1 == pentagon2);

    EXPECT_FALSE(pentagon1 == pentagon3);
}

TEST(HexagonTest, AreaAndCenter) {
    Point<int> center(0, 0);
    Hexagon<int> hexagon(center, 4);

    double expected_area = (3 * sqrt(3) * 4 * 4) / 2;
    EXPECT_DOUBLE_EQ(hexagon.Area(), expected_area);

    EXPECT_EQ(hexagon.GeometricCenter(), center);
}

TEST(HexagonTest, OpEquality) {
    Point<int> center(0, 0);
    Hexagon<int> hexagon1(center, 4);
    Hexagon<int> hexagon2(center, 4);
    Hexagon<int> hexagon3(center, 5);

    EXPECT_TRUE(hexagon1 == hexagon2);

    EXPECT_FALSE(hexagon1 == hexagon3);
}

TEST(FigureInputOutputTest, RhombusInputOutput) {
    std::istringstream input("0 0 4 6");
    Rhombus<int> rhombus;
    input >> rhombus;

    EXPECT_EQ(rhombus.GeometricCenter(), Point<int>(0, 0));
    EXPECT_DOUBLE_EQ(rhombus.Area(), 12.0);
}

TEST(FigureInputOutputTest, PentagonInputOutput) {
    std::istringstream input("0 0 4");
    Pentagon<int> pentagon;
    input >> pentagon;

    double expected_area = (5 * 4 * 4) / (4 * tan(M_PI / 5));
    EXPECT_DOUBLE_EQ(pentagon.Area(), expected_area);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}