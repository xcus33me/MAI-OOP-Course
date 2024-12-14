#pragma once

#include <iostream>
#include <vector>
#include <memory_resource>

class DynamicMemoryResource : public std::pmr::memory_resource {
public:
    DynamicMemoryResource() = default;
    ~DynamicMemoryResource() {
        for (const auto& block : allocated_blocks) {
            ::operator delete(block.ptr, std::align_val_t(block.size));
        }
        allocated_blocks.clear();
        free_blocks.clear();
    }

protected:
    void* do_allocate(size_t bytes, size_t alignment) override {
        for (auto it = free_blocks.begin(); it != free_blocks.end(); ++it) {
            if (std::align(alignment, bytes, *it, bytes)) {
                void* ptr = *it;
                free_blocks.erase(it);
                return ptr;
            }
        }

        void* ptr = ::operator new(bytes, std::align_val_t(alignment));
        allocated_blocks.push_back({ptr, bytes});
        return ptr;
    }

    void do_deallocate(void* ptr, size_t bytes, size_t alignment) override {
        (void)bytes; // Unused
        (void)alignment; // Unused
        free_blocks.push_back(ptr);
    }

    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override {
        return this == &other;
    }

private:
    struct Block {
        void* ptr;
        size_t size;
    };

    std::vector< Block > allocated_blocks;
    std::vector< void* > free_blocks;
};