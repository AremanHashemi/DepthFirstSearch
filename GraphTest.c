//
// Created by areman on 11/29/19.
//
#include "Graph.h"
void testDirectedGraph();

int main(){
    testDirectedGraph();
}

void testDirectedGraph(){
    Graph G = newGraph(8);

    addArc(G,1,2);

    addArc(G,2,3);
    addArc(G,2,6);
    addArc(G,2,5);

    addArc(G,3,4);
    addArc(G,3,7);

    addArc(G,4,3);
    addArc(G,4,8);

    addArc(G,5,1);
    addArc(G,5,6);

    addArc(G,6,7);

    addArc(G,7,6);
    addArc(G,7,8);

    addArc(G,8,8);
    priGraph(G);
}
