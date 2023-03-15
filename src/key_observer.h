#ifndef _KEY_OBSERVER
#define _KEY_OBSERVER

#include <vector>
#include <functional>

class KeyObserver {
public:
    void add_listener(std::function<void(char)> listener);

    // Start listening for key presses.
    // This will lock up the current thread.
    void start_listening();
    void end_listening();

private:
    bool is_listening = false;

    std::vector<std::function<void(char)>> listeners;
    void listen() const;
};

#endif
