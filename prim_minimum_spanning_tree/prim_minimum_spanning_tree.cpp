#include "prim_minimum_spanning_tree.h"

PrimMinimumSpanningTree::PrimMinimumSpanningTree(const std::vector<std::vector<std::pair<int, int>>>& graph, int start_vertex)
    : m_graph(graph), m_visited(graph.size()), m_min_distance(graph.size(), INT_MAX), m_vertex(graph.size()), m_start_vertex(start_vertex)
{
}

void PrimMinimumSpanningTree::prim()
{
    std::ofstream out("prim_minimum_spanning_tree/graph.txt");
    out << m_graph.size() << " " << m_graph[0].size() << " " << m_start_vertex << std::endl;
    for (int i = 0; i < m_graph.size(); i++) {
        for (int j = 0; j < m_graph[i].size(); j++) {
            out << i << " " << m_graph[i][j].first << " " << m_graph[i][j].second << std::endl;
        }
    }
    out.close();
    system("cd prim_minimum_spanning_tree & python prim_minimum_spanning_tree.py");

    m_min_distance[m_start_vertex] = 0;
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
    pq.push(std::make_pair(0, m_start_vertex));

    while (!pq.empty()) {
        int current_vertex = pq.top().second;
        pq.pop();

        if (m_visited[current_vertex]) {
            continue;
        }
        m_visited[current_vertex] = true;

        for (int i = 0; i < m_graph[current_vertex].size(); i++) {
            int neighbor = m_graph[current_vertex][i].first;
            int weight = m_graph[current_vertex][i].second;
            if (!m_visited[neighbor] && weight < m_min_distance[neighbor]) {
                m_min_distance[neighbor] = weight;
                m_vertex[neighbor] = current_vertex;
                pq.push(std::make_pair(m_min_distance[neighbor], neighbor));
            }
        }
    }

    std::cout << "Minimum Spanning Tree:\n";
    for (int i = 1; i < m_graph.size(); i++) {
        std::cout << "Edge: " << m_vertex[i] << " - " << i << " Weight: " << m_min_distance[i] << std::endl;
    }
    system("cd prim_minimum_spanning_tree & result.gif");
}

void PrimMinimumSpanningTree::prim(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file\n";
        return;
    }
    std::ifstream in(filename);
    int n, m, start_vertex;
    in >> n >> m >> start_vertex;
    std::vector<std::vector<std::pair<int, int>>> graph(n);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        in >> u >> v >> w;
        graph[u].push_back(std::make_pair(v, w));
        graph[v].push_back(std::make_pair(u, w));
    }
    in.close();

    PrimMinimumSpanningTree prim(graph, start_vertex);
    prim.prim();
}