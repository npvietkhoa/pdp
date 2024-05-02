#ifndef PDP_NAIVE_QUEUE_H
#define PDP_NAIVE_QUEUE_H

template<class T> class NaiveQueue {
private:
    T* items;
    int head, tail;
    
public:
    NaiveQueue(T *items, int head, int tail) : items(items), head(head), tail(tail) {}
    
    void enq(T element);
    
    T deq();
};

template<class T>
T NaiveQueue<T>::deq() {
    return NULL;
}

template<class T>
void NaiveQueue<T>::enq(T element) {

}

#endif //PDP_NAIVE_QUEUE_H
