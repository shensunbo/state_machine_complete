// State Pattern implementation
#include <iostream>
#include <memory>
#include <string>

// forward declarations
class AccessControl;
class LockedState;
class UnlockedState;
class AlarmState;

// State interface
class AccessState {
public:
    explicit AccessState(AccessControl* ctx) : ctx_(ctx) {}
    virtual ~AccessState() = default;

    virtual void swipe() = 0;
    virtual void open() = 0;
    virtual void close() = 0;
    virtual void reset() = 0;
    virtual const char* name() const = 0;

protected:
    AccessControl* ctx_;
};

// Concrete states - method bodies implemented after AccessControl
class LockedState : public AccessState {
public:
    using AccessState::AccessState;
    void swipe() override;
    void open() override;
    void close() override;
    void reset() override;
    const char* name() const override { return "Locked"; }
};

class UnlockedState : public AccessState {
public:
    using AccessState::AccessState;
    void swipe() override;
    void open() override;
    void close() override;
    void reset() override;
    const char* name() const override { return "Unlocked"; }
};

class AlarmState : public AccessState {
public:
    using AccessState::AccessState;
    void swipe() override;
    void open() override;
    void close() override;
    void reset() override;
    const char* name() const override { return "Alarm"; }
};

// Context
class AccessControl {
public:
    AccessControl() {
        state_ = std::make_shared<LockedState>(this);
    }

    void setState(std::shared_ptr<AccessState> s) {
        state_ = std::move(s);
    }

    void swipe_card()  { state_->swipe(); }
    void open_door()   { state_->open(); }
    void close_door()  { state_->close(); }
    void reset()       { state_->reset(); }

    void printCurrentState() const {
        std::cout << "------------>Current State: " << state_->name() << std::endl;
    }

private:
    std::shared_ptr<AccessState> state_;
};

// Implementations of state behaviors (now that AccessControl is defined)

void LockedState::swipe() {
    std::cout << "####Door unlocked." << std::endl;
    ctx_->setState(std::make_shared<UnlockedState>(ctx_));
}

void LockedState::open() {
    std::cout << "####Door opened while locked! Alarm triggered." << std::endl;
    ctx_->setState(std::make_shared<AlarmState>(ctx_));
}

void LockedState::close() {
    std::cout << "####Nothing to close. Door is locked." << std::endl;
}

void LockedState::reset() {
    std::cout << "####Nothing to reset in Locked state." << std::endl;
}

void UnlockedState::swipe() {
    std::cout << "####Card swiped but already unlocked." << std::endl;
}

void UnlockedState::open() {
    std::cout << "####Door opened." << std::endl;
    // stay Unlocked
}

void UnlockedState::close() {
    std::cout << "####Door closed." << std::endl;
    ctx_->setState(std::make_shared<LockedState>(ctx_));
}

void UnlockedState::reset() {
    std::cout << "####System reset." << std::endl;
    ctx_->setState(std::make_shared<LockedState>(ctx_));
}

void AlarmState::swipe() {
    std::cout << "####Alarm active. Swipe ignored." << std::endl;
}

void AlarmState::open() {
    std::cout << "####Alarm active. Open ignored." << std::endl;
}

void AlarmState::close() {
    std::cout << "####Alarm active. Close ignored." << std::endl;
}

void AlarmState::reset() {
    std::cout << "####System reset from Alarm." << std::endl;
    ctx_->setState(std::make_shared<LockedState>(ctx_));
}

// simple CLI
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

    while (true) {
        ac.printCurrentState();
        printHelp();
        unsigned int command;
        std::cout << "Enter command: ";
        if (!(std::cin >> command)) break;

        if (command == 1) {
            ac.swipe_card();
        } else if (command == 2) {
            ac.open_door();
        } else if (command == 3) {
            ac.close_door();
        } else if (command == 4) {
            ac.reset();
        } else if (command == 5) {
            break;
        } else {
            std::cout << "Unknown command." << std::endl;
        }
    }
    return 0;
}
