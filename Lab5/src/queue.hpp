#pragma once

#include <cstddef>
#include <iterator>
#include <memory_resource>
#include <type_traits>

#define MIN_CAP static_cast<size_t>(10)

template<typename T, typename allocator_type = std::pmr::polymorphic_allocator<T>>
class Queue {
private:
    template<bool IsConst>
    class BaseIterator {
        friend Queue;
    public:
        using value_type = T;
        using reference_type = std::conditional_t<IsConst, const T&, T&>;
        using pointer_type = std::conditional_t<IsConst, const T*, T*>;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::forward_iterator_tag;
    private:
        pointer_type cur_;
    private:
        BaseIterator() noexcept
         : cur_(nullptr)
        {}

        explicit BaseIterator(pointer_type ptr) noexcept
         : cur_(ptr)
        {}
    public:
        template<bool B = IsConst, typename = std::enable_if_t<B>>
        BaseIterator(const BaseIterator<false>& other) noexcept
         : cur_(other.cur_)
        {}

        inline bool operator==(const BaseIterator& other) const noexcept {
            return this->cur_ == other.cur_;
        }

        inline bool operator!=(const BaseIterator& other) const noexcept {
            return this->cur_ != other.cur_;
        }

        reference_type operator*() const noexcept {
            return *this->cur_;
        }

        pointer_type operator->() const noexcept {
            return &(*this->cur_);
        }

        BaseIterator& operator++() noexcept {
            ++this->cur_;
            return *this;
        }

        BaseIterator operator++(int) noexcept {
            BaseIterator copy = *this;
            ++this->cur_;
            return copy;
        }
    };
public:
    using Iterator = BaseIterator<false>;
    using ConstIterator = BaseIterator<true>;

private:
    allocator_type allocator_;
    size_t sz_;
    size_t cap_;
    T* data_;
    size_t head_;
    size_t tail_;

    using allocator_traits = std::allocator_traits<allocator_type>;

public:
    explicit Queue(const allocator_type& alloc = {}) noexcept
     : allocator_(alloc)
     , sz_(0)
     , cap_(0)
     , data_(nullptr)
     , head_(0)
     , tail_(0)
    {}

    Queue(const Queue& other, const allocator_type& alloc = {})
     : allocator_(alloc)
     , sz_(other.sz_)
     , cap_(other.cap_)
     , data_(allocator_.allocate(other.cap_))
     , head_(0)
     , tail_(other.sz_)
    {
        for (size_t i = 0; i < this->sz_; ++i) {
            try {
                this->allocator_.construct(this->data_ + i, other.data_[(other.head_ + i) % other.cap_]);
            } catch (...) {
                for (size_t j = 0; j < i; ++j) {
                    allocator_traits::destroy(this->allocator_, this->data_ + j);
                }
                this->allocator_.deallocate(this->data_, this->cap_);
                throw;
            }
        }
    }

    Queue(Queue&& other, const allocator_type& alloc = {}) noexcept
     : allocator_(std::move(alloc))
     , sz_(other.sz_)
     , cap_(other.cap_)
     , data_(other.data_)
     , head_(other.head_)
     , tail_(other.tail_)
    {
        other.sz_ = 0;
        other.cap_ = 0;
        other.data_ = nullptr;
        other.head_ = 0;
        other.tail_ = 0;
    }

    ~Queue() noexcept {
        while (!this->Empty()) {
            this->Pop();
        }
        this->allocator_.deallocate(this->data_, this->cap_);
    }

    T& Front() const noexcept {
        return this->data_[this->head_];
    }

    T& Back() const noexcept {
        return this->data_[(this->tail_ - 1 + this->cap_) % this->cap_];
    }

    inline Iterator Begin() const noexcept {
        return Iterator(this->data_ + this->head_);
    }

    inline Iterator End() const noexcept {
        return Iterator(this->data_ + this->tail_);
    }

    inline ConstIterator CBegin() const noexcept {
        return ConstIterator(this->data_ + this->head_);
    }

    inline ConstIterator CEnd() const noexcept {
        return ConstIterator(this->data_ + this->tail_);
    }

    bool Empty() const noexcept {
        return this->sz_ == 0;
    }

    size_t Size() const noexcept {
        return this->sz_;
    }

private:
    void CheckCapacity() {
        if (this->sz_ >= this->cap_) {
            this->Reserve(std::max(MIN_CAP, 2 * this->cap_));
        }
    }

public:
    void Reserve(size_t new_cap) {
        if (new_cap <= this->cap_) {
            return;
        }

        T* new_data = this->allocator_.allocate(new_cap);

        for (size_t i = 0; i < this->sz_; ++i) {
            try {
                this->allocator_.construct(new_data + i, std::move_if_noexcept(this->data_[(this->head_ + i) % this->cap_]));
            } catch (...) {
                for (size_t j = 0; j < i; ++j) {
                    allocator_traits::destroy(this->allocator_, new_data + j);
                }
                this->allocator_.deallocate(new_data, new_cap);
                throw;
            }
        }

        for (size_t i = 0; i < this->sz_; ++i) {
            allocator_traits::destroy(this->allocator_, this->data_ + ((this->head_ + i) % this->cap_));
        }
        this->allocator_.deallocate(this->data_, this->cap_);

        this->cap_ = new_cap;
        this->data_ = new_data;
        this->head_ = 0;
        this->tail_ = this->sz_;
    }

    /* Изменение очереди */

    void Push(const T& value) {
        this->CheckCapacity();
        this->allocator_.construct(this->data_ + this->tail_, value);
        this->tail_ = (this->tail_ + 1) % this->cap_;
        ++this->sz_;
    }

    void Push(T&& value) noexcept {
        this->CheckCapacity();
        this->allocator_.construct(this->data_ + this->tail_, std::move(value));
        this->tail_ = (this->tail_ + 1) % this->cap_;
        ++this->sz_;
    }

    void Pop() noexcept {
        allocator_traits::destroy(this->allocator_, this->data_ + this->head_);
        this->head_ = (this->head_ + 1) % this->cap_;
        --this->sz_;
    }
};