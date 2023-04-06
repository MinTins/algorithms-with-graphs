#include "a_star_shortest_path.h"

AStarShortestPath::AStarShortestPath(const std::vector<std::vector<std::pair<int, double>>>& graph, int start_vertex)
    : m_graph(graph), m_visited(graph.size()), m_distances(graph.size(), INFINITY), m_parents(graph.size()), m_start_vertex(start_vertex)
{
}

double AStarShortestPath::heuristic(int from, int to)
{
    // Euclidean distance
    double x1 = from / 10.0;
    double y1 = from % 10;
    double x2 = to / 10.0;
    double y2 = to % 10;
    return std::sqrt(std::pow(x1 - x2, 2) + std::pow(y1 - y2, 2));
}

void AStarShortestPath::a_star()
{
    std::ofstream out("a_star_shortest_path/graph.txt");
    out << m_graph.size() << " " << m_graph[0].size() << " " << m_start_vertex << std::endl;
    for (int i = 0; i < m_graph.size(); i++) {
        for (int j = 0; j < m_graph[i].size(); j++) {
            int neighbor = m_graph[i][j].first;
            double weight = m_graph[i][j].second;
            out << i << " " << neighbor << " " << weight << std::endl;
        }
    }
    out.close();
    system("cd a_star_shortest_path & python a_star_shortest_path.py");

    std::priority_queue<std::pair<double, int>, std::vector<std::pair<double, int>>, std::greater<std::pair<double, int>>> pq;
    m_distances[m_start_vertex] = 0;
    pq.push({ 0, m_start_vertex });

    while (!pq.empty()) {
        int current_vertex = pq.top().second;
        pq.pop();

        if (m_visited[current_vertex]) {
            continue;
        }
        m_visited[current_vertex] = true;

        std::cout << "Visited vertex: " << current_vertex << std::endl;

        for (int i = 0; i < m_graph[current_vertex].size(); i++) {
            int neighbor = m_graph[current_vertex][i].first;
            double weight = m_graph[current_vertex][i].second;
            double distance = m_distances[current_vertex] + weight + heuristic(neighbor, m_start_vertex) - heuristic(current_vertex, m_start_vertex);
            if (distance < m_distances[neighbor]) {
                m_distances[neighbor] = distance;
                m_parents[neighbor] = current_vertex;
                pq.push({ distance, neighbor });
            }
        }
    }

    std::cout << "Shortest path:\n";
    for (int i = 0; i < m_graph.size(); i++) {
        if (m_distances[i] == INFINITY) {
            std::cout << "No path to vertex " << i << std::endl;
        }
        else {
            std::cout << "Distance to vertex " << i << ": " << m_distances[i] << std::endl;
            std::cout << "Path: ";
            std::vector<int> path;
            int current_vertex = i;
            while (current_vertex != m_start_vertex) {
                path.push_back(current_vertex);
                current_vertex = m_parents[current_vertex];
            }
            path.push_back(m_start_vertex);
            for (int j = path.size() - 1; j >= 0; j--) {
                std::cout << path[j] << " ";
            }
            std::cout << std::endl;
        }
    }
    system("cd a_star_shortest_path & result.gif");
}

void AStarShortestPath::a_star(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file\n";
        return;
    }

    std::ifstream in(filename);
    int n, start_vertex;
    in >> n >> start_vertex;
    std::vector<std::vector<std::pair<int, double>>> graph(n);
    int from, to;
    double weight;
    while (in >> from >> to >> weight) {
        graph[from].push_back({ to, weight });
    }
    in.close();

    AStarShortestPath a_star(graph, start_vertex);
    a_star.a_star();
}