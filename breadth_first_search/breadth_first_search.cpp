#include "breadth_first_search.h"

BreadthFirstSearch::BreadthFirstSearch(const std::vector<std::vector<int>>& graph, int start_vertex)
    : m_graph(graph), m_visited(graph.size()), m_start_vertex(start_vertex)
{
}

void BreadthFirstSearch::bfs()
{
    std::ofstream out("breadth_first_search/graph.txt");
    out << m_graph.size() << " " << m_graph[0].size() << " " << m_start_vertex << std::endl;
    for (int i = 0; i < m_graph.size(); i++) {
        for (int j = 0; j < m_graph[i].size(); j++) {
            out << i << " " << m_graph[i][j] << std::endl;
        }
    }
    out.close();
    system("cd breadth_first_search & python breadth_first_search.py");

    m_visited[m_start_vertex] = true;
    m_queue.push(m_start_vertex);

    while (!m_queue.empty()) {
        int current_vertex = m_queue.front();
        m_queue.pop();
        std::cout << "Visited vertex: " << current_vertex << std::endl;

        for (int i = 0; i < m_graph[current_vertex].size(); i++) {
            int neighbor = m_graph[current_vertex][i];
            if (!m_visited[neighbor]) {
                m_visited[neighbor] = true;
                m_queue.push(neighbor);
            }
        }
    }
    system("cd breadth_first_search & result.gif");
}

void BreadthFirstSearch::bfs(const std::string& filename)
{
    std::ifstream in(filename);
    int n, m, start_vertex;
    in >> n >> m >> start_vertex;
    std::vector<std::vector<int>> graph(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        in >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    in.close();

    BreadthFirstSearch bfs(graph, start_vertex);
    bfs.bfs();
}