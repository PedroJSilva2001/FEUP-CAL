/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include <iostream>
template <class T> class Edge;
template <class T> class Graph;
template <class T> class Vertex;


/****************** Provided structures  ********************/

template <class T>
class Vertex {
	T info;                // contents
	std::vector<Edge<T> > adj;  // list of outgoing edges
	bool visited;          // auxiliary field used by dfs and bfs
	bool processing;       // auxiliary field used by isDAG
	int indegree;          // auxiliary field used by topsort

	void addEdge(Vertex<T> *dest, double w);
	bool removeEdgeTo(Vertex<T> *d);
public:
	Vertex(T in);
	friend class Graph<T>;
};

template <class T>
class Edge {
	Vertex<T> * dest;      // destination vertex
	double weight;         // edge weight
public:
	Edge(Vertex<T> *d, double w);
	friend class Graph<T>;
	friend class Vertex<T>;
};

template <class T>
class Graph {
    std::vector<Vertex<T> *> vertexSet;    // vertex set

	void dfsVisit(Vertex<T> *v,  std::vector<T> & res) const;
	Vertex<T> *findVertex(const T &in) const;
	bool dfsIsDAG(Vertex<T> *v) const;
public:
	int getNumVertex() const;
	bool addVertex(const T &in);
	bool removeVertex(const T &in);
	bool addEdge(const T &sourc, const T &dest, double w);
	bool removeEdge(const T &sourc, const T &dest);
    std::vector<T> dfs() const;
    std::vector<T> bfs(const T &source) const;
    std::vector<T> topsort() const;
	int maxNewChildren(const T &source, T &inf) const;
	bool isDAG() const;
};

/****************** Provided constructors and functions ********************/

template <class T>
Vertex<T>::Vertex(T in): info(in) {}

template <class T>
Edge<T>::Edge(Vertex<T> *d, double w): dest(d), weight(w) {}


template <class T>
int Graph<T>::getNumVertex() const {
	return vertexSet.size();
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
template <class T>
Vertex<T> * Graph<T>::findVertex(const T &in) const {
	for (auto v : vertexSet)
		if (v->info == in)
			return v;
	return NULL;
}

/****************** 1a) addVertex ********************/

/*
 *  Adds a vertex with a given content/info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
template <class T>
bool Graph<T>::addVertex(const T &in) {
    if (findVertex(in) != nullptr) {
        return false;
    }
    vertexSet.push_back(new Vertex<T>(in));
    // TODO (4 lines)
    // HINT: use the findVertex function to check if a vertex already exists
    return false;
}

/****************** 1b) addEdge ********************/

/*
 * Adds an edge to a graph (this), given the contents of the source (sourc) and
 * destination (dest) vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w) {
    Vertex<T> *u = findVertex(sourc);
    Vertex<T> *v = findVertex(dest);
    if (u == nullptr || v == nullptr) {
        return false;
    }
    u->addEdge(v, w);
    // TODO (6 lines)
    // HINT: use findVertex to obtain the actual vertices
    // HINT: use the next function to actually add the edge
    return true;
}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
template <class T>
void Vertex<T>::addEdge(Vertex<T> *d, double w) {
    adj.push_back(Edge<T>(d, w));
    // TODO (1 line)
}


/****************** 1c) removeEdge ********************/

/*
 * Removes an edge from a graph (this).
 * The edge is identified by the source (sourc) and destination (dest) contents.
 * Returns true if successful, and false if such edge does not exist.
 */
template <class T>
bool Graph<T>::removeEdge(const T &sourc, const T &dest) {
    Vertex<T> *u = findVertex(sourc);
    Vertex<T> *v = findVertex(dest);
    if (u == nullptr || v == nullptr) {
        return false;
    }
    return u->removeEdgeTo(v);
    // TODO (5 lines)
    // HINT: Use "findVertex" to obtain the actual vertices.
    // HINT: Use the next function to actually remove the edge.
}

/*
 * Auxiliary function to remove an outgoing edge (with a given destination (d))
 * from a vertex (this).
 * Returns true if successful, and false if such edge does not exist.
 */
template <class T>
bool Vertex<T>::removeEdgeTo(Vertex<T> *d) {
    for (unsigned i = 0; i < adj.size(); ++i) {
        if (adj.at(i).dest == d) {
            adj.erase(adj.begin()+i);
            return true;
        }
    }
    // TODO (6 lines)
    // HINT: use an iterator to scan the "adj" vector and then erase the edge.
    return false;
}


/****************** 1d) removeVertex ********************/

/*
 *  Removes a vertex with a given content (in) from a graph (this), and
 *  all outgoing and incoming edges.
 *  Returns true if successful, and false if such vertex does not exist.
 */
template <class T>
bool Graph<T>::removeVertex(const T &in) {
    bool found = false;
    for (unsigned i = 0; i < vertexSet.size(); ++i) {
        if (vertexSet.at(i)->info == in) {
            Vertex<T> *v = vertexSet.at(i);
            vertexSet.erase(vertexSet.begin()+i);
            for (Vertex<T> *u : vertexSet) {
                u->removeEdgeTo(v);
            }
            return true;
        }
    }
    // TODO (10 lines)
    // HINT: use an iterator to scan the "vertexSet" vector and then erase the vertex.
    // HINT: take advantage of "removeEdgeTo" to remove incoming edges.
    return false;
}


/****************** 2a) dfs ********************/

/*
 * Performs a depth-first search (dfs) in a graph (this).
 * Returns a vector with the contents of the vertices by dfs order.
 * Follows the algorithm described in theoretical classes.
 */
template <class T>
std::vector<T> Graph<T>::dfs() const {
    // TODO (7 lines)
    std::vector<T> res;
    for (Vertex<T> *u : vertexSet) {
        u->visited = false;
    }
    for (Vertex<T> *u : vertexSet) {
        if (!u->visited) {
            dfsVisit(u, res);
        }
    }
    return res;
}

/*
 * Auxiliary function that visits a vertex (v) and its adjacent not yet visited, recursively.
 * Updates a parameter with the list of visited node contents.
 */
template <class T>
void Graph<T>::dfsVisit(Vertex<T> *v, std::vector<T> & res) const {
    v->visited = true;
    res.push_back(v->info);
    for (Edge<T> e : v->adj) {
        if (!e.dest->visited) {
            dfsVisit(e.dest, res);
        }
    }

    // TODO (7 lines)
}

/****************** 2b) bfs ********************/

/*
 * Performs a breadth-first search (bfs) in a graph (this), starting
 * from the vertex with the given source contents (source).
 * Returns a vector with the contents of the vertices by dfs order.
 * Follows the algorithm described in theoretical classes.
 */
template <class T>
std::vector<T> Graph<T>::bfs(const T & source) const {
    std::vector<T> res;
    std::queue<Vertex<T> *> q;

    Vertex<T> *s = findVertex(source);

    if (s == nullptr) {
        return res;
    }

    for (Vertex<T> *u : vertexSet) {
        u->visited = false;
    }
    q.push(s);
    s->visited = true;
    while (!q.empty()) {
        Vertex<T> *u = q.front(); //pqp porque é que o pop() não retorna a merda do elemento em c++?
        q.pop();
        res.push_back(u->info);
        for (Edge<T> &e : u->adj) {
            if (!e.dest->visited ) {
                q.push(e.dest);
                e.dest->visited = true;
            }
        }
    }
    return res;

    // TODO (22 lines)
    // HINT: Use the flag "visited" to mark newly discovered vertices .
    // HINT: Use the "queue<>" class to temporarily store the vertices.

}

/****************** 2c) toposort ********************/

/*
 * Performs a topological sorting of the vertices of a graph (this).
 * Returns a vector with the contents of the vertices by topological order.
 * If the graph has cycles, returns an empty vector.
 * Follows the algorithm described in theoretical classes.
 */

template<class T>
std::vector<T> Graph<T>::topsort() const {

    std::vector<T> res;
    std::queue<Vertex<T> *> q;

    for (Vertex<T> *u : vertexSet) {
        u->indegree = 0;
    }

    for (Vertex<T> *u : vertexSet) {
        for (auto &e : u->adj) {
            e.dest->indegree++;
        }
    }
    for (Vertex<T> *u : vertexSet) {
        if (u->indegree == 0) {
            q.push(u);
        }
    }
    while(!q.empty()) {
        Vertex<T> *u = q.front();
        q.pop();
        res.push_back(u->info);
        for(Edge<T> &e : u->adj) {
            e.dest->indegree--;
            if(e.dest->indegree == 0) {
                q.push(e.dest);
            }
        }
    }

    if (res.size() != vertexSet.size()) {
        std::cout << "Graph has no topological order" << std::endl;
        res.clear();
        return res;
    }

    return res;

    // TODO (26 lines)
}

/****************** 3a) maxNewChildren (HOME WORK)  ********************/

/*
 * Performs a breadth-first search in a graph (this), starting
 * from the vertex with the given source contents (source).
 * During the search, determines the vertex that has a maximum number
 * of new children (adjacent not previously visited), and returns the
 * contents of that vertex (inf) and the number of new children (return value).
 */

template <class T>
int Graph<T>::maxNewChildren(const T & source, T &inf) const {

    int globalMax = -1, localMax;
    std::queue<Vertex<T> *> q;

    Vertex<T> *s = findVertex(source);

    if (s == nullptr) {
        return globalMax;
    }

    for (Vertex<T> *u : vertexSet) {
        u->visited = false;
    }
    q.push(s);
    s->visited = true;
    while (!q.empty()) {
        Vertex<T> *u = q.front(); //pqp porque é que o pop() não retorna a merda do elemento em c++?
        q.pop();
        localMax = 0;
        for (Edge<T> &e : u->adj) {
            if (!e.dest->visited ) {
                q.push(e.dest);
                e.dest->visited = true;
                localMax++;
            }
        }
        if (localMax > globalMax) {
            globalMax = localMax;
            inf = u->info;
        }
    }

    return globalMax;
}

/****************** 3b) isDAG   (HOME WORK)  ********************/

/*
 * Performs a depth-first search in a graph (this), to determine if the graph
 * is acyclic (acyclic directed graph or DAG).
 * During the search, a cycle is found if an edge connects to a vertex
 * that is being processed in the the stack of recursive calls (see theoretical classes).
 * Returns true if the graph is acyclic, and false otherwise.
 */

template <class T>
bool Graph<T>::isDAG() const {
    for (Vertex<T> *u : vertexSet) {
        u->processing = false;
        u->visited = false;
    }
    for (Vertex<T> *u : vertexSet) {
        if (!u->visited) {
            if (!dfsIsDAG(u)) {
                return false;
            }
        }
    }

    return true;
}

/**
 * Auxiliary function that visits a vertex (v) and its adjacent not yet visited, recursively.
 * Returns false (not acyclic) if an edge to a vertex in the stack is found.
 */
template <class T>
bool Graph<T>::dfsIsDAG(Vertex<T> *v) const {
    v->visited = true;
    v->processing = true;
    for (Edge<T> e : v->adj) {
        if (e.dest->processing) {
            return false;
        }
        if (!e.dest->visited) {
            if (!dfsIsDAG(e.dest)) {
                return false;
            }
        }
    }
    v->processing = false;

    return true;
}

#endif /* GRAPH_H_ */
