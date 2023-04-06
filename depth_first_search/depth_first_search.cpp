#include "depth_first_search.h"

DepthFirstSearch::DepthFirstSearch(const std::vector<std::vector<int>>& graph, int start_vertex)
    : m_graph(graph), m_visited(graph.size()), m_start_vertex(start_vertex)
{
}

void DepthFirstSearch::dfs()
{
    std::ofstream out("depth_first_search/graph.txt");
    out << m_graph.size() << " " << m_graph[0].size() << " " << m_start_vertex << std::endl;
    for (int i = 0; i < m_graph.size(); i++) {
        for (int j = 0; j < m_graph[i].size(); j++) {
            out << i << " " << m_graph[i][j] << std::endl;
        }
    }
    out.close();
    system("cd depth_first_search & python depth_first_search.py");

    m_visited[m_start_vertex] = true;
    m_stack.push(m_start_vertex);
    std::cout << "Visited vertex: " << m_start_vertex << std::endl;
    while (!m_stack.empty()) {
        int current_vertex = m_stack.top();
        m_stack.pop();

        for (int i = 0; i < m_graph[current_vertex].size(); i++) {
            int neighbor = m_graph[current_vertex][i];
            if (!m_visited[neighbor]) {
                std::cout << "Visited vertex: " << neighbor << std::endl;
                m_visited[neighbor] = true;
                m_stack.push(neighbor);
            }
        }
    }
    system("cd depth_first_search & result.gif");
}

void DepthFirstSearch::dfs(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file\n";
        return;
    }

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

    DepthFirstSearch dfs(graph, start_vertex);
    dfs.dfs();
}