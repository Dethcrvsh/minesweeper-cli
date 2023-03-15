#include "key_observer.h"
#include <iostream>

void KeyObserver::add_listener(std::function<void(char)> listener) {
    this->listeners.push_back(listener);
}

void KeyObserver::start_listening() {
    this->is_listening = true;
    this->listen();
}

void KeyObserver::end_listening() {
    this->is_listening = false;
}

void KeyObserver::listen() const {
    system("stty raw");

    while(this->is_listening) {
        char key = getchar();
        
        for (auto listener : this->listeners) {
            listener(key);
        }
    }
}
