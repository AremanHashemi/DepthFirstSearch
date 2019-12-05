//
// Areman Hashemi, #1744655, pa5
//
#include "Graph.h"
void testDirectedGraph();
void testTranspose();
void testCopy();
void testDeepCopy();
void testDFS();
int main(){
//    testDFS();
//    testCopy();
//    testDeepCopy();
//    testDirectedGraph();
    testTranspose();
}
void testDFS(){
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
    List L = newList();
    append(L,1);
    append(L,2);
    append(L,3);
    append(L,4);
    append(L,5);
    append(L,6);
    append(L,7);
    append(L,8);
    DFS(G,L);
    for(int i = 1; i <= 8; i++){
        printf("Vertex %d | Discover %d | Finish %d | Parent %d\n",i,getDiscover(G,i),getFinish(G,i),getParent(G,i));
    }
    Graph GTranspose = transpose(G);
    priGraph(GTranspose);
    priList(L);
    DFS(GTranspose,L);
    printf("\n\n");
    for(int i = 1; i <= 8; i++){
        printf("Vertex %d | Discover %d | Finish %d | Parent %d\n",i,getDiscover(GTranspose,i),getFinish(GTranspose,i),getParent(GTranspose,i));
    }
}
void testDeepCopy(){
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
    printf("\nCopy G after adding (1,5),(4,5):\n");
    Graph copyG = copyGraph(G);

    addArc(copyG,1,5);
    addArc(copyG,4,5);
    priGraph(copyG);
}
void testCopy(){
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

    printf("\nCopy G:\n");
    Graph copyG = copyGraph(G);
    priGraph(copyG);
}
void testTranspose(){
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
    printf("Graph G:\n");
    priGraph(G);
    Graph T = transpose(G);
    printf("G transpose: \n");
    priGraph(T);
    freeGraph(&G);
    freeGraph(&T);

}
void testBaseTranspose(){
    Graph G = newGraph(2);
    addArc(G,1,2);

    Graph T = transpose(G);
    printf("G transpose: \n");
    priGraph(T);
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
