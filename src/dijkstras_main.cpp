#include "dijkstras.h"
#include <cassert>

void test_dijkstra_from_file() {
    cout << "--------------------" << '\n';
    cout << "TESTING DIJKSTRA FROM FILES" << '\n';

    // Test with small.txt
    {
        string filename = "src/small.txt";
        Graph G;
        file_to_graph(filename, G);

        // 4
        // 0 3 1
        // 3 0 3
        // 1 0 5
        // 3 1 2
        // 2 3 8
        // 1 2 3
        //  distance[0] = 0
        //  distance[3] = 1       (0 -> 3)
        //  distance[1] = 3       (0 -> 3 -> 1)
        //  distance[2] = 6       (0 -> 3 -> 1 -> 2)
        int source = 0;
        vector<int> previous;
        vector<int> distances = dijkstra_shortest_path(G, source, previous);
        vector<int> expected = {0, 3, 6, 1};

        assert(distances.size() == expected.size());
        for (size_t i = 0; i < expected.size(); i++) {
            assert(distances[i] == expected[i]);
        }

        // Extract shortest path from 0 to 2 expected: 0 -> 3 -> 1 -> 2
        vector<int> path = extract_shortest_path(distances, previous, 2);
        vector<int> expected_path = {0, 3, 1, 2};
        assert(path == expected_path);

        cout << "small.txt Dijkstra test passed. ";
        print_path(path, distances[2]);
        cout << '\n';
    }

    // Test with medium.txt
    {
        string filename = "src/medium.txt";
        Graph G;
        file_to_graph(filename, G);

        // 6
        // 0 1 5
        // 1 2 4
        // 2 3 9
        // 3 4 7
        // 4 0 1
        // 0 5 2
        // 5 4 8
        // 3 5 3
        // 5 2 1
        //  distance[0] = 0
        //  distance[1] = 5       (0 -> 1)
        //  distance[2] = 3       (0 -> 5 -> 2)
        //  distance[3] = 12      (0 -> 5 -> 2 -> 3)
        //  distance[4] = 10      (0 -> 5 -> 2 -> 3 -> 4) or (0 -> 5 -> 4) is 2+8=10
        //  distance[5] = 2       (0 -> 5)
        int source = 0;
        vector<int> previous;
        vector<int> distances = dijkstra_shortest_path(G, source, previous);
        vector<int> expected = {0, 5, 3, 12, 10, 2};

        assert(distances.size() == expected.size());
        for (size_t i = 0; i < expected.size(); i++) {
            assert(distances[i] == expected[i]);
        }

        // Extract shortest path from 0 to 3 | expected: 0 -> 5 -> 2 -> 3
        vector<int> path = extract_shortest_path(distances, previous, 3);
        vector<int> expected_path = {0, 5, 2, 3};
        assert(path == expected_path);

        cout << "medium.txt Dijkstra test passed. ";
        print_path(path, distances[3]);
        cout << '\n';
    }
}

int main() {
  test_dijkstra_from_file();
}