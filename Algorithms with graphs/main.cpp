#include <iostream>
#include "GraphMethods.h"

int main() {
    GraphMethods graphMethods;
    int methodChoice;
    int dataChoice;

    std::cout << "������� ����� (1-8):" << std::endl;
    std::cout << "1. ����� ����� - ����� � ������" << std::endl;
    std::cout << "2. ����� ����� - ����� � �������" << std::endl;
    std::cout << "3. �������� ���� �������� ���������� ���������� ������" << std::endl;
    std::cout << "4. �������� �������� ������ ����������� ������" << std::endl;
    std::cout << "5. �������� �* ������ ����������� ������" << std::endl;
    std::cout << "6. �������� �����-���������� ������ ������������� ������" << std::endl;
    std::cout << "7. �������������� �������� �������� ��� ������ ����������� ����� � ��������� �����" << std::endl;
    std::cout << "8. �������������� �������� �* ������ ������������ �����" << std::endl;

    std::cin >> methodChoice;

    std::cout << "������� ��� (1-2):" << std::endl;
    std::cout << "1. ���������� ���" << std::endl;
    std::cout << "2. ��� � �����" << std::endl;

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