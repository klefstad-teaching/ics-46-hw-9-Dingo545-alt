#include <gtest/gtest.h>

#include "dijkstras.h"
#include "ladder.h"


// Optional: Debug helper that asserts edge destinations are in bounds.
static void validateGraph(const Graph& G) {
    int n = G.numVertices;
    for (int u = 0; u < n; ++u) {
        for (const Edge& e : G[u]) {
            // Assert that the destination is valid.
            assert(e.dst >= 0 && e.dst < n && "Edge destination is out of bounds!");
        }
    }
}


TEST(DijkstraTest, SimpleGraphTest) {
    Graph G;
    G.numVertices = 5;
    G.resize(G.numVertices);

    
    G[0].push_back(Edge(0, 1, 1));
    G[0].push_back(Edge(0, 2, 4));
    G[1].push_back(Edge(1, 2, 2));
    G[1].push_back(Edge(1, 3, 6));
    G[2].push_back(Edge(2, 3, 3));

    validateGraph(G);

    int source = 0;
    vector<int> previous;
    vector<int> distances = dijkstra_shortest_path(G, source, previous);

    EXPECT_EQ(distances[0], 0);
    EXPECT_EQ(distances[1], 1);
    EXPECT_EQ(distances[2], 3);
    EXPECT_EQ(distances[3], 6);

    vector<int> path = extract_shortest_path(distances, previous, 3);
    vector<int> expected_path = {0, 1, 2, 3};
    EXPECT_EQ(path, expected_path);
}

TEST(DijkstraTest, DisconnectedGraphTest) {
    Graph G;
    G.numVertices = 3;
    G.resize(G.numVertices);

    G[0].push_back(Edge(0, 1, 5));

    int source = 0;
    vector<int> previous;
    vector<int> distances = dijkstra_shortest_path(G, source, previous);

    EXPECT_EQ(distances[0], 0);
    EXPECT_EQ(distances[1], 5);
    EXPECT_EQ(distances[2], INF);

    vector<int> path = extract_shortest_path(distances, previous, 2);
    vector<int> expected_path;
    EXPECT_EQ(path, expected_path);
}
