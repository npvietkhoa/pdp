#include "gtest/gtest.h"
#include "../threadsafe_queue.h"

TEST(ThreadsafeQueueTest, BasicPushPop) {
    threadsafe_queue<int> queue;
    int value = 42;

    // Push a value
    queue.push(value);

    // Wait and pop the value
    int popped_value;
    queue.wait_and_pop(popped_value);
    EXPECT_EQ(value, popped_value);  // Check if popped value matches pushed value
}



