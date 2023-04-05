#include "prim_minimum_spanning_tree.h"
#include <iostream>
#include <fstream>
#include <limits>

void PrimMinimumSpanningTree::findMST(std::vector<std::vector<int>>& graph, int startNode) {
    int n = graph.size();
    std::vector<int> parent(n, -1);
    std::vector<int> key(n, std::numeric_limits<int>::max());
    std::vector<bool> mstSet(n, false);

    key[startNode] = 0;

    for (int i = 0; i < n - 1; i++) {
        int u = findMinKey(key, mstSet);
        mstSet[u] = true;

        for (int v = 0; v < n; v++) {
            if (graph[u][v] && !mstSet[v] && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    printMST(parent, graph);
}



void PrimMinimumSpanningTree::testPrim() {
    std::vector<std::vector<int>> graph = {
                            {0, 2, 0, 6, 0},
                            {2, 0, 3, 8, 5},
                            {0, 3, 0, 0, 7},
                            {6, 8, 0, 0, 9},
                            {0, 5, 7, 9, 0}
    };
    findMST(graph, 0);
}


void PrimMinimumSpanningTree::findMSTFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file\n";
        return;
    }

    int n, startNode;
    file >> n >> startNode;

    std::vector<std::vector<int>> graph(n, std::vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            file >> graph[i][j];
        }
    }

    findMST(graph, startNode);

    file.close();
}

int PrimMinimumSpanningTree::findMinKey(const std::vector<int>& key, const std::vector<bool>& mstSet) {
    int min = std::numeric_limits<int>::max();
    int minIndex = -1;

    for (int i = 0; i < key.size(); i++) {
        if (!mstSet[i] && key[i] < min) {
            min = key[i];
            minIndex = i;
        }
    }

    return minIndex;
}

void PrimMinimumSpanningTree::printMST(const std::vector<int>& parent, const std::vector<std::vector<int>>& graph) {
    std::cout << "Edge \tWeight\n";
    for (int i = 1; i < parent.size(); i++) {
        std::cout << parent[i] << " - " << i << "\t" << graph[i][parent[i]] << "\n";
    }
}