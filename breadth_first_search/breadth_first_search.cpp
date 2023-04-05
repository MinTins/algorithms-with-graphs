#include "breadth_first_search.h"
#include <queue>

Graph::Graph(int V) {
    this->V = V;
    adj.resize(V);
}

void Graph::addEdge(int v, int w) {
    adj[v].push_back(w);
}

std::vector<int> Graph::BFS(int s) {
    std::vector<bool> visited(V, false);
    std::vector<int> result;

    std::queue<int> q;
    visited[s] = true;
    q.push(s);

    while (!q.empty()) {
        s = q.front();
        result.push_back(s);
        q.pop();

        for (auto i = adj[s].begin(); i != adj[s].end(); ++i) {
            if (!visited[*i]) {
                visited[*i] = true;
                q.push(*i);
            }
        }
    }

    return result;
}