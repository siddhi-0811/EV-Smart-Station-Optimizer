# EV Smart Station Optimizer

A menu-driven C++ application that recommends the most suitable Electric Vehicle (EV) charging station by considering multiple real-world factors such as shortest distance, battery level, station congestion, charging cost, and optional pre-booking.

---

## Overview

The **EV Smart Station Optimizer** is designed to help electric vehicle users find the **best charging station**, rather than simply the nearest one.

The system combines **Dijkstra's Shortest Path Algorithm** with a **multi-factor cost optimization approach** to recommend the most suitable charging station. It evaluates several parameters including distance, battery level, charging price, station load, and optional pre-booking before selecting the optimal station.

---

## Objectives

- Find the optimal charging station for EV users.
- Minimize travel distance and charging cost.
- Reduce congestion at charging stations.
- Provide an optional charging slot pre-booking facility.
- Enable station owners to efficiently manage charging stations.

---

## Features

### EV Owner Module

The EV owner enters:

- Current location
- Battery percentage

The system then asks whether the user wants to **pre-book a charging slot**.

#### If Pre-booking is Selected

- Guaranteed charging slot
- Additional booking charge
- Station load is automatically updated

#### If Pre-booking is Not Selected

- First Come First Serve (FCFS) allocation
- No additional booking cost

---

### Charging Station Recommendation

The system performs the following steps:

1. Calculates the shortest distance from the EV location to all charging stations using **Dijkstra's Algorithm**.
2. Evaluates every charging station using a multi-factor cost function.
3. Selects the station with the minimum overall cost using a **Greedy Selection Strategy**.

---

## Cost Function Parameters

The recommendation is based on:

- Distance from the EV
- Current station load
- Charging price per unit
- EV battery percentage
- Optional pre-booking cost

---

## Output

The system displays:

- Assigned charging station
- Price per unit
- Shortest distance
- Estimated travel time
- Estimated charging cost
- Booking status

---

## Station Owner Module

The station owner can:

- View charging stations
- Update station load
- Update station capacity
- Add new charging stations
- Update charging price

---

## Station List Module

Users can view:

- Charging station details
- Charging price
- Available free slots

---

## Algorithms Used

- Dijkstra's Shortest Path Algorithm
- Greedy Selection Strategy
- Graph Data Structure
- Priority Queue (STL)

---

## Technologies Used

- C++
- Object-Oriented Programming (OOP)
- Standard Template Library (STL)
- Graphs
- Priority Queue

---

## How to Run

### Compile

```bash
g++ main2.cpp -o ev
```

### Run

```bash
./ev
```

For Windows (MinGW):

```bash
g++ main2.cpp -o ev.exe
ev.exe
```

---

## Future Enhancements

- Graphical User Interface (GUI)
- Google Maps Integration
- Live Charging Slot Availability
- AI-Based Charging Station Recommendation
- Mobile Application Support

---

## Author

**Siddhi Singh**

B.Tech Computer Science & Engineering (AI & Data Science)

MIT World Peace University
