#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int INF = 1000000000;

// -------- EDGE --------
class Edge {
public:
    int node, weight;
    Edge(int n, int w) {
        node = n;
        weight = w;
    }
};

// -------- GRAPH --------
class Graph {
public:
    int V; //no.of nodes (location)
    vector<vector<Edge>> adj; //adj list list of list of connections

    Graph(int v) {
        V = v;
        adj.resize(V);
    }

    void addEdge(int u, int v, int w) {
        adj[u].push_back(Edge(v, w));
        adj[v].push_back(Edge(u, w));
    }
};

vector<int> dijkstra(Graph &g, int src) {

    // Step 1: Create distance list and set all to INF
    vector<int> dist(g.V);
    for(int i = 0; i < g.V; i++) {
        dist[i] = INF;
    }

    // Step 2: Distance of source to itself is 0
    dist[src] = 0;

    // Step 3: Create priority queue (min heap)
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;

    // Step 4: Push starting node
    pq.push(make_pair(0, src));

    // Step 5: Loop until queue is empty
    while(pq.empty() == false) {

        // Get top element
        pair<int,int> topElement = pq.top();
        pq.pop();

        int currentDistance = topElement.first;
        int currentNode = topElement.second;

        // Step 6: Check all neighbors of current node
        for(int i = 0; i < g.adj[currentNode].size(); i++) {

            Edge currentEdge = g.adj[currentNode][i];

            int nextNode = currentEdge.node;
            int weight = currentEdge.weight;

            // Step 7: Check if shorter path found
            if(dist[nextNode] > dist[currentNode] + weight) {

                // Update distance
                dist[nextNode] = dist[currentNode] + weight;

                // Push updated value into queue
                pq.push(make_pair(dist[nextNode], nextNode));
            }
        }
    }

    // Step 8: Return final distances
    return dist;
}

// -------- EV --------
class EV {
public:
    int id, location, battery;

    EV(int i, int loc, int b) {
        id = i;
        location = loc;
        battery = b;
    }
};

// -------- STATION --------
class Station {
public:
    int id, location, capacity, load, price;

    Station(int i, int loc, int cap, int l, int p) {
        id = i;
        location = loc;
        capacity = cap;
        load = l;
        price = p;
    }
};

// -------- COST --------
int calculateCost(int distance, int load, int capacity, int battery, int price, bool booking) {

    int cost = distance;

    // Battery critical → prioritize distance
    if(battery < 20) {
        cost += distance * 2;
    }

    // Load factor
    float loadFactor = (float)load / capacity;
    cost += loadFactor * 20;

    // Price factor
    cost += price * 2;

    return cost;
}

// -------- TOTAL COST --------
int calculateTotalCost(int battery, int distance, int price, bool booking) {

    int consumptionRate = 2; // battery per unit distance

    int batteryAfterTravel = battery - (distance * consumptionRate);

    if(batteryAfterTravel < 0) batteryAfterTravel = 0;

    int energy = (100 - batteryAfterTravel);

    int cost = energy * price;

    if(booking) cost += 50;

    return cost;
}
// -------- TIME --------
int calculateTime(int distance) {
    return distance * 2;
}

// -------- BEST STATION --------
int findBestStation(Graph &g, EV &ev, vector<Station> &stations, int &bestDist, bool booking) {

    vector<int> dist = dijkstra(g, ev.location);

    int best = -1;
    int minCost = INF;

    for(int i = 0; i < stations.size(); i++) {

        if(stations[i].load >= stations[i].capacity) continue;

        int distance = dist[stations[i].location];
        int load = stations[i].load;
        int price = stations[i].price;

        int cost = calculateCost(distance, load, stations[i].capacity, ev.battery, price, booking);

        if(cost < minCost) {
            minCost = cost;
            best = i;
            bestDist = distance;
        }
    }

    return best;
}

// -------- LOCATION --------
int getLocation(string loc) {
    if(loc == "A") return 0;
    if(loc == "B") return 1;
    if(loc == "C") return 2;
    if(loc == "D") return 3;
    if(loc == "E") return 4;
    if(loc == "F") return 5;
    return 0;
}

int main() {

    // -------- GRAPH SETUP --------
   Graph g(15);

// Route 1 → very short
g.addEdge(0,1,2);
g.addEdge(1,2,2);
g.addEdge(2,3,1);   // total = 5

// Route 2 → medium
g.addEdge(0,4,5);
g.addEdge(4,5,4);
g.addEdge(5,6,3);   // total = 12

// Route 3 → long but smooth
g.addEdge(0,7,8);
g.addEdge(7,8,3);
g.addEdge(8,9,2);   // total = 13

// Cross connections (non-equal paths)
g.addEdge(2,5,6);   // makes alt path but worse
g.addEdge(5,8,2);   // improves mid → long path
g.addEdge(6,9,4);

// Extension (extra depth)
g.addEdge(9,10,3);
g.addEdge(10,11,2);
g.addEdge(11,12,4);
g.addEdge(12,13,3);
g.addEdge(13,14,2);

    // -------- STATIONS --------
    vector<Station> stations;

// VERY CLOSE but expensive
stations.push_back(Station(1,3,4,2,12));   // distance ≈ 5

// MEDIUM balanced
stations.push_back(Station(2,6,4,2,8));    // distance ≈ 12

// FAR but cheap
stations.push_back(Station(3,9,5,1,5));    // distance ≈ 13

// FAR + congested
stations.push_back(Station(4,11,3,3,6));   // distance ≈ 18

// VERY FAR but empty
stations.push_back(Station(5,14,4,0,7));   // distance ≈ 23

    int choice = 0;

    // -------- MAIN LOOP --------
    while(true) {

        cout << "\n====== EV SYSTEM ======\n";
        cout << "1. EV Owner\n";
        cout << "2. Station Owner\n";
        cout << "3. View Station List\n";
        cout << "4. Exit\n";

        cout << "Enter choice: ";
        cin >> choice;

        // ================= EV OWNER =================
        if(choice == 1) {

            string loc;
            int battery;

            cout << "\nEnter location (A-F): ";
            cin >> loc;

            cout << "Enter battery percentage: ";
            cin >> battery;

            int bookingChoice;
            cout << "Do you want to pre-book?\n";
            cout << "1. Yes\n2. No\n";
            cin >> bookingChoice;

            bool booking;
            if(bookingChoice == 1) {
                booking = true;
            } else {
                booking = false;
            }

            // create EV
            EV ev(1, getLocation(loc), battery);

            int distance = 0;

            // find best station
            int index = findBestStation(g, ev, stations, distance, booking);

            if(index != -1) {

                // if booking, update load
                if(booking == true) {
                    stations[index].load = stations[index].load + 1;
                }

                int price = stations[index].price;

                int totalCost = calculateTotalCost(battery, distance, price, booking);
                int time = calculateTime(distance);

                cout << "\n--- RESULT ---\n";
                cout << "Assigned Station: " << stations[index].id << endl;
                cout << "Price per unit: " << price << endl;
                cout << "Distance: " << distance << endl;
                cout << "Time required: " << time << " minutes\n";
                cout << "Total Cost: " << totalCost << endl;

                if(booking == true) {
                    cout << "Slot is pre-booked\n";
                } else {
                    cout << "No booking (first come first serve)\n";
                }

            } else {
                cout << "No station available\n";
            }
        }

        // ================= STATION OWNER =================
        else if(choice == 2) {

            cout << "\n--- Station Owner Menu ---\n";
            cout << "1. View Stations\n";
            cout << "2. Update Load\n";
            cout << "3. Update Capacity\n";
            cout << "4. Add New Station\n";
            cout << "5. Update Price\n";

            int op;
            cout << "Enter option: ";
            cin >> op;

            // -------- VIEW --------
            if(op == 1) {

                for(int i = 0; i < stations.size(); i++) {

                    cout << "ID: " << stations[i].id << endl;
                    cout << "Load: " << stations[i].load << endl;
                    cout << "Capacity: " << stations[i].capacity << endl;
                    cout << "Price: " << stations[i].price << endl;
                    cout << "------------------------\n";
                }
            }

            // -------- UPDATE LOAD --------
            else if(op == 2) {

                int id, newLoad;

                cout << "Enter station ID: ";
                cin >> id;

                cout << "Enter new load: ";
                cin >> newLoad;

                for(int i = 0; i < stations.size(); i++) {

                    if(stations[i].id == id) {
                        stations[i].load = newLoad;
                    }
                }
            }

            // -------- UPDATE CAPACITY --------
            else if(op == 3) {

                int id, newCap;

                cout << "Enter station ID: ";
                cin >> id;

                cout << "Enter new capacity: ";
                cin >> newCap;

                for(int i = 0; i < stations.size(); i++) {

                    if(stations[i].id == id) {
                        stations[i].capacity = newCap;
                    }
                }
            }

            // -------- ADD STATION --------
            else if(op == 4) {

                int id, loc, cap, load, price;

                cout << "Enter ID: ";
                cin >> id;

                cout << "Enter location (0-5): ";
                cin >> loc;

                cout << "Enter capacity: ";
                cin >> cap;

                cout << "Enter current load: ";
                cin >> load;

                cout << "Enter price: ";
                cin >> price;

                Station newStation(id, loc, cap, load, price);
                stations.push_back(newStation);
            }

            // -------- UPDATE PRICE --------
            else if(op == 5) {

                int id, newPrice;

                cout << "Enter station ID: ";
                cin >> id;

                cout << "Enter new price: ";
                cin >> newPrice;

                for(int i = 0; i < stations.size(); i++) {

                    if(stations[i].id == id) {
                        stations[i].price = newPrice;
                    }
                }
            }
        }

        // ================= VIEW STATIONS =================
        else if(choice == 3) {

            cout << "\n--- Station List ---\n";

            for(int i = 0; i < stations.size(); i++) {

                int freeSlots = stations[i].capacity - stations[i].load;

                cout << "Station ID: " << stations[i].id << endl;
                cout << "Location: " << stations[i].location << endl;
                cout << "Price: " << stations[i].price << endl;
                cout << "Free Slots: " << freeSlots << endl;
                cout << "------------------------\n";
            }
        }

        // ================= EXIT =================
        else if(choice == 4) {
            cout << "Exiting program...\n";
            break;
        }

        else {
            cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}
