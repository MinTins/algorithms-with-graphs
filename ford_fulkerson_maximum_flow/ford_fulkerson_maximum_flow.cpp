#include "ford_fulkerson_maximum_flow.h"

FordFulkersonMaximumFlow::FordFulkersonMaximumFlow(const std::vector<std::vector<int>>& graph, int start_vertex, int end_vertex)
    : m_graph(graph), m_residual_graph(graph), m_parent(graph.size()), m_visited(graph.size()), m_start_vertex(start_vertex), m_end_vertex(end_vertex)
{
}

bool FordFulkersonMaximumFlow::bfs()
{
    std::fill(m_visited.begin(), m_visited.end(), false);
    std::queue<int> q;
    q.push(m_start_vertex);
    m_visited[m_start_vertex] = true;
    m_parent[m_start_vertex] = -1;

    while (!q.empty()) {
        int current_vertex = q.front();
        q.pop();

        for (int neighbor : m_residual_graph[current_vertex]) {
            if (!m_visited[neighbor] && m_residual_graph[current_vertex][neighbor] > 0) {
                q.push(neighbor);
                m_visited[neighbor] = true;
                m_parent[neighbor] = current_vertex;
            }
        }
    }

    return m_visited[m_end_vertex];
}

int FordFulkersonMaximumFlow::find_min_residual_capacity()
{
    int current_vertex = m_end_vertex;
    int min_residual_capacity = INT_MAX;

    while (current_vertex != m_start_vertex) {
        int parent = m_parent[current_vertex];
        min_residual_capacity = std::min(min_residual_capacity, m_residual_graph[parent][current_vertex]);
        current_vertex = parent;
    }

    return min_residual_capacity;
}

void FordFulkersonMaximumFlow::update_residual_graph(int min_residual_capacity)
{
    int current_vertex = m_end_vertex;

    while (current_vertex != m_start_vertex) {
        int parent = m_parent[current_vertex];
        m_residual_graph[parent][current_vertex] -= min_residual_capacity;
        m_residual_graph[current_vertex][parent] += min_residual_capacity;
        current_vertex = parent;
    }
}

void FordFulkersonMaximumFlow::ford_fulkerson()
{
    std::ofstream out("ford_fulkerson_maximum_flow/graph.txt");
    out << m_graph.size() << " " << m_graph[0].size() << " " << m_start_vertex << " " << m_end_vertex << std::endl;
    for (int i = 0; i < m_graph.size(); i++) {
        for (int j = 0; j < m_graph[i].size(); j++) {
            out << i << " " << j << " " << m_graph[i][j] << std::endl;
        }
    }
    out.close();
    system("cd ford_fulkerson_maximum_flow & python ford_fulkerson_maximum_flow.py");

    int max_flow = 0;

    while (bfs()) {
        int min_residual_capacity = find_min_residual_capacity();
        max_flow += min_residual_capacity;
        update_residual_graph(min_residual_capacity);
    }

    std::cout << "Maximum flow: " << max_flow << std::endl;
}

void FordFulkersonMaximumFlow::ford_fulkerson(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file\n";
        return;
    }

    std::ifstream in(filename);
    int n, m, start_vertex, end_vertex;
    in >> n >> m >> start_vertex >> end_vertex;
    std::vector<std::vector<int>> graph(n, std::vector<int>(n));
    for (int i = 0; i < m; i++) {
        int u, v, w;
        in >> u >> v >> w;
        graph[u][v] = w;
    }
    in.close();

    FordFulkersonMaximumFlow ff(graph, start_vertex, end_vertex);
    ff.ford_fulkerson();
}