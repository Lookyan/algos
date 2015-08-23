#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <list>

using namespace std;

class Graph
{
public:
    Graph();
    Graph(int V);
    void addEdge(int v, int w);
    int getV() { return V; }
    int getE() { return E; }
    list<int>* getAdj(int v);
private:
    vector< list<int> > adj;
    int V; // кол-во вершин
    int E; // кол-во ребер
};

#endif // GRAPH_H
