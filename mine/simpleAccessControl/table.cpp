// State Transition table
#include <iostream>
#include <string>
#include <functional>

enum class State {
    Locked,
    Unlocked,
    Alarm
};

enum class Event {
    swipe_card,
    open_door,
    close_door,
    reset
};

typedef struct {
    State current_state;
    Event event;
    State next_state;
    std::function<void(void)> action;
} StateTransition;

class AccessControl {
public:
    AccessControl() : state_(State::Locked) {}
    void handleEvent(Event event) {
        for (size_t i = 0; i < TABLE_SIZE; i++) {
            if (transition_table[i].current_state == state_ &&
                transition_table[i].event == event) {
                
                if (transition_table[i].action) {
                    transition_table[i].action();
                }
                
                state_ = transition_table[i].next_state;
                return;
            }
        }
        std::cout << "####No valid transition for this event in current state." << std::endl;
    }

    void printCurrentState() const {
        switch (state_) {
            case State::Locked:
                std::cout << "------------>Current State: Locked" << std::endl;
                break;
            case State::Unlocked:
                std::cout << "------------>Current State: Unlocked" << std::endl;
                break;
            case State::Alarm:
                std::cout << "------------>Current State: Alarm" << std::endl;
                break;
        }
    }

private:
    State state_;
    const static size_t TABLE_SIZE = 5;
    StateTransition transition_table[TABLE_SIZE] = {
        {State::Locked, Event::swipe_card, State::Unlocked, std::bind(&AccessControl::unlock_door, this)},
        {State::Unlocked, Event::open_door, State::Unlocked, std::bind(&AccessControl::open_door, this)},
        {State::Unlocked, Event::close_door, State::Locked, std::bind(&AccessControl::close_door, this)},
        {State::Unlocked, Event::reset, State::Locked, std::bind(&AccessControl::reset, this)},
        {State::Alarm, Event::reset, State::Locked, std::bind(&AccessControl::reset, this)}
    };

    void unlock_door() {
        std::cout << "####Door unlocked." << std::endl;
    }

    void open_door() {
        std::cout << "####Door opened." << std::endl;
    }

    void close_door() {
        std::cout << "####Door closed." << std::endl;
    }

    void reset() {
        std::cout << "####System reset." << std::endl;
    }
};

void printHelp(){
    std::cout << "Available commands:" << std::endl;
    std::cout << "1. swipe_card" << std::endl;
    std::cout << "2. open_door" << std::endl;
    std::cout << "3. close_door" << std::endl;
    std::cout << "4. reset" << std::endl;
    std::cout << "5. exit" << std::endl;
}

int main() {
    AccessControl ac;
    
    while(1){
        ac.printCurrentState();
        printHelp();
        unsigned int command;
        std::cout << "Enter command: ";
        std::cin >> command;

        if (command == 1) {
            ac.handleEvent(Event::swipe_card);
        } else if (command == 2) {
            ac.handleEvent(Event::open_door);
        } else if (command == 3) {
            ac.handleEvent(Event::close_door);
        } else if (command == 4) {
            ac.handleEvent(Event::reset);
        } else if (command == 5) {
            break;
        } else {
            std::cout << "Unknown command." << std::endl;
        }
    }
    return 0;
}