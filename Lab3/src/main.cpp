#include <iostream>
#include <vector>

#include "solution.hpp"
#include "figure_manager.hpp"

int main() {
    FigureManager manager;

    while (true) {
        std::cout << "\nMenu:\n"
                  << "1. Add a figure\n"
                  << "2. Remove a figure by index\n"
                  << "3. Show all figures\n"
                  << "4. Calculate total area\n"
                  << "5. Exit\n"
                  << "Your choice: ";
        
        int choice;
        std::cin >> choice;
        std::cout << "\n";

        switch (choice) {
            case 1:
                manager.AddFigure();
                break;
            case 2:
                std::cout << "Enter index to remove: ";
                size_t index;
                std::cin >> index;
                manager.RemoveFigure(index - 1);
                break;
            case 3:
                manager.PrintAllFigures();
                break;
            case 4:
                std::cout << "Total area: " << manager.CalculateTotalArea() << std::endl;
                break;
            case 5:
                return 0;
            default:
                std::cout << "Invalid choice!" << std::endl;
        }
    }
    return 0;
}