#pragma once

#include <cmath>
#include <iostream>
#include <vector>

class Figure {
public:
    virtual ~Figure() = default;

    virtual double Area() const = 0;
    virtual std::pair<double, double> GeometricCenter() const = 0;

    virtual void PrintVertices(std::ostream& out) const = 0;
    virtual void InputVertices(std::istream& in) = 0;

    friend std::ostream& operator<<(std::ostream& out, const Figure& figure) {
        figure.PrintVertices(out);
        return out;
    }

    friend std::istream& operator>>(std::istream& in, Figure& figure){
        figure.InputVertices(in);
        return in;
    }

    virtual Figure& operator=(const Figure& other) = 0;
    virtual bool operator==(const Figure& other) const = 0;

    operator double() const {
        return Area();
    }
};

class Rhombus : public Figure {
public:
    Rhombus() : center{0, 0}, diagonal1(0), diagonal2(0) {}
    Rhombus(const std::pair<double, double>& c, double d1, double d2) : center(c), diagonal1(d1), diagonal2(d2) {}

    double Area() const override {
        return (diagonal1 * diagonal2) / 2;
    }

    std::pair<double, double> GeometricCenter() const override {
        return center;
    }

    void PrintVertices(std::ostream& out) const override {
        out << "Rhombus with center at (" << center.first << ", " << center.second << ")";
    }

    void InputVertices(std::istream& in) override {
        std::cout << "Enter center (x, y) and diagonals d1, d2: ";
        in >> center.first >> center.second >> diagonal1 >> diagonal2;
    }

    Figure& operator=(const Figure& other) override {
        if (auto* r = dynamic_cast<const Rhombus*>(&other)) {
            center = r->center;
            diagonal1 = r->diagonal1;
            diagonal2 = r->diagonal2;
        }
        return *this;
    }

    bool operator==(const Figure& other) const override {
        if (auto* r = dynamic_cast<const Rhombus*>(&other)) {
            return center == r->center && diagonal1 == r->diagonal1 && diagonal2 == r->diagonal2;
        }
        return false;
    }
private:
    std::pair<double, double> center;
    double diagonal1, diagonal2;
};

class Pentagon : public Figure {
public:
    Pentagon() : center{0, 0}, side(0) {}
    Pentagon(const std::pair<double, double>& c, double s) : center(c), side(s) {}

    double Area() const override {
        return (5 * side * side) / (4 * tan(M_PI / 5));
    }

    std::pair<double, double> GeometricCenter() const override {
        return center;
    }

    void PrintVertices(std::ostream& out) const override {
        out << "Pentagon with center at (" << center.first << ", " << center.second << ")";
    }

    void InputVertices(std::istream& in) override {
        std::cout << "Enter center (x, y) and side length: ";
        in >> center.first >> center.second >> side;
    }

    Figure& operator=(const Figure& other) override {
        if (auto* p = dynamic_cast<const Pentagon*>(&other)) {
            center = p->center;
            side = p->side;
        }
        return *this;
    }

    bool operator==(const Figure& other) const override {
        if (auto* p = dynamic_cast<const Pentagon*>(&other)) {
            return center == p->center && side == p->side;
        }
        return false;
    }
private:
    std::pair<double, double> center;
    double side;
};

class Hexagon : public Figure {
public:
    Hexagon() : center{0, 0}, side(0) {}
    Hexagon(const std::pair<double, double>& c, double s) : center(c), side(s) {}

    double Area() const override {
        return (3 * sqrt(3) * side * side) / 2;
    }

    std::pair<double, double> GeometricCenter() const override {
        return center;
    }

    void PrintVertices(std::ostream& out) const override {
        out << "Hexagon with center at (" << center.first << ", " << center.second << ")";
    }

    void InputVertices(std::istream& in) override {
        std::cout << "Enter center (x, y) and side length: ";
        in >> center.first >> center.second >> side;
    }

    Figure& operator=(const Figure& other) override {
        if (auto* h = dynamic_cast<const Hexagon*>(&other)) {
            center = h->center;
            side = h->side;
        }
        return *this;
    }

    bool operator==(const Figure& other) const override {
        if (auto* h = dynamic_cast<const Hexagon*>(&other)) {
            return center == h->center && side == h->side;
        }
        return false;
    }
private:
    std::pair<double, double> center;
    double side;
};

