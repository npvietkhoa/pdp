#include <gtest/gtest.h>
#include <thread>
#include <algorithm>
#include "../lib/threadsafe_queue.h"

class ThreadSafeQueueTest : public ::testing::Test {
protected:
    threadsafe_queue<int> queue;
};

// Test for pushing and popping elements in single-threaded context
TEST_F(ThreadSafeQueueTest, PushAndPop) {
    queue.push(1);
    queue.push(2);

    int value;
    queue.wait_and_pop(value);
    EXPECT_EQ(value, 1);

    queue.wait_and_pop(value);
    EXPECT_EQ(value, 2);
}

// Test for thread safety using multiple threads
TEST_F(ThreadSafeQueueTest, MultiThreadedPushAndPop) {
    std::thread t1([&] {
        for (int i = 0; i < 10; ++i) {
            queue.push(i);
        }
    });

    std::thread t2([&] {
        for (int i = 10; i < 20; ++i) {
            queue.push(i);
        }
    });

    t1.join();
    t2.join();

    std::vector<int> popped_values;
    for (int i = 0; i < 20; ++i) {
        int value;
        queue.wait_and_pop(value);
        popped_values.push_back(value);
    }

    std::sort(popped_values.begin(), popped_values.end());
    for (int i = 0; i < 20; ++i) {
        EXPECT_EQ(popped_values[i], i);
    }
}

// Test for copy constructor
TEST_F(ThreadSafeQueueTest, CopyConstructor) {
    queue.push(1);
    queue.push(2);

    threadsafe_queue<int> copied_queue(queue);

    int value;
    copied_queue.wait_and_pop(value);
    EXPECT_EQ(value, 1);

    copied_queue.wait_and_pop(value);
    EXPECT_EQ(value, 2);
}

// Test for popping from an empty queue (waits for push)
TEST_F(ThreadSafeQueueTest, WaitAndPopOnEmptyQueue) {
    std::thread t([&] {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        queue.push(42);
    });

    int value;
    queue.wait_and_pop(value);
    EXPECT_EQ(value, 42);

    t.join();
}

