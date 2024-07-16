#include <gtest/gtest.h>
#include "../lib/naive_queue.h"

class NaiveQueueTest : public ::testing::Test {
protected:
    NaiveQueue<int> *queue;

    void SetUp() override {
        queue = new NaiveQueue<int>(5);
    }

    void TearDown() override {
        delete queue;
    }
};

TEST_F(NaiveQueueTest, ConstructorTest) {
    EXPECT_EQ(queue->getSize(), 0);
    EXPECT_TRUE(queue->isEmpty());
    EXPECT_FALSE(queue->isFull());
}

TEST_F(NaiveQueueTest, EnqueueTest) {
    queue->enq(1);
    EXPECT_EQ(queue->getSize(), 1);
    EXPECT_FALSE(queue->isEmpty());
    EXPECT_FALSE(queue->isFull());
}

TEST_F(NaiveQueueTest, DequeueTest) {
    queue->enq(1);
    int element = queue->deq();
    EXPECT_EQ(element, 1);
    EXPECT_EQ(queue->getSize(), 0);
    EXPECT_TRUE(queue->isEmpty());
    EXPECT_FALSE(queue->isFull());
}

TEST_F(NaiveQueueTest, EnqueueAndDequeueTest) {
    queue->enq(1);
    queue->enq(2);
    EXPECT_EQ(queue->deq(), 1);
    EXPECT_EQ(queue->deq(), 2);
    EXPECT_TRUE(queue->isEmpty());
}

TEST_F(NaiveQueueTest, OverflowTest) {
    queue->enq(1);
    queue->enq(2);
    queue->enq(3);
    queue->enq(4);
    queue->enq(5);
    EXPECT_TRUE(queue->isFull());
    // Try enqueuing another element
    queue->enq(6);
    EXPECT_EQ(queue->getSize(), 5);
}

TEST_F(NaiveQueueTest, UnderflowTest) {
    EXPECT_THROW(queue->deq(), std::out_of_range);
}


