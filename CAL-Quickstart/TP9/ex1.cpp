#include <gtest/gtest.h>

#include <iostream>
#include <string>
#include <sstream>
#include "Graph.h"

using namespace std;

TEST(TP9_Ex1, testMinCostFlow1) {
    Graph<string> g;

    g.addVertex("s");
    g.addVertex("x");
    g.addVertex("t");

    g.addEdge("s", "t", 3, 1);
    g.addEdge("s", "x", 2, 2);
    g.addEdge("x", "t", 1, 2);

    double cost = g.minCostFlow("s", "t", INF);

    EXPECT_EQ(cost, 7);

    EXPECT_EQ(g.getFlow("s", "t"), 3);
    EXPECT_EQ(g.getFlow("s", "x"), 1);
    EXPECT_EQ(g.getFlow("x", "t"), 1);
}

TEST(TP9_Ex1, testMinCostFlow2) {
	Graph<string> g;

	g.addVertex("s");
	g.addVertex("a");
	g.addVertex("b");
	g.addVertex("c");
	g.addVertex("d");
	g.addVertex("t");

	g.addEdge("s", "a", 3, 0);
	g.addEdge("s", "b", 2, 0);
	g.addEdge("a", "b", 1, -2);
	g.addEdge("a", "c", 3, 1);
	g.addEdge("a", "d", 4, 2);
	g.addEdge("b", "d", 2, 2);
	g.addEdge("c", "t", 2, 1);
	g.addEdge("d", "t", 3, 1);

	double cost = g.minCostFlow("s", "t", 3);

	EXPECT_EQ(cost, 5);

	EXPECT_EQ(g.getFlow("s", "a"), 3);
	EXPECT_EQ(g.getFlow("s", "b"), 0);
	EXPECT_EQ(g.getFlow("a", "b"), 1);
	EXPECT_EQ(g.getFlow("a", "c"), 2);
	EXPECT_EQ(g.getFlow("a", "d"), 0);
	EXPECT_EQ(g.getFlow("b", "d"), 1);
	EXPECT_EQ(g.getFlow("c", "t"), 2);
	EXPECT_EQ(g.getFlow("d", "t"), 1);
}

TEST(TP9_Ex1, testMinCostFlow3) {
    Graph<string> g;

    g.addVertex("s");
    g.addVertex("a");
    g.addVertex("b");
    g.addVertex("c");
    g.addVertex("d");
    g.addVertex("t");

    g.addEdge("s", "a", 3, 3);
    g.addEdge("s", "b", 3, 0);
    g.addEdge("a", "b", 3, -4);
    g.addEdge("a", "c", 3, 1);
    g.addEdge("a", "d", 3, 2);
    g.addEdge("b", "d", 3, 2);
    g.addEdge("c", "t", 3, 1);
    g.addEdge("d", "t", 3, 1);

    double cost = g.minCostFlow("s", "t", 3);

    EXPECT_EQ(cost, 6);
}
