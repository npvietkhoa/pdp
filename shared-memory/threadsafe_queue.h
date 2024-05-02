//
// Created by Khoa Nguyen on 12.04.24.
//

#ifndef PDP_THREADSAFE_QUEUE_H
#define PDP_THREADSAFE_QUEUE_H

#include "queue"
#include "mutex"

template<typename T> class threadsafe_queue {
private:
    std::queue<T> data;
    std::mutex mut;
    std::condition_variable cond;

public:
    threadsafe_queue() : data(), mut(), cond() {};
    threadsafe_queue(threadsafe_queue const& other_queue);

    void push(T new_value);
    void wait_and_pop(T& value);
};


/**
 * Block one (or multiple) thread(s) until another thread modified the condition
 * variable and performs the notification
 * - Acquire the mutex (must be std::unique_lock)
 * - Execute wait(), wait_for() or wait_until() (releases the mutex)
 * - Wakeup occurs on the condition or after timeout, mutex is re-acquired
 * @tparam T type of queue
 * @param value value will be popped from queue
 */
template<typename T>
void threadsafe_queue<T>::wait_and_pop(T &value) {
    std::unique_lock<std::mutex> lk(mut);
    cond.wait(lk, [this]() { return !this.data.empty(); } );
    value = this->data.front();
    data.pop();
}

/**
 * - Acquire the mutex () (usually via std::lock_guard)
 * - Perform the modification, release the mutex
 * - Execute notify_one() or notify_all()
 * @tparam T type of new_value
 * @param new_value value to push into queue
 */
template<typename T>
void threadsafe_queue<T>::push(T new_value) {
    std::lock_guard<std::mutex> lk(this->mut);
    data.push(new_value);
    cond.notify_one();
}



/**
 *
 * @tparam T
 * @param other_queue
 */
template<typename T>
threadsafe_queue<T>::threadsafe_queue(const threadsafe_queue &other_queue) {
    // lock the mutex
    std::lock_guard<std::mutex> lk(other_queue.mut);
    data = other_queue.data;
}



#endif //PDP_THREADSAFE_QUEUE_H
