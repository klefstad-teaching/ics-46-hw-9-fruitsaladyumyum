#ifndef DIJKSTRAS_H
#define DIJKSTRAS_H

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>
#include <stack>

using namespace std;

constexpr int INF = numeric_limits<int>::max();
constexpr int UNDEFINED = -1; //STUDENT-ADDED SINCE THEY WERE ON THE SLIDES

struct Edge {
    int src=0;
    int dst=0;
    int weight=0;
    Edge(int s = 0, int d = 0, int w = 0) : src(s), dst(d), weight(w) {}
    friend istream& operator>>(istream& in, Edge& e)
    {
        return in >> e.src >> e.dst >> e.weight;
    }

    friend ostream& operator<<(ostream& out, const Edge& e)
    {
        return out << "(" << e.src << "," << e.dst << "," << e.weight << ")";
    }
};

struct Graph : public vector<vector<Edge>> {
    int numVertices=0;
};

//STUDENT-ADDED DUE TO EXISTNECE IN SLIDES
struct Compare {
    bool operator()(pair<int, int> a, pair<int, int> b) {
        if (a.second > b.second) {
            return true;
        }
        else {
            return false;
        }
    }
};
using minHeap = priority_queue<pair<int, int>, vector<pair<int, int>>, Compare>; //pair<vertex, weight>

inline istream& operator>>(istream& in, Graph& G) {
    if (!(in >> G.numVertices))
        throw runtime_error("Unable to find input file");
    G.resize(G.numVertices);
    for (Edge e; in >> e;)
        G[e.src].push_back(e);
    return in;
}

inline void file_to_graph(const string& filename, Graph& G) {
    ifstream in(filename);
    if (!in) {
        throw runtime_error("Can't open input file");
    }
    in >> G;
    in.close();
}

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous);
vector<int> extract_shortest_path(const vector<int>& /*distances*/, const vector<int>& previous, int destination);
void print_path(const vector<int>& v, int total);

string get_arg(int argc, char *argv[], string def); //STUDENT-ADDED


#endif