#include "Graph.h"
#include "Person.h"

// Complete the functions on the Graph.h file

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP5_Ex3a, test_maxNewChildren) {
    Graph<Person> net1;
    Person p1("Ana",19);
    Person p2("Carlos",33);
    Person p3("Filipe", 20);
    Person p4("Ines", 18);
    Person p5("Maria", 24);
    Person p6("Rui",21);
    Person p7("Vasco",28);
    net1.addVertex(p1); net1.addVertex(p2);
    net1.addVertex(p3); net1.addVertex(p4);
    net1.addVertex(p5); net1.addVertex(p6); net1.addVertex(p7);
    net1.addEdge(p1,p2,0);
    net1.addEdge(p1,p3,0);
    net1.addEdge(p2,p5,0);
    net1.addEdge(p3,p4,0);
    net1.addEdge(p5,p6,0);
    net1.addEdge(p5,p1,0);
    net1.addEdge(p3,p6,0);
    net1.addEdge(p3,p7,0);
    net1.addEdge(p3,p2,0);
    Person pt;
    EXPECT_EQ(3, net1.maxNewChildren(Person("Ana",19), pt));
    EXPECT_EQ("Filipe", pt.getName());
}

TEST(TP5_Ex3b, test_isDAG) {
    Graph<int> myGraph;

    myGraph.addVertex(0);myGraph.addVertex(1); myGraph.addVertex(2);
    myGraph.addVertex(3); myGraph.addVertex(4); myGraph.addVertex(5);
    myGraph.addEdge(1, 2, 0);
    myGraph.addEdge(2, 5, 0);
    myGraph.addEdge(5, 4, 0);
    myGraph.addEdge(4, 1, 0);
    myGraph.addEdge(5, 1, 0);
    myGraph.addEdge(2, 3, 0);
    myGraph.addEdge(3, 1, 0);
    myGraph.addEdge(0, 4, 0);

    EXPECT_EQ(false, myGraph.isDAG());

    myGraph.removeEdge(4, 1);
    myGraph.removeEdge(5, 1);
    myGraph.removeEdge(2, 3);

    EXPECT_EQ(true, myGraph.isDAG());

    myGraph.addEdge(1, 4, 0);

    EXPECT_EQ(true, myGraph.isDAG());
}