# state
* Locked
* Unlocked
* Alarm

# event
* swipe_card
* open_door
* close_door
* reset

# transition table
| Current State | Event          | Next State    | Action               |
|---------------|----------------|---------------|----------------------|
| Locked        | swipe_card     | Unlocked      |  unlock_door()       |
| Unlocked      | open_door      | Unlocked      |  open_door()         |
| Unlocked      | close_door     | Locked        |  close_door()       |
| Unlocked      | reset          | Locked        |  reset()            |
| Alarm         | reset          | Locked        |  reset()            |