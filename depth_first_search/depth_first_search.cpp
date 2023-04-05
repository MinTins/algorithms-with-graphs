#include <iostream>
#include <vector>
#include <stack>
#include <fstream>
#include "depth_first_search.h"

void DepthFirstSearch::dfs(std::vector<std::vector<int>>& graph, int start) {
    std::vector<bool> visited(graph.size(), false);
    std::stack<int> stack;

    visited[start] = true;
    stack.push(start);

    while (!stack.empty()) {
        int current = stack.top();
        stack.pop();
        std::cout << current << " ";

        for (int neighbor : graph[current]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                stack.push(neighbor);
            }
        }
    }

    std::cout << std::endl;
}

void DepthFirstSearch::test_dfs() {
    std::vector<std::vector<int>> graph = { {1, 2}, {0, 2, 3}, {0, 1, 3}, {1, 2} };
    int start = 0;

    std::cout << "DFS traversal starting from " << start << ": ";
    dfs(graph, start);
}

void DepthFirstSearch::test_dfs(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error opening file" << std::endl;
        return;
    }

    int num_vertices, num_edges, start;
    file >> num_vertices >> num_edges >> start;

    std::vector<std::vector<int>> graph(num_vertices);
    int vertex1, vertex2;
    for (int i = 0; i < num_edges; i++) {
        file >> vertex1 >> vertex2;
        graph[vertex1].push_back(vertex2);
        graph[vertex2].push_back(vertex1);
    }

    std::cout << "DFS traversal starting from " << start << ": ";
    dfs(graph, start);

    file.close();
}