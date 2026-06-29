# Praktikum Informatik 2 – C++ Traffic Simulation

**Course:** Praktikum Informatik 2 (PI2) 
**Institution:** RWTH Aachen University, Institute for Human-Machine Interaction  
**Language:** C++ (C++17 Standard)  
**IDE:** Eclipse CDT  


**Overview**

This repository contains my full implementation for the *Praktikum Informatik 2* course at RWTH Aachen University. The project consists of three progressively expanding lab blocks that together produce a fully functional, object-oriented **road traffic simulation** in C++. Vehicles (cars and bicycles) navigate a network of roads and intersections, governed by a global time-step simulation engine, speed limits, no-overtaking rules, and fuel mechanics — all rendered graphically via a TCP/IP-based visualization server.


### Project Part 1 – Fundamentals of the Traffic System

- Designed and implemented a `Fahrzeug` (Vehicle) base class with private member variables for name, unique ID (auto-incremented via a static class variable), maximum speed, total distance traveled, and simulation time.
- Implemented derived classes `PKW` (car) and `Fahrrad` (bicycle) using an inheritance hierarchy, applying `virtual`, `override`, `protected`, and `const` correctly throughout.
- Added car-specific fuel mechanics to `PKW`: tank volume, fuel consumption per 100 km, a `dTanken()` refueling function with optional fill amount, and stalling behavior when the tank runs empty.
- Implemented a fatigue model for `Fahrrad`: speed decreases by 10% per 20 km traveled, with a minimum speed of 12 km/h, using a virtual `dGeschwindigkeit()` method.
- Programmed a global simulation clock (`dGlobaleZeit`) and a `vSimulieren()` method that advances each vehicle's position and time state by the elapsed time interval, preventing double-processing within a single tick.
- Overloaded `operator<<` for formatted console output of all vehicle types using a virtual `vAusgeben(ostream&)` method, and overloaded `operator<` to compare vehicles by total distance covered.
- Managed vehicles using `std::vector` of `unique_ptr<Fahrzeug>` and `shared_ptr<Fahrzeug>`, investigating ownership semantics, `use_count`, `move` transfers, and destructor timing via the debugger.
- Disabled the copy constructor and implemented a custom assignment operator; explored the distinction between copy construction and assignment in an OOP context.

---

### Project Part 2 – Extension of the Traffic System

- Introduced an abstract base class `Simulationsobjekt` consolidating shared properties (name, ID, simulation time) from both `Fahrzeug` and the new `Weg` (road segment) class, including a pure virtual `vSimulieren()` method.
- Implemented the `Weg` class as a subclass of `Simulationsobjekt`, managing a `std::list` of `unique_ptr<Fahrzeug>` and enforcing speed limits via a `Tempolimit` enum class (urban: 50 km/h, rural: 100 km/h, motorway: unlimited). `PKW::dGeschwindigkeit()` respects the road's speed limit; bicycles are exempt.
- Designed a **Strategy pattern** with an abstract `Verhalten` (behavior) class and two concrete subclasses: `Fahren` (driving) and `Parken` (parked/waiting). Each vehicle holds a `Verhalten` instance, which computes the exact distance it may travel in a time step without exceeding the road's end. Vehicles switch behavior on arrival at a new road segment.
- Implemented `Weg::vAnnahme()` (overloaded for driving and parked vehicles), maintaining a sorted list with parked vehicles at the front and driving vehicles at the rear.
- Built a custom **exception hierarchy**: abstract `Fahrausnahme` (derived from `std::exception`) with subclasses `Losfahren` (vehicle departs) and `Streckenende` (vehicle reaches road end). Exceptions are thrown by `Verhalten` and caught in `Weg::vSimulieren()`, which calls the polymorphic `vBearbeiten()` handler.
- Integrated a **graphical output** module via a provided client/server library (`SimuClient`). Implemented virtual `vZeichnen(const Weg&)` methods in `PKW` and `Fahrrad` to call the correct drawing function, rendering cars as red dots and bicycles as green dots on a live TCP/IP visualization window.
- Implemented a **deferred-update template class** `vertagt::VListe<T>`, which buffers `push_front`, `push_back`, and `erase` operations and applies them only upon `vAktualisieren()`. This prevents iterator invalidation when vehicles are inserted or removed from the road list mid-simulation. Completed a provided template skeleton covering `VAktion`, `VPushFront`, `VPushBack`, and `VErase` subclasses.
- Replaced the plain `std::list` in `Weg` with `vertagt::VListe<unique_ptr<Fahrzeug>>`, resolving iterator invalidation during exception handling.

---

### Project Part 3 – Full Traffic Network Simulation

- Implemented a **no-overtaking constraint** in `Fahren::dStrecke()`: when enabled on a road (`Weg::p_bUeberholverbot`), a vehicle cannot pass the position of the vehicle ahead of it in the sorted list. Broken-down (empty-tank) cars are exempt from acting as obstacles.
- Introduced the `Kreuzung` (intersection) class as a subclass of `Simulationsobjekt`, storing outgoing roads and an optional fuel depot (`p_dTankstelle`). Implemented `Kreuzung::vSimulieren()` to cascade simulation calls to all outgoing roads.
- Implemented a static `Kreuzung::vVerbinde()` method that creates bidirectional road connections between two intersections, setting up `weak_ptr` references between roads and intersections to avoid cyclic ownership.
- Implemented `Kreuzung::pZufaelligerWeg()` to randomly select a next road for a vehicle at a junction, excluding the road it arrived on (with dead-end handling). Vehicles are refueled at intersections with available fuel and rerouted as driving vehicles onto the selected road.
- Overloaded `operator>>` for all `Simulationsobjekt` subclasses via a virtual `vEinlesen(istream&)` method, enabling structured deserialization of vehicles and intersections from text streams.
- Designed and implemented a `Simulation` class with `vEinlesen(istream&)` and `vSimulieren(double dDauer, double dZeitschritt)`. The input parser reads a structured ASCII file defining intersections, roads, and vehicle deployments using keywords (`KREUZUNG`, `STRASSE`, `PKW`, `FAHRRAD`), uses a `std::map<string, shared_ptr<Kreuzung>>` for name-based lookup, and throws `std::runtime_error` with line numbers on malformed input.
- Extended `vEinlesen` with an optional graphics mode (`bMitGrafik`), reading pixel coordinates for intersections and roads and passing them to the graphical rendering server, producing a complete animated simulation of the full road network.

---

## Skills Demonstrated

- **Advanced OOP:** multi-level inheritance, abstract classes, pure virtual methods, Strategy and template design patterns
- **Modern C++ (C++17):** `unique_ptr`, `shared_ptr`, `weak_ptr`, `move` semantics, `enum class`, range-based loops
- **STL:** `std::list`, `std::vector`, `std::map`, `std::uniform_int_distribution`, stream I/O
- **Templates:** authored a generic deferred-update list (`VListe<T>`) with an internal action queue
- **Exception Handling:** custom exception hierarchy derived from `std::exception`, structured `try`/`catch` blocks, stream exception handling
- **File I/O:** structured ASCII file parsing with error detection, line-number reporting, and `runtime_error` propagation
- **GUI / Networking:** TCP/IP-based real-time graphical visualization of the simulation via a client/server library
- **Algorithms:** no-overtaking enforcement, Dijkstra-style road traversal, random intersection routing
- **Tooling:** Eclipse CDT, MinGW GCC (C++17), GDB debugger, Java-based simulation display server
