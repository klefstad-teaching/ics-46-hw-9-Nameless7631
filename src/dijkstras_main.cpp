#include "dijkstras.h"
#include <vector>

int main(){
    string filename = "src/small.txt";
    Graph G;
    file_to_graph(filename, G);

    std::vector<int> previous;
    std::vector<int> distances = dijkstra_shortest_path(G, 0, previous);

    int destination = 3;
    std::vector<int> path = extract_shortest_path(distances, previous, destination);

    print_path(path, distances[destination]);
}