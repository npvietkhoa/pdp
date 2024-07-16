//
// Created by Khoa Nguyen on 22.05.24.
//
#include "thread"
#include "cassert"
#include "atomic"


std::atomic<bool> nf_flag(false);
int               nf_data;

int mem_fence();

void foo_nf_func() {
    nf_data = 22;
    nf_flag.store(true, std::memory_order_relaxed);
}

void bar_nf_func() {
    while(!nf_flag.load(std::memory_order_relaxed)) {};

    // could be failed here
    assert(nf_data == 22);
}


int main() {
    std::thread foo_thrd(foo_nf_func), bar_thrd(bar_nf_func);
    foo_thrd.join();
    bar_thrd.join();
    mem_fence();
}

