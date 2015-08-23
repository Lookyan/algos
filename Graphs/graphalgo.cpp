#include "graph.h"
#include "graphalgo.h"
#include "assert.h"

using namespace std;

GraphAlgo::GraphAlgo(Graph& G, int s) : V(G.getV()), start(s)
{
    edgeTo = new int[G.getV()];
    marked = new bool[G.getV()];
    for(int i = 0; i < G.getV(); i++) {
        marked[i] = false;
        edgeTo[i] = -1;
    }
    marked[s] = true;
    dfs(G, s);
}

void GraphAlgo::dfs(Graph &G, int s)
{
    for(list<int>::iterator iter = G.getAdj(s)->begin(); iter != G.getAdj(s)->end(); iter++) {
        if(!marked[*iter]) {
            marked[*iter] = true;
            edgeTo[*iter] = s;
            dfs(G, *iter);
        }
    }
}

bool GraphAlgo::isAchievable(int v)
{
    assert(v < V);
    return marked[v];
}

vector<int>* GraphAlgo::getPath(int v)
{
    vector<int>* path = new vector<int>;
    int current = v;
    while(current != start) {
        path->push_back(current);
        current = edgeTo[current];
    }
    return path;
}

