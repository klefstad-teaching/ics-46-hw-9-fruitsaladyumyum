#include "dijkstras.h"

#define UNUSED(x) (void)(x) //TODO: DELETE LATER D/ELETE LA/TER DELETE L/ATER/ DELETE LATER DEL/ETE LATER DELETE LATER /DELETE LATER 




vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    UNUSED(G);UNUSED(source);UNUSED(previous);vector<int> cars; return cars;
    /* PROVIDED PSEUDO-CODE
    int numVertices = G.size();
    vector<int> distances(numVertices, INF); //TODO: what does this line do???
    vector<bool> visited(numVertices, false);
    distances[source] = 0;
    previous[source] = UNDEFINED;
    priority_queue<pair<int, int>> minHeap; //pair<vertex, weight>
    minHeap.push({source, 0});
    while (!minHeap.empty()) {
        int u = minHeap.extractVertexWithMinimumWeight().first(); //TODO: EXTRACT VERTEX ITH MINIMUM WEIGHT?!?!??
        if (visited[u]) continue;
        visited[u] = true;
        for (Edge edge : G[u]) { //TODO: BUT G is a vector<vector<Edge>>, not a vector<Edge>!!!
            int v = edge.dest; //TODO: .dest?!?!??!!?/
            int weight = edge.second;
            if (!visited[v] && (distances[u]+weight < distances[v])) {
                distances[v] = distances[u]+weight;
                previous[v] = u;
                minHeap.push({v, distances[v]});
            }
        }
    }
    */
};


vector<int> extract_shortest_path(const vector<int>& /*distances*/, const vector<int>& previous, int destination) {UNUSED(previous);UNUSED(destination);vector<int> cars; return cars;};
void print_path(const vector<int>& v, int total) {UNUSED(v);UNUSED(total);};