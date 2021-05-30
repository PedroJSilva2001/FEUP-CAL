#ifndef TEST_AUX_H_
#define TEST_AUX_H_

#include <gtest/gtest.h>

#include <sstream>
#include <random>
#include <time.h>
#include <chrono>
#include "Graph.h"

/**
 * Auxiliary functions to tests...
 *
 */
Graph<int> CreateTestGraph();

template <typename T1, typename T2>
std::basic_ostream<char>& operator<<(std::basic_ostream<char> & strm, const std::pair<T1, T2>& kvPair)
{
    strm << "(" << kvPair.first << ", " << kvPair.second << ")";
    return strm;
}


void generateRandomGridGraph(int n, Graph<std::pair<int,int>> & g);

template <class T>
void checkAllPaths(Graph<T> &g, std::string expected) {
    std::stringstream ss;
    std::vector<Vertex<T>* > vs = g.getVertexSet();
    for(unsigned int i = 0; i < vs.size(); i++) {
        ss << vs[i]->getInfo() << "<-";
        if ( vs[i]->getPath() != NULL )
            ss << vs[i]->getPath()->getInfo();
        ss << "|";
    }
    EXPECT_EQ(expected, ss.str());
}

template <class T>
void checkSinglePath(std::vector<T> path, std::string expected) {
    std::stringstream ss;
    for(unsigned int i = 0; i < path.size(); i++)
        ss << path[i] << " ";
    EXPECT_EQ(expected, ss.str());
}

#endif /* TEST_AUX_H_ */
