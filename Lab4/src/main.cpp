#include <iostream>
#include "array.hpp"
#include "solution.hpp"

std::shared_ptr<Figure<double>> CreateFigure(int choice) {
    switch (choice) {
        case 1: {
            Point<double> center;
            double diagonal1, diagonal2;
            std::cout << "Enter center (x, y) and diagonals d1, d2: ";
            std::cin >> center.x >> center.y >> diagonal1 >> diagonal2;
            return std::make_shared<Rhombus<double>>(center, diagonal1, diagonal2);
        }
        case 2: {
            Point<double> center;
            double side;
            std::cout << "Enter center (x, y) and side length: ";
            std::cin >> center.x >> center.y >> side;
            return std::make_shared<Pentagon<double>>(center, side);
        }
        case 3: {
            Point<double> center;
            double side;
            std::cout << "Enter center (x, y) and side length: ";
            std::cin >> center.x >> center.y >> side;
            return std::make_shared<Hexagon<double>>(center, side);
        }
        default:
            std::cout << "Invalid choice!\n";
            return nullptr;
    }
}

int main() {
    Array<std::shared_ptr<Figure<double>>> figures;
    int option;

    while (true) {
        std::cout << "\nMenu:\n"
                  << "1. Add a figure\n"
                  << "2. Remove a figure by index\n"
                  << "3. Show all figures\n"
                  << "4. Calculate total area\n"
                  << "5. Exit\n"
                  << "Your choice: ";

        std::cin >> option;

        switch (option) {
            case 1: {
                std::cout << "Choose figure type: 1 - Rhombus, 2 - Pentagon, 3 - Hexagon: ";
                int choice;
                std::cin >> choice;
                auto figure = CreateFigure(choice);
                if (figure) {
                    figures.Add(figure);
                    std::cout << "Figure added.\n";
                }
                break;
            }
            case 2: {
                std::cout << "Enter index of figure to remove: ";
                size_t index;
                std::cin >> index;
                if (index <= figures.Size() && figures.Remove(index - 1)) {
                    std::cout << "Figure removed.\n";
                } else {
                    std::cout << "Invalid index.\n";
                }
                break;
            }
            case 3: {
                if (figures.Size() == 0) {
                    std::cout << "No figures to display.\n";
                } else {
                    for (size_t i = 0; i < figures.Size(); ++i) {
                        std::cout << i + 1 << ". " << *figures[i] << "\n"
                                  << "Geometric center: (" << figures[i]->GeometricCenter().x << ", "
                                  << figures[i]->GeometricCenter().y << ")\n"
                                  << "Area: " << static_cast<double>(figures[i]->Area()) << "\n";
                    }
                }
                break;
            }
            case 4: {
                double totalArea = 0;
                for (size_t i = 0; i < figures.Size(); ++i) {
                    totalArea += static_cast<double>(figures[i]->Area());
                }
                std::cout << "Total area of all figures: " << totalArea << "\n";
                break;
            }
            case 5:
                return 0;
            default:
                std::cout << "Invalid choice.\n";
        }
    }
}
