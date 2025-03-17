#include "dijkstras.h"

#define UNUSED(x) (void)(x) //TODO: DELETE LATER D/ELETE LA/TER DELETE L/ATER/ DELETE LATER DEL/ETE LATER DELETE LATER /DELETE LATER 




vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    int numVertices = G.size();
    vector<int> distances(numVertices, INF); //make distances have numVertices elements. Each element is INF.
    vector<bool> visited(numVertices, false); //make visited have numVertices elements. Each element is false.
    distances[source] = 0;
    previous[source] = UNDEFINED;
    minHeap minHeap; //pair<vertex, weight>
    minHeap.push({source, 0});
    //for each vertex that had an incoming edge from the most recent u vertex (u==source on first iteration)
    while (!minHeap.empty()) {
        int u = minHeap.top().first; //extract vertex with minimum weight
        minHeap.pop();
        if (visited[u]) continue; //don't examine u vertices that we've already visited
        visited[u] = true;
        //for each outgoing edge from vertex u
        for (Edge edge : G[u]) {
            int v = edge.dst;
            int weight = edge.weight;
            //if we haven't visited v yet, and the distance is lower than the
            //distance beween u and v that we've seen so far
            if (!visited[v] && (distances[u]+weight < distances[v])) {
                distances[v] = distances[u]+weight;
                previous[v] = u;
                minHeap.push({v, distances[v]});
            }
        }
    }
    return distances;
};


vector<int> extract_shortest_path(const vector<int>& /*distances*/, const vector<int>& previous, int destination) {
    vector<int> path;
    int curr_vert = destination;
    //we need to check for curr_vert!=INF because we may reach a point where we are unable to reach the source
    for ( ; curr_vert != UNDEFINED && curr_vert != INF; curr_vert = previous[curr_vert]) {
        path.insert(path.begin(), curr_vert);
    }
    if (curr_vert == INF) {
        vector<int> empty_path;
        return empty_path;
    }
    return path;
};


void print_path(const vector<int>& v, int total) {
    if (total == INF) {
        cout << "No path found. " << endl;
    }
    else {
        for (int vertex : v) {
            cout << vertex << " ";
        }
        cout << endl;
        cout << "Total cost is " << total << endl;
    }
    
};


string get_arg(int argc, char *argv[], string def) {
    if (argc > 1)
        return argv[1];
    else
        return def;
}