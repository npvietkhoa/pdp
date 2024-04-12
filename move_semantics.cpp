#include <thread>
#include <iostream>

/*
 * Demonstrate move operation and ownership within threads
 */
void foo() {
    std::cout << "foobar";
}

int main() {
    std::thread foo_thread(foo);
    std::thread another_foo_thread(foo);

    // Move resource to other
    std::thread foo_move = std::move(foo_thread);
    std::thread another_foo_move;
    another_foo_move = std::move(another_foo_thread);

    // This will cause program terminated as foo_move already owns a thread
    // foo_move = std::move(another_foo_move);


    // Wait for threads execution finished
    foo_move.join();
    another_foo_move.join();
}
