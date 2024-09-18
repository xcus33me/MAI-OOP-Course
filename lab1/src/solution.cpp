#include <iomanip>
#include <string>
#include <sstream>

#include "solution.hpp"

std::string convertTo24HourFormat(int hours, int minutes, std::string period) {
    if (period == "am" && hours == 12) {
        hours = 0;  
    } else if (period == "pm" && hours != 12) {
        hours += 12;  
    }

    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << hours 
        << std::setw(2) << std::setfill('0') << minutes;

    return oss.str();
}