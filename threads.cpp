/*
 * Simple example for thread creating and execution.
 */
#include <iostream>
#include "thread"

int main() {
    std::thread::id main_thread;
    std::cout << "main_id: " << main_thread << std::endl;

    std::thread foo_thread([] {
        std::cout << "foo_id: " << std::this_thread::get_id() << std::endl;
    });

    std::thread bar_thread([] {
        std::cout << "bar_id: " << std::this_thread::get_id() << std::endl;
    });

//    Main threads will block and wait for other execution finish
    foo_thread.join();
    bar_thread.join();

//    execute independently of the thread handle
//    foo_thread.detach();
//    bar_thread.detach();
//    TODO: handling before std::thread is destroyed a.k.a std::terminated is called
}