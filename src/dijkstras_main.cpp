#include "dijkstras.h"



int main(int argc, char *argv[]) {
    string filename = get_arg(argc, argv, "small.txt");
    Graph G;
    file_to_graph(filename, G);

    //for each source vertex
    for (int source=0; source < G.numVertices; ++source) {
        vector<int> previous(G.numVertices, INF);
        vector<int> distances = dijkstra_shortest_path(G, source, previous);
        //for each destination vertex
        for (int dest=0; dest < G.numVertices; ++dest) {
            print_path(extract_shortest_path(distances, previous, dest), distances[dest]);
        }
    }

    return 0;
}