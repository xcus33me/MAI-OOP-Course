#include <string>

#include <gtest/gtest.h>
#include "solution.hpp"

TEST(RhombusTest, Area) {
    Rhombus r({0, 0}, 4, 6);
    EXPECT_DOUBLE_EQ(r.Area(), 12.0);
}

TEST(RhombusTest, GeometricCenter) {
    Rhombus r({3, 4}, 4, 6);
    auto center = r.GeometricCenter();
    EXPECT_DOUBLE_EQ(center.first, 3.0);
    EXPECT_DOUBLE_EQ(center.second, 4.0);
}

TEST(RhombusTest, OpEquality) {
    Rhombus r1({0, 0}, 4, 6);
    Rhombus r2({0, 0}, 4, 6);
    EXPECT_TRUE(r1 == r2);

    Rhombus r3({1, 1}, 4, 6);
    EXPECT_FALSE(r1 == r3);
}

TEST(PentagonTest, Area) {
    Pentagon p({0, 0}, 5);
    EXPECT_NEAR(p.Area(), 43.0119, 1e-3);
}

TEST(PentagonTest, GeometricCenter) {
    Pentagon p({2, 3}, 5);
    auto center = p.GeometricCenter();
    EXPECT_DOUBLE_EQ(center.first, 2.0);
    EXPECT_DOUBLE_EQ(center.second, 3.0);
}

TEST(PentagonTest, OpEquality) {
    Pentagon p1({0, 0}, 5);
    Pentagon p2({0, 0}, 5);
    EXPECT_TRUE(p1 == p2);

    Pentagon p3({1, 1}, 5);
    EXPECT_FALSE(p1 == p3);
}

TEST(HexagonTest, Area) {
    Hexagon h({0, 0}, 3);
    EXPECT_NEAR(h.Area(), 23.3827, 1e-3);
}

TEST(HexagonTest, GeometricCenter) {
    Hexagon h({4, 5}, 3);
    auto center = h.GeometricCenter();
    EXPECT_DOUBLE_EQ(center.first, 4.0);
    EXPECT_DOUBLE_EQ(center.second, 5.0);
}

TEST(HexagonTest, OpEquality) {
    Hexagon h1({0, 0}, 3);
    Hexagon h2({0, 0}, 3);
    EXPECT_TRUE(h1 == h2);

    Hexagon h3({1, 1}, 3);
    EXPECT_FALSE(h1 == h3);
}

TEST(FigureTest, InputOutputRhombus) {
    Rhombus r;
    std::istringstream input("0 0 4 6");
    input >> r;
    std::ostringstream output;
    output << r;
    EXPECT_EQ(output.str(), "Rhombus with center at (0, 0)");
}

TEST(FigureTest, InputOutputPentagon) {
    Pentagon p;
    std::istringstream input("2 3 5");
    input >> p;
    std::ostringstream output;
    output << p;
    EXPECT_EQ(output.str(), "Pentagon with center at (2, 3)");
}

TEST(FigureTest, InputOutputHexagon) {
    Hexagon h;
    std::istringstream input("4 5 3");
    input >> h;
    std::ostringstream output;
    output << h;
    EXPECT_EQ(output.str(), "Hexagon with center at (4, 5)");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}