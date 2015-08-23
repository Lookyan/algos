#include "graph.h"

Graph::Graph() : V(0), E(0)
{
}

Graph::Graph(int V): V(V), E(0)
{
    for(int i = 0; i < V; i++) {
        adj.push_back(list<int>());
    }
}

void Graph::addEdge(int v, int w)
{
    adj[v].push_front(w);
    adj[w].push_front(v);
    E++;
}

list<int>* Graph::getAdj(int v)
{
    return &adj[v];
}
