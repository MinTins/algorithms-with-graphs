#ifndef PRIM_MINIMUM_SPANNING_TREE_H
#define PRIM_MINIMUM_SPANNING_TREE_H

#include <vector>
#include <iostream>
#include <string>

class PrimMinimumSpanningTree {
public:
    PrimMinimumSpanningTree() = default;
    ~PrimMinimumSpanningTree() = default;

    void findMST(std::vector<std::vector<int>>& graph, int startNode);
    void testPrim();
    void findMSTFromFile(const std::string& filename);

private:
    int findMinKey(const std::vector<int>& key, const std::vector<bool>& mstSet);
    void printMST(const std::vector<int>& parent, const std::vector<std::vector<int>>& graph);

};

#endif // PRIM_MINIMUM_SPANNING_TREE_H