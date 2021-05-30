#include "Graph.h"
#include "TestAux.h"

// Complete the functions on the Graph.h file

/// TESTS ///

TEST(TP6_Ex1, test_unweightedShortestPath) {
    Graph<int> myGraph = CreateTestGraph();

    myGraph.unweightedShortestPath(3);
    checkAllPaths(myGraph, "1<-3|2<-1|3<-|4<-1|5<-2|6<-3|7<-4|");
    checkSinglePath(myGraph.getPath(3, 7), "3 1 4 7 ");

    myGraph.unweightedShortestPath(5);
    checkSinglePath(myGraph.getPath(5, 6), "5 7 6 ");
}