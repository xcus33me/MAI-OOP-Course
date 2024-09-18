#include <iostream>

#include "solution.hpp"

int main() {
    int hours, minutes;
    std::string input;

    while (true) {
        std::cin >> hours >> minutes >> input;

        std::cout << "Answer: " << convertTo24HourFormat(hours, minutes, input) << std::endl;
    }

    return 0;
}