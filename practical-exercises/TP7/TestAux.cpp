#include "Graph.h"
#include "TestAux.h"

/**
 * Auxiliary functions to tests...
 *
 */
Graph<int> CreateTestGraph() {
    Graph<int> myGraph;

    for(int i = 1; i < 8; i++)
        myGraph.addVertex(i);

    myGraph.addBidirectionalEdge(1, 2, 2);
    myGraph.addBidirectionalEdge(1, 4, 7);
    myGraph.addBidirectionalEdge(2, 4, 3);
    myGraph.addBidirectionalEdge(2, 5, 5);
    myGraph.addBidirectionalEdge(3, 1, 2);
    myGraph.addBidirectionalEdge(3, 6, 5);
    myGraph.addBidirectionalEdge(4, 3, 1);
    myGraph.addBidirectionalEdge(4, 5, 1);
    myGraph.addBidirectionalEdge(4, 7, 4);
    myGraph.addBidirectionalEdge(5, 7, 2);
    myGraph.addBidirectionalEdge(6, 4, 3);
    myGraph.addBidirectionalEdge(7, 6, 4);

    return myGraph;
}


void generateRandomGridGraph(int n, Graph<std::pair<int,int>> & g) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(1, n);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            g.addVertex(std::make_pair(i,j));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            if (i < n-1)
                g.addBidirectionalEdge(std::make_pair(i,j), std::make_pair(i+1,j), dis(gen));
            if (j < n-1)
                g.addBidirectionalEdge(std::make_pair(i,j), std::make_pair(i,j+1), dis(gen));
        }
}

bool isSpanningTree(const std::vector<Vertex<int>*> &res){
    std::map<int, std::set<int> > adj;
    for(const Vertex<int> *v: res) {
        adj[v->getInfo()];
        const Vertex<int> *u = v->getPath();
        if (u != nullptr) {
            adj[u->getInfo()].emplace(v->getInfo());
            adj[v->getInfo()].emplace(u->getInfo());
        }
    }

    std::queue<int> q;
    std::set<int> visited;
    q.push(res.at(0)->getInfo());
    while(!q.empty()){
        int u = q.front(); q.pop();
        if(visited.count(u)) continue;
        visited.emplace(u);
        for(const int &v: adj.at(u)){
            q.emplace(v);
        }
    }

    for(const Vertex<int> *v: res)
        if(!visited.count(v->getInfo())) return false;
    return true;
}

double spanningTreeCost(const std::vector<Vertex<int>*> &res){
    double ret = 0;
    for(const Vertex<int> *v: res){
        const Vertex<int> *u = v->getPath();
        if(u == nullptr) continue;
        for(const Edge<int> *e: u->adj){
            if(e->getDest()->getInfo() == v->getInfo()){
                ret += e->getWeight();
                break;
            }
        }
    }
    return ret;
}
