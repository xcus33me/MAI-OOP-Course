#include <iostream>

#include "solution.hpp"

class FigureManager {
public:
    void AddFigure() {
        std::cout << "Choose figure type: 1 - Rhombus, 2 - Pentagon, 3 - Hexagon: ";
        int choice;
        std::cin >> choice;

        Figure* figure = nullptr;
        switch (choice) {
            case 1:
                figure = CreateRhombus();
                break;
            case 2:
                figure = CreatePentagon();
                break;
            case 3:
                figure = CreateHexagon();
                break;
            default:
                std::cout << "Invalid choice!" << std::endl;
                return;
        }
        figures.push_back(figure);
    }

    void RemoveFigure(size_t index) {
        if (index < figures.size()) {
            delete figures[index]; 
            figures.erase(figures.begin() + index);
            std::cout << "Figure removed!" << std::endl;
        } else {
            std::cout << "Invalid index!" << std::endl;
        }
    }

    double CalculateTotalArea() const {
        double totalArea = 0;
        for (const auto& figure : figures) {
            totalArea += static_cast<double>(*figure);
        }
        return totalArea;
    }

    void PrintAllFigures() const {
        int counter = 1;
        for (const auto& figure : figures) {
            std::cout << counter << ". " << *figure << std::endl;
            std::cout << "Geometric Center: (" << figure->GeometricCenter().first << ", "
                      << figure->GeometricCenter().second << ")" << std::endl;
            std::cout << "Area: " << static_cast<double>(*figure) << std::endl;
            ++counter;
        }
    }

    ~FigureManager() {
        for (auto figure : figures) {
            delete figure;
        }
    }

private:
    std::vector<Figure*> figures;

    Rhombus* CreateRhombus() {
        std::pair<double, double> center;
        double diagonal1, diagonal2;
        std::cout << "Enter center (x, y) and diagonals d1, d2: ";
        std::cin >> center.first >> center.second >> diagonal1 >> diagonal2;
        return new Rhombus(center, diagonal1, diagonal2);
    }

    Pentagon* CreatePentagon() {
        std::pair<double, double> center;
        double side;
        std::cout << "Enter center (x, y) and side length: ";
        std::cin >> center.first >> center.second >> side;
        return new Pentagon(center, side);
    }

    Hexagon* CreateHexagon() {
        std::pair<double, double> center;
        double side;
        std::cout << "Enter center (x, y) and side length: ";
        std::cin >> center.first >> center.second >> side;
        return new Hexagon(center, side);
    }
};