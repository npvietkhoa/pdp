#ifndef PDP_NAIVE_QUEUE_H
#define PDP_NAIVE_QUEUE_H

#include <stdexcept>  // For std::out_of_range
#include <iostream>   // For std::cerr

template<class T>
class NaiveQueue {
private:
    T* items;
    int head, tail, capacity, size;

public:
    NaiveQueue(int capacity)
            : items(new T[capacity]), head(0), tail(0), capacity(capacity), size(0) {}

    ~NaiveQueue() {
        delete[] items;
    }

    void enq(T element);
    T deq();
    bool isEmpty() const;
    bool isFull() const;
    int getSize() const;
};

template<class T>
void NaiveQueue<T>::enq(T element) {
    if (isFull()) {
        std::cerr << "Queue is full. Cannot enqueue element.\n";
        return;
    }
    items[tail] = element;
    tail = (tail + 1) % capacity;
    ++size;
}

template<class T>
T NaiveQueue<T>::deq() {
    if (isEmpty()) {
        throw std::out_of_range("Queue is empty");
    }
    T element = items[head];
    head = (head + 1) % capacity;
    --size;
    return element;
}

template<class T>
bool NaiveQueue<T>::isEmpty() const {
    return size == 0;
}

template<class T>
bool NaiveQueue<T>::isFull() const {
    return size == capacity;
}

template<class T>
int NaiveQueue<T>::getSize() const {
    return size;
}

#endif // PDP_NAIVE_QUEUE_H
