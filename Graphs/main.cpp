#include <iostream>
#include "graph.h"
#include "graphalgo.h"

using namespace std;

int main()
{
    Graph graph(5);
    graph.addEdge(2, 3);
    graph.addEdge(4, 2);
    graph.addEdge(1, 4);    
    graph.addEdge(2, 1);
    graph.addEdge(3, 4);
    graph.addEdge(3, 1);
    graph.addEdge(3, 0);
    
    GraphAlgo algo(graph, 2);
    cout << algo.isAchievable(0);
    
    return 0;
}

