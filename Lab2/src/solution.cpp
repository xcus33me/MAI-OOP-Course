#include "solution.hpp"

#include <algorithm>
#include <stdexcept>
#include <sstream>

Thirteen::Thirteen() : digits{} {}

Thirteen::Thirteen(const std::initializer_list<unsigned char> &t) {
    for (unsigned char digit : t) {
        if (digit >= '0' && digit <= '9') {
            digits.push_back(digit - '0');
        } else if (digit >= 'A' && digit <= 'C') {
            digits.push_back(10 + (digit - 'A'));
        } else if (digit <= 12) {
            digits.push_back(digit);
        } else {
            throw std::runtime_error("Каждая цифра должна быть в диапазоне от 0 до 12!");
        }
    }
}

Thirteen::Thirteen(const std::string &t) {
    for (auto it = t.rbegin(); it != t.rend(); ++it) {
        char ch = *it;
        unsigned char digit;

        if (ch >= '0' && ch <= '9') {
            digit = ch - '0';
        } else if (ch >= 'A' && ch <= 'C') {
            digit = 10 + (ch - 'A');
        } else {
            throw std::runtime_error("Некорректный символ в тринадцатиричном числе!");
        }

        digits.push_back(digit);
    }
}

Thirteen::Thirteen(const Thirteen& other) : digits(other.digits) {

}

Thirteen::Thirteen(Thirteen&& other) noexcept 
    : digits(other.digits) {
    other.digits.clear();
}

Thirteen& Thirteen::operator=(const Thirteen& other) {
    if (this != &other) {
        digits = other.digits;
    }
    return *this;
}

Thirteen Thirteen::operator+(const Thirteen& other) {
    Thirteen result;
    size_t max_length = std::max(digits.size(), other.digits.size());
    int carry = 0;

    for (size_t i = 0; i < max_length; ++i) {
        unsigned char digit1 = i < digits.size() ? digits[digits.size() - 1 - i] : 0;
        unsigned char digit2 = (i < other.digits.size()) ? other.digits[other.digits.size() - 1 - i] : 0;
    
        int sum = digit1 + digit2 + carry;
        carry = sum / 13;
        result.digits.insert(result.digits.begin(), sum % 13);
    }

    if (carry > 0) {
        result.digits.insert(result.digits.begin(), carry);
    }

    return result;
}

Thirteen Thirteen::operator-(const Thirteen& other) {
    Thirteen result;
    size_t max_length = std::max(digits.size(), other.digits.size());
    int borrow = 0;

    for (size_t i = 0; i < max_length; ++i) {
        unsigned char digit1 = i < digits.size() ? digits[digits.size() - 1 - i] : 0;
        unsigned char digit2 = i < other.digits.size() ? other.digits[other.digits.size() - 1 - i] : 0;

        int diff = digit1 - digit2 - borrow;
        if (diff < 0) {
            diff += 13;
            borrow = 1;
        } else {
            borrow = 0;
        }

        result.digits.insert(result.digits.begin(), diff);
    }

    while (!result.digits.empty() && result.digits.front() == 0) {
        result.digits.erase(result.digits.begin());
    }

    return result;
}

Thirteen Thirteen::operator+=(const Thirteen& other) {
    *this = *this + other;
    return *this;
}
 
Thirteen Thirteen::operator-=(const Thirteen& other) {
    *this = *this - other;
    return *this;
}

bool Thirteen::operator>(const Thirteen& other) {
    if (digits.size() != other.digits.size()) {
        return digits.size() > other.digits.size();
    }

    for (size_t i = 0; i < digits.size(); ++i) {
        if (digits[i] != other.digits[i]) {
            return digits[i] > other.digits[i];
        }
    }

    return false;
}

bool Thirteen::operator<(const Thirteen& other) {
    if (digits.size() != other.digits.size()) {
        return digits.size() < other.digits.size();
    }

    for (size_t i = 0; i < digits.size(); ++i) {
        if (digits[i] != other.digits[i]) {
            return digits[i] < other.digits[i];
        }
    }

    return false;
}

bool Thirteen::operator==(const Thirteen& other) {
    if (digits.size() != other.digits.size()) {
        return false;
    }

    for (size_t i = 0; i < digits.size(); ++i) {
        if (digits[i] != other.digits[i]) {
            return false;
        }
    }

    return true;
}

std::string Thirteen::toString() const {
    if (digits.empty()) return "0";

    std::ostringstream result;
    for (auto it = digits.begin(); it != digits.end(); ++it) {
        unsigned char digit = *it;

        if (digit >= 0 && digit <= 9) {
            result << static_cast<char>('0' + digit);
        } else if (digit >= 10 && digit <= 12) {
            result << static_cast<char>('A' + (digit - 10));
        } else {
            throw std::runtime_error("Некорректное значение в массиве digits!");
        }
    }

    return result.str();
}