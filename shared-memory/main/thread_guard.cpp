/**
 * Implementation of RAII - Resource Acquisition Is Initialization
 * 1. encapsulate each resource into a class
 * - constructor acquires the resource and establishes all class invariants or throws an exception if that cannot be done,
 * - destructor releases the resource and never throws exceptions
 * 2. always use the resource via an instance of a RAII-class
 * - with automatic storage duration or temporary lifetime
 */
#include "thread"

class thread_guard {
private:
    std::thread &thread;

public:
    explicit thread_guard(std::thread &thread_);

    virtual ~thread_guard();

    // In order to maintain one guard at a time
    // Disable constructor copy
    thread_guard(thread_guard const &) = delete;
    // Disabling the Copy Assignment Operation =
    thread_guard &operator=(thread_guard const &) = delete;
};

thread_guard::thread_guard(std::thread &thread_) : thread(thread_) {}

thread_guard::~thread_guard() {
    // When guard is going to be destroyed,
    // join the thread to process
    if (this->thread.joinable()) {
        this->thread.join();
    }
}



