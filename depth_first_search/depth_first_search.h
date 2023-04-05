#ifndef DEPTH_FIRST_SEARCH_H
#define DEPTH_FIRST_SEARCH_H

#include <vector>
#include <iostream>
#include <string>

class DepthFirstSearch {
public:
    void dfs(std::vector<std::vector<int>>& graph, int start);
    void test_dfs();
    void test_dfs(const std::string& filename);
};


#endif