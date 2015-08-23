#ifndef GRAPHALGO_H
#define GRAPHALGO_H
#include <vector>

class Graph;

using namespace std;

class GraphAlgo
{
public:
    GraphAlgo(Graph& G, int s);
    bool isAchievable(int v);
    vector<int>* getPath(int v);
    ~GraphAlgo() {
        delete[] edgeTo;
        delete[] marked;
    }

private:
    GraphAlgo();
    void dfs(Graph& G, int s);
    
    int V;
    int start;
    int* edgeTo;
    bool* marked;
};

#endif // GRAPHALGO_H
