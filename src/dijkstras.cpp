#include <iostream>
#include <queue>
#include "dijkstras.h"

auto cmp = [](const Node& a, const Node& b) {
    return a.weight > b.weight; // smaller weight has higher priority
};

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
  int n = G.size();

  vector<int> distance(n, INF);
  vector<bool> visited(n, false);
  previous.assign(n, -1);

  std::priority_queue<Node, std::vector<Node>, decltype(cmp)> pq(cmp);
  pq.push(Node{source, 0});

  distance[source] = 0;

  while (!pq.empty()) {
    Node current = pq.top();
    pq.pop();


    int u = current.vertex;


    if (visited[u]) {continue;}

    visited[u] = true;

    for (Edge const & e : G[u]) {
      int v = e.dst;
      int weight = e.weight;

      if (!visited[v] && distance[u] + weight < distance[v]) {
        distance[v] = distance[u] + weight;
        previous[v] = u;

        pq.push(Node{v, distance[v]});
      }
    }
  }
  return distance;
}

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination) {
    vector<int> path;

    if (distances[destination] == INF) {
        return {};
    }

    for (int at = destination; at != -1; at = previous[at])
        path.push_back(at);
    reverse(path.begin(), path.end());
    return path;
}

void print_path(const vector<int>& v, int total) {
  for (int n : v) {
    std::cout << n << ' ';
  }
  std::cout << "\nTotal cost is " << total;
}

