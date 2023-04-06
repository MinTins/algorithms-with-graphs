
#include <iostream>
#include <string>
#include <vector>


// import methods
#include "breadth_first_search/breadth_first_search.h"
#include "depth_first_search/depth_first_search.h"
#include "prim_minimum_spanning_tree/prim_minimum_spanning_tree.h"


int main() {
    BreadthFirstSearch bfs;
    DepthFirstSearch dfs;
    PrimMinimumSpanningTree prim;


    std::string input;
    int choice = 0;
    while (true) {
        std::cout << "\n--Choose a graph algorithm to test:" << std::endl;
        std::cout << "---1. Breadth-First Search" << std::endl;
        std::cout << "---2. Depth-First Search" << std::endl;
        std::cout << "---3. Prim's Minimum Spanning Tree" << std::endl;
        std::cout << "---4. Dijkstra's Shortest Path" << std::endl;
        std::cout << "---5. A* Shortest Path" << std::endl;
        std::cout << "---6. Ford-Fulkerson Maximum Flow" << std::endl;
        std::cout << "---7. Bidirectional Dijkstra Social Network" << std::endl;
        std::cout << "---8. Bidirectional A* Transport Network" << std::endl;
        std::cout << "--Enter 'q' to quit." << std::endl;
        std::getline(std::cin, input);

        if (input == "q") {
            break;
        }

        try {
            choice = std::stoi(input);
        }
        catch (std::invalid_argument) {
            std::cout << "Invalid input. Please enter a number or 'q'." << std::endl;
            continue;
        }

        if (choice < 1 || choice > 8) {
            std::cout << "Invalid choice. Please enter a number between 1 and 8, or 'q'." << std::endl;
            continue;
        }

        std::cout << "Choose a test method:" << std::endl;
        std::cout << "1. Use test data provided in the code" << std::endl;
        std::cout << "2. Use test data from a file" << std::endl;
        std::getline(std::cin, input);

        if (input == "1") {
            switch (choice) {
            case 1: {
                // Test Breadth-First Search
                BreadthFirstSearch bfs({ {1, 2, 3}, {0, 2}, {0, 1, 3}, {0, 2} }, 0);
                bfs.bfs();
                break;
            }
            case 2: {
                // Test Depth-First Search
                DepthFirstSearch dfs({ {1, 2, 3}, {0, 2}, {0, 1, 3}, {0, 2} }, 0);
                dfs.dfs();
                break;
            }
            case 3:{
                // Test Prim's Minimum Spanning Tree
                PrimMinimumSpanningTree prim({ {{1, 2}, {3, 6}}, {{0, 2}, {2, 3}, {3, 8}, {4, 5}}, {{1, 3}, {4, 7}}, {{0, 6}, {1, 8}, {4, 9}}, {{1, 5}, {2, 7}, {3, 9}} }, 0);
                prim.prim();
                break;
            }
            case 4:
                // Test Dijkstra's Shortest Path
                // testDijkstra("dijkstra_shortest_path/test_dijkstra_data.txt");
                break;
            case 5:
                // Test A* Shortest Path
                // testAStar("a_star_shortest_path/test_a_star_data.txt");
                break;
            case 6:
                // Test Ford-Fulkerson Maximum Flow
                // testFordFulkerson("ford_fulkerson_maximum_flow/test_ford_fulkerson_data.txt");
                break;
            case 7:
                // Test Bidirectional Dijkstra Social Network
                // testBidirectionalDijkstraSocialNetwork("bidirectional_dijkstra_social_network/test_bidirectional_dijkstra_social_network_data.txt");
                break;
            case 8:
                // Test Bidirectional A* Transport Network
                // testBidirectionalAStarTransportNetwork("bidirectional_a_star_transport_network/test_bidirectional_a_star_transport_network_data.txt");
                break;
            }
        }
        else if (input == "2") {
            std::cout << "Enter the filename: ";
            std::getline(std::cin, input);

            switch (choice) {
            case 1:
                // Test Breadth-First Search
                bfs.bfs(input);
                break;
            case 2:
                // Test Depth-First Search
                dfs.dfs(input);
                break;
            case 3:
                // Test Prim's Minimum Spanning Tree
                prim.prim(input);
                break;
            case 4:
                // Test Dijkstra's Shortest Path
                // testDijkstra(input);
                break;
            case 5:
                // Test A* Shortest Path
                // testAStar(input);
                break;
            case 6:
                // Test Ford-Fulkerson Maximum Flow
                // testFordFulkerson(input);
                break;
            case 7:
                // Test Bidirectional Dijkstra Social Network
                // testBidirectionalDijkstraSocialNetwork(input);
                break;
            case 8:
                // Test Bidirectional A* Transport Network
                // testBidirectionalAStarTransportNetwork(input);
                break;
            }
        }
        else {
            std::cout << "Invalid choice. Please enter '1' or '2'." << std::endl;
        }
    }

    return 0;
}
