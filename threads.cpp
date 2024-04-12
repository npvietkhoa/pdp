/*
 * Simple example for thread creating and execution.
 */
#include <iostream>
#include "thread"

void foo_func() {
    std::cout << "foo" << std::endl;
    std::cout << "func_foo_id: " << std::this_thread::get_id() << std::endl;
}

void bar_func() {
    std::cout << "bar" << std::endl;
    std::cout << "func_bar_id: " << std::this_thread::get_id() << std::endl;
}

int main() {
    std::thread::id main_thread;
    std::cout << "main_id: " << main_thread << std::endl;

    // create threads with functions
    std::thread foo_func_thread(foo_func);
    std::thread bar_func_thread(bar_func);

    // Create threads with lambda
    std::thread foo_lambda_thread([] {
        std::cout << "foo_id: " << std::this_thread::get_id() << std::endl;
    });
    std::thread bar_lambda_thread([] {
        std::cout << "bar_id: " << std::this_thread::get_id() << std::endl;
    });



    // Main threads will block and wait for other execution finish
    foo_func_thread.join();
    bar_func_thread.join();

    foo_func_thread.join();
    bar_func_thread.join();

//    execute independently of the thread handle
//    foo_thread.detach();
//    bar_thread.detach();
//    TODO: handling before std::thread is destroyed a.k.a std::terminated is called
}