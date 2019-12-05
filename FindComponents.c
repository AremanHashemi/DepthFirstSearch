//
// Areman Hashemi, #1744655, pa4
//
#include<stdio.h>
#include<stdlib.h>
#include "Graph.h"
void checkArgc(int argc);
void openFile(FILE **in, char * fileName);
void readGraphOrder(FILE** in, int* size);

int main(int argc, char* argv[]){
    checkArgc(argc);
    int  order = 0;
    char *inputFile= argv[1];
    char *outputFile =argv[2];
    FILE *in = NULL;
    FILE *out = NULL;
    openFile(&in, inputFile);
    readGraphOrder(&in, &order);
    Graph A = newGraph(order);
    int src = 0;
    int dst = 0;
    do{
        fscanf(in,"%d",&src);
        fscanf(in,"%d",&dst);
        if(src != 0 || dst != 0){
            addArc(A,src,dst);
        }
    }while(src != 0 || dst != 0);
    out = fopen(outputFile, "w");
    if( out==NULL ){
        printf("Unable to open file %s for writing\n", outputFile);
        exit(1);
    }
    printGraph(out,A);
    List L = newList();
    for(int i = 1; i <= getOrder(A); i++){
        append(L,i);
    }
    DFS(A,L);
    Graph ATranspose = transpose(A);
    DFS(ATranspose,L);
    priList(L);
    //FIND SCC
    int numSCC = 0;
    List sccHeads = newList();
    for(moveBack(L);index(L) != -1; movePrev(L)){
        if(getParent(ATranspose,get(L)) == NIL){
            numSCC++;
            prepend(sccHeads, get(L));
        }
    }

    List* SCC = calloc(numSCC,(List));

    fprintf(out,"\nG contains %d strongly connected components:\n",numSCC);
    moveBack(sccHeads);
    for(moveBack(L);index(L) != -1; movePrev(L)){
        if(get(L) == get(sccHeads)){

        }
        fprintf(out," %d",get(L));
    }

    freeGraph(&A);
    fclose(in);
    fclose(out);
    return(0);
}
void checkArgc(int argc){
    if(argc != 3){
        printf("error");
        exit(1);
    }
}
void openFile(FILE **in, char * fileName){
    *in = fopen(fileName, "r");
    if (*in == NULL){
        printf("Unable to open file %s for reading\n", fileName);
        exit(1);
    }
}
void readGraphOrder(FILE** in, int* size){
    if(size < 0){
        printf("FindPath ERROR: input file has Size < 0 ");
        exit(1);
    }
    fscanf(*in, "%d", *&size);
}