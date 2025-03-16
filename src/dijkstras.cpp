#include "dijkstras.h"
#include <vector>
#include <queue>
#include <stack>

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous){
    int numVertices = G.numVertices;
    std::vector<int> distances(numVertices, INF);
    std::vector<bool> visited(numVertices, false);

    distances[source] = 0;
    previous.assign(numVertices, -1);

    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> minHeap;
    minHeap.push({0, source});

    while(!minHeap.empty()){
        int u = minHeap.top().second;
        minHeap.pop();

        if (visited[u]) continue;
        visited[u] = true;

        for (const Edge& edge : G[u]) {
            int v = edge.dst;
            int weight = edge.weight;
            if (!visited[v] && distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
                previous[v] = u;
                minHeap.push({distances[v], v});
            }
        }
    }
    return distances;
}

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination){
    std::stack<int> path;
    
    for (int i = destination; i != -1; i = previous[i]) {
        path.push(i);
    }
    
    std::vector<int> shortest_path;
    while(!path.empty()){
        shortest_path.push_back(path.top());
        path.pop();
    }
    return shortest_path;
}

void print_path(const vector<int>& v, int total){
    for(int i : v) std::cout << i << " ";
    std::cout << std::endl;
    std::cout << "Total cost is " << total << std::endl;
}
