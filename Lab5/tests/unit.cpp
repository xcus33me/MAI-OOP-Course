#include <gtest/gtest.h>
#include "queue.hpp"
#include "dyn_mem_resource.hpp"

size_t allocation_count = 0;
size_t deallocation_count = 0;

void* operator new(size_t size) {
    ++allocation_count;
    return std::malloc(size);
}

void operator delete(void* ptr) noexcept {
    ++deallocation_count;
    std::free(ptr);
}

TEST(QueueTest, DefaultConstructor) {
    Queue<int> queue;
    EXPECT_TRUE(queue.Empty());
    EXPECT_EQ(queue.Size(), 0);
}

TEST(QueueTest, PushAndFrontBack) {
    Queue<int> queue;
    queue.Push(1);
    queue.Push(2);
    queue.Push(3);

    EXPECT_EQ(queue.Front(), 1);
    EXPECT_EQ(queue.Back(), 3);
    EXPECT_EQ(queue.Size(), 3);
}

TEST(QueueTest, Pop) {
    Queue<int> queue;
    queue.Push(1);
    queue.Push(2);
    queue.Push(3);

    queue.Pop();
    EXPECT_EQ(queue.Front(), 2);
    EXPECT_EQ(queue.Size(), 2);

    queue.Pop();
    EXPECT_EQ(queue.Front(), 3);
    EXPECT_EQ(queue.Size(), 1);

    queue.Pop();
    EXPECT_TRUE(queue.Empty());
}

TEST(QueueTest, Iterator) {
    Queue<int> queue;
    queue.Push(1);
    queue.Push(2);
    queue.Push(3);

    auto it = queue.Begin();
    EXPECT_EQ(*it, 1);
    ++it;
    EXPECT_EQ(*it, 2);
    ++it;
    EXPECT_EQ(*it, 3);
    ++it;
    EXPECT_EQ(it, queue.End());
}

TEST(QueueTest, CopyConstructor) {
    Queue<int> queue;
    queue.Push(1);
    queue.Push(2);
    queue.Push(3);

    Queue<int> copied_queue(queue);
    EXPECT_EQ(copied_queue.Size(), 3);
    EXPECT_EQ(copied_queue.Front(), 1);
    EXPECT_EQ(copied_queue.Back(), 3);
}

TEST(QueueTest, MoveConstructor) {
    Queue<int> queue;
    queue.Push(1);
    queue.Push(2);
    queue.Push(3);

    Queue<int> moved_queue(std::move(queue));
    EXPECT_EQ(moved_queue.Size(), 3);
    EXPECT_EQ(moved_queue.Front(), 1);
    EXPECT_EQ(moved_queue.Back(), 3);
    EXPECT_TRUE(queue.Empty());
}

TEST(QueueTest, Reserve) {
    Queue<int> queue;
    queue.Reserve(100);
    EXPECT_EQ(queue.Size(), 0);

    for (int i = 0; i < 100; ++i) {
        queue.Push(i);
    }

    EXPECT_EQ(queue.Size(), 100);
    EXPECT_EQ(queue.Front(), 0);
    EXPECT_EQ(queue.Back(), 99);
}

TEST(QueueTest, CustomAllocator) {
    DynamicMemoryResource pool;
    std::pmr::polymorphic_allocator<int> allocator(&pool);

    Queue<int, std::pmr::polymorphic_allocator<int>> queue(allocator);
    queue.Push(1);
    queue.Push(2);
    queue.Push(3);

    EXPECT_EQ(queue.Size(), 3);
    EXPECT_EQ(queue.Front(), 1);
    EXPECT_EQ(queue.Back(), 3);

    queue.Pop();
    EXPECT_EQ(queue.Front(), 2);
    EXPECT_EQ(queue.Size(), 2);
}

TEST(QueueTest, MemoryCleanupOnDestruction) {
    allocation_count = 0;
    deallocation_count = 0;

    {
        Queue<int> queue;
        queue.Push(1);
        queue.Push(2);
        queue.Push(3);
    }

    EXPECT_EQ(allocation_count, deallocation_count);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
