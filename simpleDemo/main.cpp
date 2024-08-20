#include "WashingMachine.h"
#include <iostream>

int main() {
    WashingMachine washingMachine;

    int input;
    while (true) {
        washingMachine.displayState();
        std::cout << "***********************************" << std::endl;
        std::cout << "0. Start" << std::endl;
        std::cout << "1. Pause" << std::endl;
        std::cout << "2. Resume" << std::endl;
        std::cout << "3. Stop" << std::endl;
        std::cout << "4. Cycle Complete" << std::endl;
        std::cout << "5. Error Detected" << std::endl;
        std::cout << "6. User Reset" << std::endl;
        std::cout << "7. Door Open" << std::endl;
        std::cout << "8. Door Close" << std::endl;
        std::cout << "***********************************" << std::endl;
        std::cin >> input;

        Event event;
        switch (input) {
            case 0:
                event = Event::Start;
                break;
            case 1:
                event = Event::Pause;
                break;
            case 2:
                event = Event::Resume;
                break;
            case 3:
                event = Event::Stop;
                break;
            case 4:
                event = Event::CycleComplete;
                break;
            case 5:
                event = Event::ErrorDetected;
                break;
            case 6:
                event = Event::UserReset;
                break;
            case 7:
                event = Event::DoorOpen;
                break;
            case 8:
                event = Event::DoorClose;
                break;
            default:
                std::cout << "Invalid input. Try again!" << std::endl;
                continue;
        }

        washingMachine.handleEvent(event);
    }

    return 0;
}