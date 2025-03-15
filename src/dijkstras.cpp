#include "dijkstras.h"
#include <algorithm>
#include <istream>
#include <stdexcept>
#include <vector>

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous){
    int n = G.numVertices;
    vector<int> distances(n, INF);
    previous.assign(n, -1);
    distances[source] = 0;

    using pii = pair<int, int>;
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.push({0, source});

    while (!pq.empty()) {
        int dist = pq.top().first;
        int u = pq.top().second;
        pq.pop();


        if (dist > distances[u])
            continue;

        for (const Edge& e: G[u]){
            int v = e.dst;
            int weight = e.weight;
            if(distances[u] != INF && distances[u] + weight < distances[v]){
                distances[v] = distances[u] + weight;
                previous[v] = u;
                pq.push({distances[v], v});
            }
        }
    }
    return distances;
}

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination){
    vector<int> path;
    if (distances[destination] == INF)
        return path;

    for (int at = destination; at != -1; at = previous[at])
        path.push_back(at);
    reverse(path.begin(), path.end());
    return path;
}

void print_path(const vector<int>& v, int total){
    if (v.empty()) {
        cout << "No path exists." << endl;
        return;
    }

    for (size_t i = 0; i < v.size(); ++i) {
        cout << v[i];
        if (i != v.size() - 1)
            cout << " ";
    }
    cout << "\nTotal cost is "<<total << endl;
}
