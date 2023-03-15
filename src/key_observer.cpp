#include "key_observer.h"
#include <iostream>

void KeyObserver::add_listener(void *object, std::function<void(void*, char)> listener) {
    this->listeners.push_back({object, listener});
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
        
        for (auto entry: this->listeners) {
            auto object = entry.first;
            auto listener = entry.second;
            listener(object, key); 
        }
    }
}
