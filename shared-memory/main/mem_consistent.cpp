//
// Created by Khoa Nguyen on 22.05.24.
//
#include "cassert"
#include "thread"
#include "atomic"

std::atomic<bool> flag(false);
int               data;

void foo_func() {
    data = 22; // full fence - nf_data = 22 is visible to all threads
    flag.store(true, std::memory_order_seq_cst);
}

void bar_func() {
    // wait for nf_flag
    while(!flag.load(std::memory_order_seq_cst)) {};

    // full fence - load to assert can not be reordered.
    assert(data == 22);
}

void mem_fence() {
    std::thread foo_thrd(foo_func), bar_thread(bar_func);
    foo_thrd.join();
    bar_thread.join();
}


