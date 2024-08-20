#pragma once

enum class State {
    Idle,
    Wash,
    Rinse,
    Spin,
    Pause,
    Error
};

enum class Event {
    Start,
    Pause,
    Resume,
    Stop,
    UserReset,
    ErrorDetected,
    CycleComplete,
    DoorOpen,
    DoorClose
};

class WashingMachine {
public:
    WashingMachine();
    ~WashingMachine() = default;

    void handleEvent(Event event);
    void displayState();


private:
    void handleIdleEvent(Event event);
    void handleWashEvent(Event event);
    void handleRinseEvent(Event event);
    void handleSpinEvent(Event event);
    void handlePauseEvent(Event event);
    void handleErrorEvent(Event event);

private:
    State state_;
};