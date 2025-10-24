// SML-based implementation (equivalent to table.cpp)
#include <iostream>
#include "sml.hpp"

namespace sml = boost::sml;

// events
struct swipe_card {};
struct open_door {};
struct close_door {};
struct reset {};

// transition table (as a functor)
struct Door {
  struct Locked;
  struct Unlocked;
  struct Alarm;

  auto operator()() const {
    using namespace sml;
    return make_transition_table(
      // initial state is Locked
      *state<Locked> + event<swipe_card>  / [] { std::cout << "####Door unlocked." << std::endl; } = state<Unlocked>,
       state<Locked> + event<open_door>  / [] { std::cout << "####Door opened while locked! Alarm triggered." << std::endl; } = state<Alarm>,

       state<Unlocked> + event<open_door>  / [] { std::cout << "####Door opened." << std::endl; } = state<Unlocked>,
       state<Unlocked> + event<close_door> / [] { std::cout << "####Door closed." << std::endl; } = state<Locked>,
       state<Unlocked> + event<reset>      / [] { std::cout << "####System reset." << std::endl; } = state<Locked>,

       state<Alarm> + event<reset>         / [] { std::cout << "####System reset from Alarm." << std::endl; } = state<Locked>
    );
  }
};

void printHelp() {
  std::cout << "Available commands:" << std::endl;
  std::cout << "1. swipe_card" << std::endl;
  std::cout << "2. open_door" << std::endl;
  std::cout << "3. close_door" << std::endl;
  std::cout << "4. reset" << std::endl;
  std::cout << "5. exit" << std::endl;
}

template <class Sm>
void printCurrentState(Sm &sm) {
  using namespace sml;
  if (sm.is(sml::state<Door::Locked>)) {
    std::cout << "------------>Current State: Locked" << std::endl;
  } else if (sm.is(sml::state<Door::Unlocked>)) {
    std::cout << "------------>Current State: Unlocked" << std::endl;
  } else if (sm.is(sml::state<Door::Alarm>)) {
    std::cout << "------------>Current State: Alarm" << std::endl;
  } else {
    std::cout << "------------>Current State: <unknown>" << std::endl;
  }
}

int main() {
  sml::sm<Door> sm{}; // instantiate state machine

  while (true) {
    printCurrentState(sm);
    printHelp();

    unsigned int command = 0;
    std::cout << "Enter command: ";
    if (!(std::cin >> command)) break;

    bool handled = false;
    if (command == 1) {
      handled = sm.process_event(swipe_card{});
    } else if (command == 2) {
      handled = sm.process_event(open_door{});
    } else if (command == 3) {
      handled = sm.process_event(close_door{});
    } else if (command == 4) {
      handled = sm.process_event(reset{});
    } else if (command == 5) {
      break;
    } else {
      std::cout << "Unknown command." << std::endl;
      continue;
    }

    if (!handled) {
      std::cout << "####No valid transition for this event in current state." << std::endl;
    }
  }

  return 0;
}
