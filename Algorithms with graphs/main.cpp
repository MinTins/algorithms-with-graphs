#include <iostream>
#include "GraphMethods.h"

int main() {
    GraphMethods graphMethods;
    int methodChoice;
    int dataChoice;

    std::cout << "Виберіть метод (1-8):" << std::endl;
    std::cout << "1. Обхід графа - пошук в ширину" << std::endl;
    std::cout << "2. Обхід графа - пошук в глибину" << std::endl;
    std::cout << "3. Алгоритм Пріма побудови мінімального кістякового дерева" << std::endl;
    std::cout << "4. Алгоритм Дейкстри пошуку найкоротших шляхів" << std::endl;
    std::cout << "5. Алгоритм А* пошуку найкоротших шляхів" << std::endl;
    std::cout << "6. Алгоритм Форда-Фалкерсона пошуку максимального потоку" << std::endl;
    std::cout << "7. Двонаправлений алгоритм Дейкстри для пошуку потенційних друзів в соціальній мережі" << std::endl;
    std::cout << "8. Двонаправлений алгоритм А* пошуку оптимального шляху" << std::endl;

    std::cin >> methodChoice;

    std::cout << "Виберіть дані (1-2):" << std::endl;
    std::cout << "1. Заготовлені дані" << std::endl;
    std::cout << "2. Дані з файлу" << std::endl;

    std::cin >> dataChoice;

    if (dataChoice == 2) {
        graphMethods.importDataFromFile();
    }

    switch (methodChoice) {
    case 1:
        graphMethods.breadthFirstSearch();
        break;
    case 2:
        graphMethods.depthFirstSearch();
        break;
    case 3:
        graphMethods.primAlgorithm();
        break;
    case 4:
        graphMethods.dijkstraAlgorithm();
        break;
    case 5:
        graphMethods.aStarAlgorithm();
        break;
    case 6:
        graphMethods.fordFulkersonAlgorithm();
        break;
    case 7:
        graphMethods.bidirectionalDijkstraAlgorithm();
        break;
    case 8:
        graphMethods.bidirectionalAStarAlgorithm();
        break;
    default:
        break;
    }

    return 0;
}