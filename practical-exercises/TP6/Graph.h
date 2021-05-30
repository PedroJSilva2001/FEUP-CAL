/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include <list>
#include <limits>
#include <cmath>
#include "MutablePriorityQueue.h"
#include <algorithm>
#include <iostream>


template <class T> class Edge;
template <class T> class Graph;
template <class T> class Vertex;

#define INF std::numeric_limits<double>::max()

/************************* Vertex  **************************/

template <class T>
class Vertex {
    T info;						// content of the vertex
    std::vector<Edge<T> > adj;		// outgoing edges

    double dist = 0;
    Vertex<T> *path = NULL;
    int queueIndex = 0; 		// required by MutablePriorityQueue

    bool visited = false;		// auxiliary field
    bool processing = false;	// auxiliary field

    void addEdge(Vertex<T> *dest, double w);

public:
    Vertex(T in);
    T getInfo() const;
    double getDist() const;
    Vertex *getPath() const;

    bool operator<(Vertex<T> & vertex) const; // // required by MutablePriorityQueue
    friend class Graph<T>;
    friend class MutablePriorityQueue<Vertex<T>>;
};


template <class T>
Vertex<T>::Vertex(T in): info(in) {}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
template <class T>
void Vertex<T>::addEdge(Vertex<T> *d, double w) {
    adj.push_back(Edge<T>(d, w));
}

template <class T>
bool Vertex<T>::operator<(Vertex<T> & vertex) const {
    return this->dist < vertex.dist;
}

template <class T>
T Vertex<T>::getInfo() const {
    return this->info;
}

template <class T>
double Vertex<T>::getDist() const {
    return this->dist;
}

template <class T>
Vertex<T> *Vertex<T>::getPath() const {
    return this->path;
}

/********************** Edge  ****************************/

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
Edge<T>::Edge(Vertex<T> *d, double w): dest(d), weight(w) {}


/*************************** Graph  **************************/

template <class T>
void deleteMatrix(T **m, int n) {
    if (m != nullptr) {
        for (int i = 0; i < n; i++) {
            if (m[i] != nullptr) {
                delete[] m[i];
            }
        }
        delete [] m;
    }
}

template <class T>
class Graph {
    std::vector<Vertex<T> *> vertexSet;    // vertex set
    double **dist;
    int **path;

public:
    Vertex<T> *findVertex(const T &in) const;
    bool addVertex(const T &in);
    bool addEdge(const T &sourc, const T &dest, double w);
    int getNumVertex() const;
    std::vector<Vertex<T> *> getVertexSet() const;

    // Fp06 - single source
    void unweightedShortestPath(const T &s);    //TODO...
    void dijkstraShortestPath(const T &s);      //TODO...
    void bellmanFordShortestPath(const T &s);   //TODO...
    std::vector<T> getPath(const T &origin, const T &dest) const;   //TODO...

    // Fp06 - all pairs
    void floydWarshallShortestPath();   //TODO...
    std::vector<T> getfloydWarshallPath(const T &origin, const T &dest) const;   //TODO...

    Vertex<T> * initSingleSource(const T &origin);
    inline bool relax(Vertex<T> *u, Vertex<T> *v, double weight);
    //void deleteMatrix(T **m, int n);
    unsigned findVertexIdx(const T &in) const;
    void deleteMatrices() {
        deleteMatrix(dist, vertexSet.size());
        deleteMatrix(path, vertexSet.size());
    }

};

template <class T>
int Graph<T>::getNumVertex() const {
    return vertexSet.size();
}

template <class T>
std::vector<Vertex<T> *> Graph<T>::getVertexSet() const {
    return vertexSet;
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

/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
template <class T>
bool Graph<T>::addVertex(const T &in) {
    if ( findVertex(in) != NULL)
        return false;
    vertexSet.push_back(new Vertex<T>(in));
    return true;
}

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == NULL || v2 == NULL)
        return false;
    v1->addEdge(v2,w);
    return true;
}


/**************** Single Source Shortest Path algorithms ************/

template<class T>
void Graph<T>::unweightedShortestPath(const T &orig) {
    //Vertex<T> *s = findVertex(orig);
    std::queue<Vertex<T> *> q;
    Vertex<T> *s = initSingleSource(orig);

    if (s == nullptr) {
        return;
    }
    /*for (Vertex<T> *u : vertexSet) {
        u->dist = INF;
    }*/
    q.push(s);
    //s->dist = 0;
    while (!q.empty()) {
        Vertex<T> *u = q.front();
        q.pop();
        for (Edge<T> e : u->adj) {
            /*if (e.dest->dist > u->dist + 1) {
                e.dest->dist = u->dist + 1;
                e.dest->path = u;
                q.push(e.dest);
            }*/
            if (relax(u, e.dest, 1)) {
                q.push(e.dest);
            }
        }
    }
    // TODO implement this
}


template<class T>
void Graph<T>::dijkstraShortestPath(const T &origin) {
    MutablePriorityQueue<Vertex<T>> q;
    Vertex<T> *s = initSingleSource(origin);
    if (s == nullptr) {
        return;
    }
    for (Vertex<T> *u : vertexSet) {
        q.insert(u);
    }
    while (!q.empty()) {
        Vertex<T> *u = q.extractMin();
        for (Edge<T> e : u->adj) {
            if (relax(u, e.dest, e.weight)) {
                q.decreaseKey(e.dest);
                //q.insert(e.dest);
            }
        }
    }
    // TODO implement this
}


template<class T>
void Graph<T>::bellmanFordShortestPath(const T &orig) {
    initSingleSource(orig);
    for (unsigned i = 1; i < vertexSet.size(); i++) {
        for (Vertex<T> *u : vertexSet) {
            for (Edge<T> e : u->adj) {
                relax(u, e.dest, e.weight);
            }
        }
    }
    for (Vertex<T> *u : vertexSet) {
        for (Edge<T> e : u->adj) {
            if (relax(u, e.dest, e.weight)) {
                std::cout << "Negative cycle" << std::endl;
            }
        }
    }

    // TODO implement this
}


template<class T>
std::vector<T> Graph<T>::getPath(const T &origin, const T &dest) const {
    Vertex<T> *u = findVertex(origin);
    Vertex<T> *v = findVertex(dest);
    std::vector<T> res;

    if (u == nullptr || v == nullptr || v->dist == INF) {
        return res;
    }
    while (v != nullptr) {
        res.push_back(v->info);
        v = v->path;
    }
    std::reverse(res.begin(), res.end());  //estúpido
    // TODO implement this
    return res;
}



/**************** All Pairs Shortest Path  ***************/

template<class T>
void Graph<T>::floydWarshallShortestPath() {
    unsigned n = vertexSet.size();
    dist = new double *[n];
    path = new int *[n];

    for (unsigned i = 0; i < n; i++) {
        dist[i] = new double[n];
        path[i] = new int [n];
        for (unsigned j = 0; j < n; j++) {
            dist[i][j] = i == j? 0 : INF;
            path[i][j] = -1;
        }
        for (Edge<T> e : vertexSet[i]->adj) {
            int j = findVertexIdx(e.dest->info);
            dist[i][j] = e.weight;
            path[i][j] = i;
        }
    }

    for(unsigned k = 0; k < n; k++) {
        for (unsigned i = 0; i < n; i++) {
            for (unsigned j = 0; j < n; j++) {
                if (dist[i][k] == INF || dist[k][j] == INF) {
                    continue;  //vai te foder overflow, por tua causa falhei aquele ex do hackerrank
                }
                double newDist = dist[i][k] + dist[k][j];
                if (newDist < dist[i][j]) {
                    dist[i][j] = newDist;
                    path[i][j] = path[k][j];
                }
            }
        }
    }
    // TODO implement this
}

template<class T>
std::vector<T> Graph<T>::getfloydWarshallPath(const T &orig, const T &dest) const {
    std::vector<T> res;
    int i = findVertexIdx(orig);
    int j = findVertexIdx(dest);
    if (i == -1 || j == -1 || dist[i][j] == INF) { // missing or disconnected
        return res;
    }
    for ( ; j != -1; j = path[i][j]) {
        res.push_back(vertexSet[j]->info);
    }
    reverse(res.begin(), res.end());
    // TODO implement this
    return res;
}

template<class T>
Vertex<T> * Graph<T>::initSingleSource(const T &origin) {
    for(auto v : vertexSet) {
        v->dist = INF;
        v->path = nullptr;
    }
    auto s = findVertex(origin);
    s->dist = 0;
    return s;
}

template<class T>
inline bool Graph<T>::relax(Vertex<T> *u, Vertex<T> *v, double weight) {
    if (u->dist + weight < v->dist) {
        v->dist = u->dist + weight;
        v->path = u;
        return true;
    }
    return false;
}
/*
template <class T>
void Graph<T>::deleteMatrix(T **m, int n) {
    if (m != nullptr) {
        for (int i = 0; i < n; i++) {
            if (m[i] != nullptr) {
                delete[] m[i];
            }
        }
        delete [] m;
    }
}*/

template <class T>
unsigned Graph<T>::findVertexIdx(const T &in) const {
    for (unsigned i = 0; i < vertexSet.size(); i++)
        if (vertexSet[i]->info == in)
            return i;
    return -1;
}

#endif /* GRAPH_H_ */
