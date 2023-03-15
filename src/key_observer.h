#ifndef _KEY_OBSERVER
#define _KEY_OBSERVER

#include <vector>
#include <functional>

class KeyObserver {
public:
    void add_listener(void* object, std::function<void(void*, char)> listener);

    // Start listening for key presses.
    // This will lock up the current thread.
    void start_listening();
    void end_listening();

private:
    bool is_listening = false;

    // A vector with an object and its method
    std::vector<std::pair<void*, std::function<void(void*, char)>>> listeners;
    void listen() const;
};

#endif
