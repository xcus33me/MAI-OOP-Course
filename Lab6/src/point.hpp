#pragma once 

#include <cmath>
#include <iostream>

class Point {
public:
    Point(int x, int y) : x(x), y(y) {
        if (x < 0 || x > 500 || y < 0 || y > 500) {
            throw std::out_of_range("Coordinates must be within the range [0, 500].");
        }
    }

    int getX() const { return x; }
    int getY() const { return y; }

    double distance_to(const Point& other) const {
        return std::sqrt(std::pow(x - other.x, 2) + std::pow(y - other.y, 2));
    }

    void print() const {
        std::cout << "(" << x << ", " << y << ")";
    }

private:
    int x, y;
};