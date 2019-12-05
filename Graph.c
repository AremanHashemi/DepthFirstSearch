//
// Areman Hashemi, #1744655, pa5
//
#include "Graph.h"
//HELPER FUNCTIONS
void checkGraphNullity(Graph G, char *functionName);
int placeInOrder(List A, int x);
void visit(Graph G, int index, int* time, List S);

typedef struct GraphObj {
    List* adjacencyList;
    int* color;
    int* parent;
    int* discoverTime;
    int* finishTime;
    int order;
    int size;
}GraphObj;

/*** Constructors-Destructors ***/
Graph newGraph(int n) {
    n++; // to account for indexing at 1
    Graph G = malloc(sizeof(GraphObj));
    G->adjacencyList = calloc(n,sizeof(List));
    G->color = calloc(n, sizeof(int));
    G->parent = calloc(n, sizeof(int));
    G->discoverTime = calloc(n, sizeof(int));
    G->finishTime = calloc(n, sizeof(int));
    for(int i = 1; i < n; i++) {
        G->adjacencyList[i] = newList();
        G->color[i]         = WHITE;
        G->finishTime[i]    = UNDEF;
        G->discoverTime[i]  = UNDEF;
        G->parent[i]        = NIL;
    }
    n--; // no longer need indexing
    G->order = n;
    G->size = 0;
    return G;
}
void freeGraph(Graph* pG){
    if(pG == NULL){
        return;
    }
    if(*pG != NULL){
        for(int i = 1; i < (*pG)->order+1; i++) {
            freeList(&((*pG)->adjacencyList[i]));
        }
        free((*pG)->adjacencyList);
        free((*pG)->color);
        free((*pG)->discoverTime);
        free((*pG)->finishTime);
        free((*pG)->parent);
        free(*pG);
        *pG = NULL;
    }
}
/*** Access functions ***/
int getOrder(Graph G){
    checkGraphNullity(G,"getOrder()");
    return G->order;
}
int getSize(Graph G){
    checkGraphNullity(G,"getSize()");
    return G->size;
}

/* Pre: 1<=u<=n=getOrder(G) */
int getParent(Graph G, int u){
    if(1 > u){
        printf("Graph ERROR: getParent() u < 1");
    }
    if(u > getOrder(G)){
        printf("Graph ERROR: getParent() u > getOrder");
    }
    return G->parent[u];
}
/* Pre: 1<=u<=n=getOrder(G) */
int getDiscover(Graph G, int u){
    if(1 > u){
        printf("Graph ERROR: getDiscover() u < 1");
    }
    if(u > getOrder(G)){
        printf("Graph ERROR: getDiscover() u > Order(G)");
    }
    return G->discoverTime[u];
}
/* Pre: 1<=u<=n=getOrder(G) */
int getFinish(Graph G, int u){
    if(1 > u){
        printf("Graph ERROR: getFinish() u < 1");
    }
    if(u > getOrder(G)){
        printf("Graph ERROR: getFinish() u > Order(G)");
    }
    return G->finishTime[u];
}

/*** Manipulation procedures ***/
void addEdge(Graph G, int u, int v){
    checkGraphNullity(G,"addEdge()");
    if( u <= 0 || v <= 0) {
        printf("Graph ERROR: using u || v <= 0 ");
        exit(1);
    }
    if( u > getOrder(G) || v > getOrder(G)) {
        printf("Graph ERROR: using u || v > number of vertices ");
        exit(1);
    }
    if(placeInOrder(G->adjacencyList[u],v) != 1){
        G->size++;
    }
    if(placeInOrder(G->adjacencyList[v],u) != 1){
        //G->size++;
    }
}

/*
 * Places vertex in list in increasing order
 * If vertex is already in list subsequently is not readded returns 1
 */
int placeInOrder(List A, int x){
    moveFront(A);
    while(index(A) != -1 && get(A) < x){
        moveNext(A);
    }
    if(index(A) == -1){
        append(A, x);
        return 0;
    }else if(get(A) != x) {
        insertBefore(A, x);
        return 0;
    }
    return 1;
}
void addArc(Graph G, int u, int v){
    checkGraphNullity(G,"addArc()");
    if( u <= 0 || v <= 0) {
        printf("Graph ERROR: using u || v <= 0 in Arc()");
        exit(1);
    }
    if( u > getOrder(G) || v > getOrder(G)) {
        printf("Graph ERROR: using u || v > number of vertices in Arc()");
        exit(1);
    }
    if(placeInOrder(G->adjacencyList[u],v) != 1){
        G->size++;
    }
}
void DFS(Graph G, List S){/* Pre: length(S)==getOrder(G) */
    if(length(S) != getOrder(G)) {
        printf("Graph Error: calling DFS() with length(S)!=getOrder(G) ");
        exit(1);
    }
    for(int i = 1; i <= getOrder(G); i++){
        G->color[i] = WHITE;
        G->parent[i] = NIL;
    }
    int time = 0;
    for(moveFront(S); index(S) != -1; moveNext(S)){
        int startVertex = get(S);
        if(G->color[startVertex] == WHITE){
            visit(G, startVertex, &time,S);
        }
    }
    for(int i = 0; i < getOrder(G); i++){
        deleteBack(S);
    }
}
void visit(Graph G, int vertex, int* time, List S){
    G->discoverTime[vertex] = (++*time);
    G->color[vertex] = GRAY;
    List adjList = G->adjacencyList[vertex];
    for(moveFront(adjList); index(adjList) != -1; moveNext(adjList)){
        int adjVertex = get(adjList);
        if(G->color[adjVertex] == WHITE){
            G->parent[adjVertex] = vertex;
            visit(G,adjVertex, time, S);
        }
    }
    G->color[vertex] = BLACK;
    G->finishTime[vertex] = (++*time);
    prepend(S,vertex);
}

/*** Other operations ***/
Graph transpose(Graph G){
    Graph GTranspose = newGraph(getOrder(G));
    for(int i = 1; i <= getOrder(G); i++){
        List adjList = G->adjacencyList[i];
        for(moveFront(adjList); index(adjList) != -1; moveNext(adjList)){
            addArc(GTranspose,get(adjList),i);
        }
    }
    return GTranspose;
}

Graph copyGraph(Graph G){
    Graph graphCopy = newGraph(getOrder(G));
    for(int i = 1; i <= G->order; i++) {
        List listToBeFreed = graphCopy->adjacencyList[i];
        graphCopy->adjacencyList[i] = copyList(G->adjacencyList[i]);
        freeList(&listToBeFreed);
        graphCopy->color[i]         = G->color[i];
        graphCopy->finishTime[i]    = G->finishTime[i];
        graphCopy->discoverTime[i]  = G->discoverTime[i];
        graphCopy->parent[i]        = G->parent[i];
    }
    graphCopy->size = G->size;
    return graphCopy;
}
void printGraph(FILE* out, Graph G){
    for(int i = 1; i <= G->order; i++){
        fprintf(out, "%d:", i);
        List adjacencies = G->adjacencyList[i];
        moveFront(adjacencies);
        for(; index(adjacencies) != -1; moveNext(adjacencies)) {
            fprintf(out, " %d ", get(adjacencies));
        }
        fprintf(out, "\n");
    }
}
void priGraph(Graph G) {
    printf("Graph: order = %d, size = %d\n", getOrder(G), getSize(G));
    for(int i = 1; i <= G->order; i++){
        printf("%d:", i);
        List adjacencies = G->adjacencyList[i];
        moveFront(adjacencies);
        for(; index(adjacencies) != -1; moveNext(adjacencies)) {
            printf(" %d ", get(adjacencies));
        }
        printf("\n");
    }
}

void checkGraphNullity(Graph G, char *functionName){
    if( G == NULL){
        printf("Graph Error: calling %s on a NULL Graph reference",functionName);
        exit(1);
    }
}