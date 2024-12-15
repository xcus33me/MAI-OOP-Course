#pragma once

#include <initializer_list>
#include <string>
#include <vector>

class Thirteen {
public:
    Thirteen();
    Thirteen(const std::initializer_list<unsigned char> &t);
    Thirteen(const std::string &t);

    Thirteen(const Thirteen& other);
    Thirteen(Thirteen&& other) noexcept;
    virtual ~Thirteen() noexcept = default;
    
    Thirteen& operator=(const Thirteen& other);
    Thirteen operator+(const Thirteen& other);
    Thirteen operator-(const Thirteen& other);
    Thirteen operator+=(const Thirteen& other);
    Thirteen operator-=(const Thirteen& other);

    bool operator>(const Thirteen& other);
    bool operator<(const Thirteen& other);
    bool operator==(const Thirteen& other);

    std::string toString() const;

private:
    std::vector<unsigned char> digits;
};