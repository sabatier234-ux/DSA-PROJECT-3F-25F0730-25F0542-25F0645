# MayDay-404

A console-based Air Traffic Control simulation in C++. The player is the
Chief Routing Officer (CRO) of BlackBox Airline and must survive 30 ticks
of hijacks, cyber attacks, missing flights and a war event.

Every game behaviour is driven by a data structure written from scratch.
No STL containers or algorithms are used. Only these headers are allowed:
iostream, string, cstring, fstream, ctime.

## Team
Course: CL2001 Data Structures, Section CS-3F, Fall 2026

| Name         | Roll No  | Modules                         |
|--------------|----------|---------------------------------|
| Zainab Aslam | 25F-0542 | 1 (registry, crew), 3, 4, 5, 11 |
| Saba         | 25F-0730 | 6, 7, 8, 9                      |
| Javeria Abid | 25F-0645 |Hash table, 2, 10, file loaders  |

## Data Structures and Where They Are Used
| Data Structure | Class / File | Purpose in the game |
| Singly linked list | Registration | Active flight and crew registry |
| Hash table, linear probing | HashTable | Fast flight lookup by callsign |
| Circular queue | EmergencyLanding | Normal landing order (FIFO) |
| Min-heap | EmergencyLanding | Emergency dispatch by priority, then arrival tick |
| Doubly linked list | CommandHistory | Log of all CRO commands |
| Stack (linked) | CommandHistory | Undo / redo of the last command |
| BST | BSTflight | Ordered flight manifest by callsign |
| AVL tree | AVLflight | Balanced flight index |
| Graph (list + matrix) | SpaceGraph | Airspace sectors and corridors |
| BFS / DFS | RadarSweep | Radar sweep, reachability, missing flight search |
| Dijkstra + min-heap | RouteFinder | Fastest route to a runway |
| Kruskal + union-find | RadarMST | Minimum radar coverage |

## Project Structure
- Flight.h : Flight and Crew record structures
- Registration, HashTable, EmergencyLanding, CommandHistory
- BSTflight, AVLflight
- SpaceGraph, RadarSweep, RouteFinder, RadarMST
- LeaderBoard, GameEngine, main.cpp
- Data files: flights.txt, crew.txt, airspace.txt, scenario.txt,
  rules.txt, about.txt, gamemenu.txt, mainmenu.txt, leaderboard.txt

## Build and Run
1. Clone the repository.
2. Open Microsoft Visual Studio and create a new C++ Console project.
3. Add all .h and .cpp files to the project.
4. Place all .txt files in the same folder the program runs from
   (the project working directory).
5. Build and run (Ctrl+F5).
6. Choose [1] New Game from the main menu and enter your CRO name
   (use _ or . instead of spaces).

## How to Play
- Each turn is one tick (30 simulated seconds), with up to 2 actions.
- Viewing radar, manifest, map and pending arrivals is free.
- Option [23] ends the turn early. Option [24] exits and counts as a loss.
- Win by surviving 30 ticks with no crash, hijack, cyber breach or war
  failure. Lose if credibility reaches 0 or any of those failures occurs.
- Results are appended to leaderboard.txt and ranked by result,
  credibility, ticks, then date.

## Fallback Behaviour
- If rules.txt is missing or corrupt, built-in defaults are used
  (30 ticks, 100 credibility, standard penalties and gains).

## Known Limitations
1. Fixed hash table size; no resizing when the table fills.
2. Flight spawns follow scenario.txt only; no fully random scenario generation.
3. Undo supports only the commands listed as undoable (options 07-11).
4. Console only; no graphical radar.
5. Input is read line by line; very long or malformed input is rejected, not corrected.

## Deviations from the Manual
1. airspace.txt weights used instead of Table 4 because the file is what
   the program loads and the manual's two sources conflict.
2. Runway 27 reference in Module 7 replaced with Runway 17 because
   Runway 27 does not exist in the game.
3. Cyber escalation uses ___ ticks for corridor and ___ for tower because
   the manual states two different sets of values.
4. Duplicate employee ID EBB91 in sample crew.txt changed to ___.

