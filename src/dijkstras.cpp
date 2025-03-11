#include <iostream>
#include "dijkstras.h"


vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
  int n = G.size();
}

// vector<int> extract_shortest_path(const vector<int>& /*distances*/, const vector<int>& previous, int destination) {

// }

void print_path(const vector<int>& v, int total) {
  for (int n : v) {
    std::cout << n << ' ';
  }
  std::cout << "\nTotal cost is " << total;
}

