#include <iostream>
#include <vector>
#include <queue>
#include <climits>

struct Edge {
    int to;
    int weight;
};

void Dijkstra(const std::vector<std::vector<Edge>>& graph, int source, int target) {
    std::vector<int> min_distance(graph.size(), INT_MAX);
    min_distance[source] = 0;
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> pq;
    pq.push({0, source});

    while (!pq.empty()) {
        int dist = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (dist > min_distance[u]) {
            continue;
        }

        for (const auto& edge : graph[u]) {
            if (min_distance[edge.to] > min_distance[u] + edge.weight) {
                min_distance[edge.to] = min_distance[u] + edge.weight;
                pq.push({min_distance[edge.to], edge.to});
            }
        }
    }

    if (min_distance[target] == INT_MAX) {
        std::cout << "There is no path from " << source << " to " << target << ".\n";
    } else {
        std::cout << "The shortest path from " << source << " to " << target << " has a cost of " << min_distance[target] << ".\n";
    }
}

int main() {
    int V, E, u, v, w;
    std::cout << "Enter the number of vertices and edges: ";
    std::cin >> V >> E;
    std::vector<std::vector<Edge>> graph(V);

    std::cout << "Enter the edges in the format 'u v weight' (0-indexed):\n";
    for (int i = 0; i < E; ++i) {
        std::cin >> u >> v >> w;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w}); // If the graph is undirected
    }

    int source, target;
    std::cout << "Enter the source node: ";
    std::cin >> source;
    std::cout << "Enter the target node: ";
    std::cin >> target;

    Dijkstra(graph, source, target);

    return 0;
}
