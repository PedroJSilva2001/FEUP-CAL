#include "Graph.h"
#include "Person.h"

// Complete the functions on the Graph.h file

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP5_Ex1a, test_addVertex) {
    Graph<Person> net1;
    Person p1("Ana",19);
    Person p2("Carlos",33);
    Person p3("Filipe", 20);
    Person p4("Ines", 18);
    net1.addVertex(p1); net1.addVertex(p2);
    net1.addVertex(p3); net1.addVertex(p4);
    EXPECT_EQ(false, net1.addVertex(p2));
    EXPECT_EQ(4, net1.getNumVertex());
}

TEST(TP5_Ex1b, test_addEdge) {
    Graph<Person> net1;
    Person p1("Ana",19);
    Person p2("Carlos",33);
    Person p3("Filipe", 20);
    Person p4("Ines", 18);
    Person p5("Maria", 24);
    net1.addVertex(p1); net1.addVertex(p2);
    net1.addVertex(p3); net1.addVertex(p4);
    EXPECT_EQ(true, net1.addEdge(p1,p2,0));
    EXPECT_EQ(true, net1.addEdge(p1,p3,0));
    EXPECT_EQ(true, net1.addEdge(p1,p4,0));
    EXPECT_EQ(false, net1.addEdge(p2,p5,0));
}

TEST(TP5_Ex1c, test_removeEdge) {
    Graph<Person> net1;
    Person p1("Ana",19);
    Person p2("Carlos",33);
    Person p3("Filipe", 20);
    Person p4("Ines", 18);
    Person p5("Maria", 24);
    net1.addVertex(p1); net1.addVertex(p2);
    net1.addVertex(p3); net1.addVertex(p4);
    EXPECT_EQ(true, net1.addEdge(p1,p2,0));
    EXPECT_EQ(true, net1.addEdge(p1,p3,0));
    EXPECT_EQ(true, net1.addEdge(p1,p4,0));
    EXPECT_EQ(true, net1.addEdge(p2,p4,0));
    EXPECT_EQ(true, net1.removeEdge(p1,p3));
    EXPECT_EQ(false, net1.removeEdge(p1,p5));
    EXPECT_EQ(false, net1.removeEdge(p2,p3));
}

TEST(TP5_Ex1d, test_removeVertex) {
    Graph<Person> net1;
    Person p1("Ana",19);
    Person p2("Carlos",33);
    Person p3("Filipe", 20);
    Person p4("Ines", 18);
    net1.addVertex(p1); net1.addVertex(p2);
    net1.addVertex(p3); net1.addVertex(p4);
    EXPECT_EQ(true, net1.removeVertex(p2));
    EXPECT_EQ(false, net1.removeVertex(p2));
    EXPECT_EQ(3, net1.getNumVertex());
}