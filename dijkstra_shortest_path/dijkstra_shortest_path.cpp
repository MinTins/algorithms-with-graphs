#include "dijkstra_shortest_path.h"

DijkstraShortestPath::DijkstraShortestPath(const std::vector<std::vector<std::pair<int, int>>>& graph, int start_vertex)
    : m_graph(graph), m_distance(graph.size(), std::numeric_limits<int>::max()), m_visited(graph.size()), m_start_vertex(start_vertex)
{
}

void DijkstraShortestPath::shortest_path()
{
    std::ofstream out("dijkstra_shortest_path/graph.txt");
    out << m_graph.size() << " " << m_graph[0].size() << " " << m_start_vertex << std::endl;
    for (int i = 0; i < m_graph.size(); i++) {
        for (int j = 0; j < m_graph[i].size(); j++) {
            out << i << " " << m_graph[i][j].first << " " << m_graph[i][j].second << std::endl;
        }
    }
    out.close();
    system("cd dijkstra_shortest_path & python dijkstra_shortest_path.py");

    m_distance[m_start_vertex] = 0;
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
    pq.push(std::make_pair(0, m_start_vertex));

    std::cout << "Shortest distances from vertex " << m_start_vertex << ":\n";

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

            if (m_distance[current_vertex] + weight < m_distance[neighbor]) {
                m_distance[neighbor] = m_distance[current_vertex] + weight;

                std::cout << "Vertex -" << neighbor << "- | weight of path: [" << m_distance[neighbor] << "]\n";
                pq.push(std::make_pair(m_distance[neighbor], neighbor));
            }
        }
    }
    system("cd dijkstra_shortest_path & result.gif");
}

void DijkstraShortestPath::shortest_path(const std::string& filename)
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

    DijkstraShortestPath dsp(graph, start_vertex);
    dsp.shortest_path();
}   