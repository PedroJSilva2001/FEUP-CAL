#include <gtest/gtest.h>

#include <sstream>
#include <random>
#include "Graph.h"
#include "TestAux.h"

// Complete the functions on the Graph.h file

/// TESTS ///

TEST(TP8_Ex1, testFordFulkerson) {
    Graph<int> graph = createTestFlowGraph();
    graph.fordFulkerson(1, 6);

    std::stringstream ss;
    for(auto v : graph.getVertexSet()) {
        ss << v->getInfo() << "-> (";
        for (auto e : v->getAdj())
            ss << (e->getDest())->getInfo() << "[Flow: " << e->getFlow() << "] ";
        ss << ") || ";
    }

    std::cout << ss.str() << std::endl << std::endl;

    EXPECT_EQ("1-> (2[Flow: 3] 3[Flow: 2] ) || 2-> (5[Flow: 1] 4[Flow: 2] 3[Flow: 0] ) || 3-> (5[Flow: 2] ) || 4-> (6[Flow: 2] ) || 5-> (6[Flow: 3] ) || 6-> () || ", ss.str());
}
