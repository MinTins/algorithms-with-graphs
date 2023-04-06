#ifndef A_STAR_SHORTEST_PATH_H
#define A_STAR_SHORTEST_PATH_H

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <cmath>

class AStarShortestPath {
public:
    AStarShortestPath(const std::vector<std::vector<std::pair<int, double>>>& graph, int start_vertex);
    void a_star();
    void a_star(const std::string& filename);

private:
    std::vector<std::vector<std::pair<int, double>>> m_graph;
    std::vector<bool> m_visited;
    std::vector<double> m_distances;
    std::vector<int> m_parents;
    int m_start_vertex;

    double heuristic(int from, int to);
};

#endif // A_STAR_SHORTEST_PATH_H#pragma once
