// Represent a given graph using adjacency matrix/list to perform DFS and BFS traversals. Use the map of the area around  college as a graph.
// Identify the prominent land marks as nodes & perform  DFS & BFS on that. 
// Landmark (Node)     	  Label
// College Entrance     	A
// Canteen	              B
// Library	              C
// Hostel	                D 
// Admin Office	          E

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int N = 5;  // Total landmarks (A to E)
vector<string> landmarks = {"College Entrance", "Canteen", "Library", "Hostel", "Admin Office"};

// Adjacency list
vector<int> graph[N];
bool visited[N];

// Add undirected edge
void addEdge(int u, int v) {
    graph[u].push_back(v);
    graph[v].push_back(u);
}

// DFS Traversal (prints in desired format)
void DFS(int node, vector<string>& path) {
    visited[node] = true;
    path.push_back(landmarks[node]);

    for (int neighbor : graph[node]) {
        if (!visited[neighbor])
            DFS(neighbor, path);
    }
}

// BFS Traversal (prints in desired format)
void BFS(int start) {
    fill(visited, visited + N, false);
    queue<int> q;
    vector<string> path;

    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        path.push_back(landmarks[curr]);

        for (int neighbor : graph[curr]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }

    // Print path 
    for (size_t i = 0; i < path.size(); ++i) {
        cout << path[i];
        if (i < path.size() - 1) cout << " -> ";
    }
    cout << endl;
}

int main() {
    // Add edges based on map
    addEdge(0, 1); // A-B
    addEdge(0, 2); // A-C
    addEdge(1, 3); // B-D
    addEdge(2, 4); // C-E
    addEdge(3, 4); // D-E

    cout << "\nDFS Traversal from College Entrance:\n";
    fill(visited, visited + N, false);
    vector<string> dfsPath;
    DFS(0, dfsPath);
    for (size_t i = 0; i < dfsPath.size(); ++i) {
        cout << dfsPath[i];
        if (i < dfsPath.size() - 1) cout << " -> ";
    }           

    cout << "\n\nBFS Traversal from College Entrance:\n";
    BFS(0);

    return 0;
}
