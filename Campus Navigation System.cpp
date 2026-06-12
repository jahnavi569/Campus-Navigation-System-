#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <algorithm>

using namespace std;

const int INF = 1000000;

class CampusNavigationSystem {
private:
    int totalLocations;
    vector<string> locationNames;
    vector<vector<int>> campusMap;

public:
    CampusNavigationSystem(int locations) {
        totalLocations = locations;
        locationNames.resize(totalLocations);
        campusMap.resize(totalLocations, vector<int>(totalLocations, INF));

        for (int i = 0; i < totalLocations; i++) {
            campusMap[i][i] = 0;
        }
    }

    void addLocation(int index, string name) {
        locationNames[index] = name;
    }

    void addPath(int source, int destination, int distance) {
        campusMap[source][destination] = distance;
        campusMap[destination][source] = distance;
    }

    void displayCampusMap() {
        cout << "\n===== Campus Distance Matrix =====\n\n";

        for (int i = 0; i < totalLocations; i++) {
            for (int j = 0; j < totalLocations; j++) {
                if (campusMap[i][j] == INF)
                    cout << "INF\t";
                else
                    cout << campusMap[i][j] << "\t";
            }
            cout << endl;
        }
    }

    void findShortestRoute(int source, int destination) {
        vector<int> distance(totalLocations, INF);
        vector<int> parent(totalLocations, -1);
        vector<bool> visited(totalLocations, false);

        distance[source] = 0;

        for (int count = 0; count < totalLocations - 1; count++) {
            int currentNode = -1;
            int minimumDistance = INF;

            for (int i = 0; i < totalLocations; i++) {
                if (!visited[i] && distance[i] < minimumDistance) {
                    minimumDistance = distance[i];
                    currentNode = i;
                }
            }

            if (currentNode == -1) break;

            visited[currentNode] = true;

            for (int neighbor = 0; neighbor < totalLocations; neighbor++) {
                if (!visited[neighbor] &&
                    campusMap[currentNode][neighbor] != INF &&
                    distance[currentNode] + campusMap[currentNode][neighbor] < distance[neighbor]) {

                    distance[neighbor] =
                        distance[currentNode] + campusMap[currentNode][neighbor];

                    parent[neighbor] = currentNode;
                }
            }
        }

        if (distance[destination] == INF) {
            cout << "\nNo route exists between the selected locations.\n";
            return;
        }

        cout << "\nShortest Distance: "
             << distance[destination]
             << " meters\n";

        vector<int> route;
        int current = destination;

        while (current != -1) {
            route.push_back(current);
            current = parent[current];
        }

        reverse(route.begin(), route.end());

        cout << "Route: ";
        for (size_t i = 0; i < route.size(); i++) {
            cout << locationNames[route[i]];
            if (i != route.size() - 1)
                cout << " -> ";
        }
        cout << endl;
    }

    void displayLocations() {
        cout << "\nCampus Locations:\n";
        for (int i = 0; i < totalLocations; i++) {
            cout << i << " : " << locationNames[i] << endl;
        }
    }
};

int main() {
    int numberOfLocations;

    cout << "===== Campus Navigation System =====\n";
    cout << "Enter number of campus locations: ";
    cin >> numberOfLocations;

    CampusNavigationSystem campus(numberOfLocations);

    cin.ignore();

    for (int i = 0; i < numberOfLocations; i++) {
        string location;
        cout << "Enter location " << i << ": ";
        getline(cin, location);
        campus.addLocation(i, location);
    }

    int totalPaths;

    cout << "\nEnter number of paths: ";
    cin >> totalPaths;

    for (int i = 0; i < totalPaths; i++) {
        int source, destination, distance;

        cout << "\nPath " << i + 1
             << " (source destination distance): ";

        cin >> source >> destination >> distance;

        campus.addPath(source, destination, distance);
    }

    int choice;

    do {
        cout << "\n===== MENU =====\n";
        cout << "1. View Campus Map\n";
        cout << "2. Find Shortest Route\n";
        cout << "3. View Locations\n";
        cout << "4. Exit\n";
        cout << "Enter Choice: ";

        cin >> choice;

        switch (choice) {
        case 1:
            campus.displayCampusMap();
            break;

        case 2: {
            int source, destination;

            campus.displayLocations();

            cout << "\nEnter Source Location ID: ";
            cin >> source;

            cout << "Enter Destination Location ID: ";
            cin >> destination;

            campus.findShortestRoute(source, destination);
            break;
        }

        case 3:
            campus.displayLocations();
            break;

        case 4:
            cout << "\nThank You!\n";
            break;

        default:
            cout << "\nInvalid Choice.\n";
        }

    } while (choice != 4);

    return 0;
}
