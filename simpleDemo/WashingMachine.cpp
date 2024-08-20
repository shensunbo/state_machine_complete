#include  "WashingMachine.h"

#include <iostream>
#include <string>

WashingMachine::WashingMachine() : state_(State::Idle) {

}

void WashingMachine::handleEvent(Event event) {
    switch (state_) {
        case State::Idle:
            handleIdleEvent(event);
            break;
        case State::Wash:
            handleWashEvent(event);
            break;
        case State::Rinse:
            handleRinseEvent(event);
            break;
        case State::Spin:
            handleSpinEvent(event);
            break;
        case State::Pause:
            handlePauseEvent(event);
            break;
        case State::Error:
            handleErrorEvent(event);
            break;
    }
}

void WashingMachine::displayState() {
    switch (state_) {
        case State::Idle:
            std::cout << "--------------------> Ready" << std::endl;
            break;
        case State::Wash:
            std::cout << "--------------------> Washing" << std::endl;
            break;
        case State::Rinse:
            std::cout << "--------------------> Rinsing" << std::endl;
            break;
        case State::Spin:
            std::cout << "--------------------> Spinning" << std::endl;
            break;
        case State::Pause:
            std::cout << "--------------------> Paused" << std::endl;
            break;
        case State::Error:
            std::cout << "--------------------> Error" << std::endl;
            break;
    }
}

void WashingMachine::handleIdleEvent(Event event) {
    switch (event) {
        case Event::Start:
            state_ = State::Wash;
            break;
        case Event::DoorOpen:
            // do nothing
            break;
        default:
            // unexpected event, do nothing
            break;
    }
}

void WashingMachine::handleWashEvent(Event event) {
    switch (event) {
        case Event::CycleComplete:
            state_ = State::Rinse;
            break;
        case Event::ErrorDetected:
            state_ = State::Error;
            break;
        case Event::Pause:
            state_ = State::Pause;
            break;
        default:
            // unexpected event, do nothing
            break;
    }
}

void WashingMachine::handleRinseEvent(Event event) {
    switch (event) {
        case Event::CycleComplete:
            state_ = State::Spin;
            break;
        case Event::ErrorDetected:
            state_ = State::Error;
            break;
        case Event::Pause:
            state_ = State::Pause;
            break;
        default:
            // unexpected event, do nothing
            break;
    }
}

void WashingMachine::handleSpinEvent(Event event) {
    switch (event) {
        case Event::CycleComplete:
            state_ = State::Idle;
            break;
        case Event::ErrorDetected:
            state_ = State::Error;
            break;
        case Event::Pause:
            state_ = State::Pause;
            break;
        default:
            // unexpected event, do nothing
            break;
    }
}

void WashingMachine::handlePauseEvent(Event event) {
    switch (event) {
        case Event::Resume:
            state_ = State::Wash;
            break;
        case Event::Stop:
            state_ = State::Idle;
            break;
        default:
            // unexpected event, do nothing
            break;
    }
}

void WashingMachine::handleErrorEvent(Event event) {
    switch (event) {
        case Event::UserReset:
            state_ = State::Idle;
            break;
        default:
            // unexpected event, do nothing
            break;
    }
}

