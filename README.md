# EV Smart Station Optimizer

## Overview

The **EV Smart Station Optimizer** is a menu-driven C++ application designed to help electric vehicle (EV) users find the most suitable charging station based on multiple real-world factors rather than simply selecting the nearest one.

The system combines **Dijkstra's Shortest Path Algorithm** with a **multi-factor cost optimization approach** to recommend the best charging station by considering travel distance, station congestion, charging price, battery level, and optional slot pre-booking.

---

## Objectives

- Recommend the optimal EV charging station.
- Minimize travel distance and charging cost.
- Reduce congestion at charging stations.
- Provide users with an option to reserve charging slots.
- Assist station owners in managing charging stations efficiently.

---

## Modules

### 1. EV Owner Module

The EV owner enters:

- Current location
- Battery percentage

The system then asks whether the user wants to **pre-book a charging slot**.

### Pre-booking

If selected:

- Guaranteed charging slot
- Additional booking charge

If not selected:

- First Come First Serve (FCFS) allocation
- No additional booking cost

---

### 2. Station Selection Process

The system performs the following steps:

1. Calculates the shortest distance from the EV location to all charging stations using **Dijkstra's Algorithm**.
2. Evaluates every available charging station using a cost function.
3. Selects the station with the minimum overall cost using a greedy approach.

---

## Cost Function

The charging station recommendation is based on multiple parameters:

- Distance to the station
- Current station load
- Charging price per unit
- EV battery level
- Optional pre-booking cost

This ensures that the selected station provides the best overall balance instead of simply being the closest one.

---

## Output

After selecting the optimal charging station, the system displays:

- Assigned charging station
- Price per unit
- Distance
- Estimated travel time
- Estimated charging cost

If pre-booking is selected, the system also reserves the charging slot by updating the station load.

---

## Station Owner Module

The station owner can:

- View all charging stations
- Update station load
- Modify charging capacity
- Add new charging stations
- Update charging price

---

## Station List Module

Users can view:

- Available charging stations
- Charging price
- Available (free) slots

---

## Algorithms Used

- Dijkstra's Shortest Path Algorithm
- Greedy Selection Strategy
- Graph Data Structure
- Priority Queue (STL)

---

## Technologies Used

- C++
- Standard Template Library (STL)
- Graphs
- Priority Queue
- Object-Oriented Programming (OOP)

---

## Future Enhancements

- Graphical User Interface (GUI)
- Real-time traffic information
- Live charging slot availability
- GPS/Google Maps integration
- Online database support
- AI-based charging station recommendation

---

## Conclusion

Unlike traditional navigation systems that only consider the shortest route, this project performs **multi-factor optimization** by balancing:

- Distance
- Charging cost
- Station congestion
- Battery level
- User preference (pre-booking)

This approach provides EV users with a more practical and efficient charging station recommendation system.

---

## Author

**Siddhi Singh**

B.Tech Computer Science and Engineering (AI & Data Science)

MIT World Peace University
