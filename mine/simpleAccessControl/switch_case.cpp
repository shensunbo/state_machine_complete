#include <iostream>

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

class AccessControl {
public:
    AccessControl() : state_(State::Locked) {}
    void handleEvent(Event event) {
        switch (state_) {
            case State::Locked:
                handleLockedEvent(event);
                break;
            case State::Unlocked:
                handleUnlockedEvent(event);
                break;
            case State::Alarm:
                handleAlarmEvent(event);
                break;
        }
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
    void handleLockedEvent(Event event) {
        switch (event) {
            case Event::swipe_card:
                state_ = State::Unlocked;
                unlock_door();
                break;
            default:
                break;
        }
    }

    void handleUnlockedEvent(Event event) {
        switch (event) {
            case Event::open_door:
                open_door();
                break;
            case Event::close_door:
                state_ = State::Locked;
                close_door();
                break;
            case Event::reset:
                state_ = State::Locked;
                reset();
                break;
            default:
                break;
        }
    }

    void handleAlarmEvent(Event event) {
        switch (event) {
            case Event::reset:
                state_ = State::Locked;
                reset();
                break;
            default:
                break;
        }
    }

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