#include "Graph.h"
#include "TestAux.h"

// Complete the functions on the Graph.h file

/// TESTS ///

TEST(TP6_Ex3, test_bellmanFord) {
    Graph<int> myGraph = CreateTestGraph();

    myGraph.bellmanFordShortestPath(3);
    checkAllPaths(myGraph, "1<-3|2<-1|3<-|4<-2|5<-4|6<-3|7<-5|");

    myGraph.bellmanFordShortestPath(1);
    checkSinglePath(myGraph.getPath(1, 7), "1 2 4 5 7 ");

    myGraph.bellmanFordShortestPath(5);
    checkSinglePath(myGraph.getPath(5, 6), "5 7 6 ");

    myGraph.bellmanFordShortestPath(7);
    checkSinglePath(myGraph.getPath(7, 1), "7 6 4 3 1 ");
}