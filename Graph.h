//
// Areman Hashemi, #1744655, pa5
//
#define UNDEF -1
#define NIL 0
#include "List.h"
#ifndef DFS_GRAPH_H
#define DFS_GRAPH_H
enum {
    WHITE, //0
    GRAY,  //1
    BLACK, //2
} color;
typedef struct GraphObj* Graph;
/* Constructors-Destructors */
Graph newGraph(int n);
void freeGraph(Graph* pG);
/* Access functions */
int getOrder(Graph G);
int getSize(Graph G);
int getParent(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) */
int getDiscover(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) */
int getFinish(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) */
/* Manipulation procedures */
void addArc(Graph G, int u, int v); /* Pre: 1<=u<=n, 1<=v<=n */
void addEdge(Graph G, int u, int v); /* Pre: 1<=u<=n, 1<=v<=n */
void DFS(Graph G, List S); /* Pre: length(S)==getOrder(G) */
/* Other Functions */
Graph transpose(Graph G);
Graph copyGraph(Graph G);
void printGraph(FILE* out , Graph G);
void priGraph(Graph G);
#endif //DFS_GRAPH_H
