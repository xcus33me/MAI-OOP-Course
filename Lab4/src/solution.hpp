#pragma once

#include <cmath>
#include <iostream>
#include <memory>
#include <vector>
#include <concepts>

template <typename T>
concept Scalar = std::is_arithmetic_v<T>;

template <Scalar T>
class Point {
public:
    T x, y;
    Point(T _x = 0, T _y = 0) : x(_x), y(_y) {}

    bool operator==(const Point<T>& other) const {
        return x == other.x && y == other.y;
    }
};

template <Scalar T>
class Figure {
public:
    virtual ~Figure() = default;

    virtual double Area() const = 0;
    virtual Point<T> GeometricCenter() const = 0;
    virtual void PrintVertices(std::ostream& out) const = 0;
    virtual void InputVertices(std::istream& in) = 0;

    friend std::ostream& operator<<(std::ostream& out, const Figure& figure) {
        figure.PrintVertices(out);
        return out;
    }

    friend std::istream& operator>>(std::istream& in, Figure& figure) {
        figure.InputVertices(in);
        return in;
    }

    virtual Figure& operator=(const Figure& other) = 0;
    virtual bool operator==(const Figure& other) const = 0;

    operator double() const {
        return Area();
    }
};

template <Scalar T>
class Rhombus : public Figure<T> {
public:
    Rhombus() = default;
    Rhombus(const Point<T>& c, T d1, T d2) : center(c), diagonal1(d1), diagonal2(d2) {}

    double Area() const override {
        return (diagonal1 * diagonal2) / 2;
    }

    Point<T> GeometricCenter() const override {
        return center;
    }

    void PrintVertices(std::ostream& out) const override {
        out << "Rhombus with center at (" << center.x << ", " << center.y << ")";
    }

    void InputVertices(std::istream& in) override {
        in >> center.x >> center.y >> diagonal1 >> diagonal2;
    }

    Rhombus& operator=(const Figure<T>& other) override {
        if (auto* r = dynamic_cast<const Rhombus*>(&other)) {
            center = r->center;
            diagonal1 = r->diagonal1;
            diagonal2 = r->diagonal2;
        }
        return *this;
    }

    bool operator==(const Figure<T>& other) const override {
        if (auto* r = dynamic_cast<const Rhombus*>(&other)) {
            return center == r->center && diagonal1 == r->diagonal1 && diagonal2 == r->diagonal2;
        }
        return false;
    }

private:
    Point<T> center;
    T diagonal1{}, diagonal2{};
};

template <Scalar T>
class Pentagon : public Figure<T> {
public:
    Pentagon() = default;
    Pentagon(const Point<T>& c, T s) : center(c), side(s) {}

    double Area() const override {
        return (5 * side * side) / (4 * tan(M_PI / 5));
    }

    Point<T> GeometricCenter() const override {
        return center;
    }

    void PrintVertices(std::ostream& out) const override {
        out << "Pentagon with center at (" << center.x << ", " << center.y << ")";
    }

    void InputVertices(std::istream& in) override {
        in >> center.x >> center.y >> side;
    }

    Pentagon& operator=(const Figure<T>& other) override {
        if (auto* p = dynamic_cast<const Pentagon*>(&other)) {
            center = p->center;
            side = p->side;
        }
        return *this;
    }

    bool operator==(const Figure<T>& other) const override {
        if (auto* p = dynamic_cast<const Pentagon*>(&other)) {
            return center == p->center && side == p->side;
        }
        return false;
    }

private:
    Point<T> center;
    T side{};
};

template <Scalar T>
class Hexagon : public Figure<T> {
public:
    Hexagon() = default;
    Hexagon(const Point<T>& c, T s) : center(c), side(s) {}

    double Area() const override {
        return (3 * sqrt(3) * side * side) / 2;
    }

    Point<T> GeometricCenter() const override {
        return center;
    }

    void PrintVertices(std::ostream& out) const override {
        out << "Hexagon with center at (" << center.x << ", " << center.y << ")";
    }

    void InputVertices(std::istream& in) override {
        in >> center.x >> center.y >> side;
    }

    Hexagon& operator=(const Figure<T>& other) override {
        if (auto* h = dynamic_cast<const Hexagon*>(&other)) {
            center = h->center;
            side = h->side;
        }
        return *this;
    }

    bool operator==(const Figure<T>& other) const override {
        if (auto* h = dynamic_cast<const Hexagon*>(&other)) {
            return center == h->center && side == h->side;
        }
        return false;
    }

private:
    Point<T> center;
    T side{};
};
