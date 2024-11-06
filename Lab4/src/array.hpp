// array.hpp

#pragma once 

#include <memory>
#include <iostream>
#include <stdexcept>

template <typename T>
class Array {
public:
    Array(size_t capacity = 10)
        : size_(0), capacity_(capacity), data_(std::make_shared<T[]>(capacity)) {}

    void Add(const T& element) {
        if (size_ >= capacity_) {
            Resize(capacity_ * 2);
        }
        data_[size_++] = element;
    }

    bool Remove(size_t index) {
        if (index < size_) {
            for (size_t i = index; i < size_ - 1; ++i) {
                data_[i] = data_[i + 1];
            }
            --size_;
            return true;
        }
        return false;
    }

    size_t Size() const { return size_; }

    T& operator[](size_t index) {
        if (index >= size_) throw std::out_of_range("Invalid index");
        return data_[index];
    }

    const T& operator[](size_t index) const {
        if (index >= size_) throw std::out_of_range("Invalid index");
        return data_[index];
    }

private:
    void Resize(size_t new_capacity) {
        auto new_data = std::make_shared<T[]>(new_capacity);
        for (size_t i = 0; i < size_; ++i) {
            new_data[i] = std::move(data_[i]);
        }
        capacity_ = new_capacity;
        data_ = std::move(new_data);
    }

    size_t size_;
    size_t capacity_;
    std::shared_ptr<T[]> data_;
};
