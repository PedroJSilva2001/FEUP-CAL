#include "Graph.h"
#include "TestAux.h"

// Complete the functions on the Graph.h file

/// TESTS ///

TEST(TP6_Ex2, test_dijkstra) {
    Graph<int> myGraph = CreateTestGraph();

    myGraph.dijkstraShortestPath(3);
    checkAllPaths(myGraph, "1<-3|2<-1|3<-|4<-2|5<-4|6<-3|7<-5|");

    myGraph.dijkstraShortestPath(1);
    checkAllPaths(myGraph, "1<-|2<-1|3<-4|4<-2|5<-4|6<-4|7<-5|");
    checkSinglePath(myGraph.getPath(1, 7), "1 2 4 5 7 ");

    myGraph.dijkstraShortestPath(5);
    checkSinglePath(myGraph.getPath(5, 6), "5 7 6 ");

    myGraph.dijkstraShortestPath(7);
    checkSinglePath(myGraph.getPath(7, 1), "7 6 4 3 1 ");
}


TEST(TP6_Ex2, test_performance_dijkstra) {
    //TODO: Change these const parameters as needed
    const int MIN_SIZE = 10;
    const int MAX_SIZE = 30; //Try with 100
    const int STEP_SIZE = 10;
    for (int n = MIN_SIZE; n <= MAX_SIZE; n += STEP_SIZE) {
       Graph< std::pair<int,int> > g;
       std::cout << "Dijkstra generating grid " << n << " x " << n << " ..." << std::endl;
       generateRandomGridGraph(n, g);
       std::cout << "Dijkstra processing grid " << n << " x " << n << " ..." << std::endl;
       auto start = std::chrono::high_resolution_clock::now();
       for (int i = 0; i < n; i++)
           for (int j = 0; j < n; j++)
               g.dijkstraShortestPath(std::make_pair(i,j));
       auto finish = std::chrono::high_resolution_clock::now();
       auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count();
       std::cout << "Dijkstra processing grid " << n << " x " << n << " average time (micro-seconds)=" << (elapsed / (n*n)) << std::endl;
   }
}