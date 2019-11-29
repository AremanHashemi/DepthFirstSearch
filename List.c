//
// Areman Hashemi, #1744655, pa4
//
#include "List.h"

//private NodeObj
typedef struct NodeObj{
    int data;
    struct NodeObj* next;
    struct NodeObj* previous;
} NodeObj;

typedef NodeObj* Node;

// Constructors-Destructors ---------------------------------------------------
// newNode()
// Returns reference to new Node object. Initializes next and data fields.
// Private.
Node newNode(int data){
    Node N = malloc(sizeof(NodeObj));
    N->data = data;
    N->next = NULL;
    N->previous = NULL;
    return(N);
}

void checkNullity(List L, char *functionName){
    if( L == NULL ){
        printf("List Error: calling %s on a NULL List reference", functionName);
        exit(1);
    }
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
// Private.
void freeNode(Node* pN){
    if( pN!=NULL && *pN!=NULL ){
        free(*pN);
        *pN = NULL;
    }
}
typedef struct ListObj {
    Node front;
    Node back;
    Node currentCursor;
    int index;
    int length;
} ListObj;

// Constructors-Destructors ---------------------------------------------------
// Creates and returns a new empty List.
List newList(void){
    List L;
    L = malloc(sizeof(ListObj));
    L->front = L->back = NULL;
    L->length = 0;
    L->index  = -1;
    L-> currentCursor = NULL;
    return (L);
}
// Frees all heap memory associated with *pL, and sets
// *pL to NULL.
void freeList(List* pL){
    checkNullity(*pL,"freeList()");
    if( pL != NULL ){
        while(length(*pL) > 0){
            deleteBack(*pL);
        }
        free(*pL);
        *pL = NULL;
    }
}

// Access functions -----------------------------------------------------------
int length(List L){
    checkNullity(L,"length()");
    return L->length;} // Returns the number of elements in L.
// Returns index of cursor element if defined, -1 otherwise.
int index(List L){
    checkNullity(L,"index()");
    return L->index;
}

// Returns front element of L. Pre: length()>0
int front(List L){
    checkNullity(L, "front()");
    if( isEmpty(L) ){
        printf("List Error: calling front on an empty List\n");
        exit(1);
    }
    return(L->front->data);
}

int back(List L){
    checkNullity(L,"back()");
    if( isEmpty(L)){
        printf("List Error: calling back() on an empty List\n");
        exit(1);
    }
    return(L->back->data);
}

// Returns cursor element of L. Pre: length()>0, index()>=0
int get(List L){
    checkNullity(L,"get()");
    if(L->length <= 0){
        printf("List Error: calling get() on empty List");
        exit(1);
    }
    if(L->currentCursor==NULL){
        printf("List Error: calling get() on non existant cursor");
        exit(1);
    }
    return L->currentCursor->data;
}

// Returns true (1) iff Lists A and B are in same
// state, and returns false (0) otherwise.
int equals(List A, List B){
    int eq = 0;
    Node N = NULL;
    Node M = NULL;
    if( A==NULL || B==NULL )
    {
        printf("Stack Error: calling equals() on NULL Stack reference\n");
        exit(1);
    }
    eq = ( A->length == B->length );
    N = A->front;
    M = B->front;
    while( eq && N!=NULL)
    {
        eq = ( N->data==M->data );
        N = N->next;
        M = M->next;
    }
    return eq;
}

// Returns true (1) if L is empty, otherwise returns false (0)
int isEmpty(List L){
    checkNullity(L,"isEmpty()");
    return(L->length==0);
}


// Manipulation procedures ----------------------------------------------------
// Resets L to its original empty state.
void clear(List L){
    checkNullity(L,"clear()");
    while( length(L) > 0){
        printf("\n");
        deleteBack(L);
    }
    L->length = 0;
    L->index = -1;
    L->front = NULL;
    L->back = NULL;
    L->currentCursor = NULL;
}
// If L is non-empty, sets cursor under the front element,
// otherwise does nothing.
void moveFront(List L){
    checkNullity(L,"moveFront()");
    if(!isEmpty(L)){
        L->currentCursor = L->front;
        L->index = 0;
    }
}

// If L is non-empty, sets cursor under the back element,
// otherwise does nothing.
void moveBack(List L){
    checkNullity(L,"moveBack()");
    if(!isEmpty(L)){
        L->currentCursor = L->back;
        L->index = L->length-1;
    }
}

// If cursor is defined and not at front, move cursor one
// step toward the front of L; if cursor is defined and at
// front, cursor becomes undefined; if cursor is undefined
// do nothing
void movePrev(List L){
    checkNullity(L,"movePrev()");
    if(  L->index!=0 ){
        L->currentCursor = L->currentCursor->previous;
        L->index--;
    }
    else {
        L->currentCursor = NULL;
        L->index = -1;
    }
}
// If cursor is defined and not at back, move cursor one
// step toward the back of L; if cursor is defined and at
// back, cursor becomes undefined; if cursor is undefined
// do nothing
void moveNext(List L){
    checkNullity(L,"moveNext()");
    if( L->index != L->length-1){
        L->currentCursor = L->currentCursor->next;
        L->index++;
    }
    else{
        L->currentCursor = NULL;
        L->index = -1;
    }
}

// Insert new element into L. If L is non-empty,
// insertion takes place before front element.
void prepend(List L, int data){
    Node N = newNode(data);
    checkNullity(L,"prepend");
    if(isEmpty(L)){
        L->back  = N;
    }
    else{
        N->next = L->front;
        L->front->previous = N;
    }
    L->front = N;
    L->length++;
    L->index++;
}

// Insert new element into L. If L is non-empty,
// insertion takes place after back element.
void append(List L, int data){
    checkNullity(L,"append()");
    Node N = newNode(data);
    if(isEmpty(L)){
        L->front = N;
    }
    else{
        L->back->next = N;
        N->previous = L->back;
    }
    L->back = N;
    L->length++;
}
// Insert new element before cursor.
// Pre: length()>0, index()>=0
void insertBefore(List L, int data){
    checkNullity(L,"insertBefore()");
    if(L->index == -1){
        printf("List Error: calling insertBefore() on null cursor");
    }
    if(L->index == 0){
        prepend(L,data);
    }
    else if(L->length > 0){
        Node N = newNode(data);
        N->next = L->currentCursor;
        N->previous = L->currentCursor->previous;
        L->currentCursor->previous->next = N;
        L->currentCursor->previous = N;
        L->length++;
        L->index++;
    }
}

// Insert new element after cursor.
// Pre: length()>0, index()>=0
void insertAfter(List L, int data){
    checkNullity(L,"insertAfter()");
    if(L->length <= 0){
        printf("List Error: calling insertAfter() on an empty List");
        exit(1);
    }
    if(L->index < 0){
        printf("List Error: calling insertAfter() on an a null index");
    }
    if(L->currentCursor == L->back){
        append(L,data);
    }else{
        Node N = newNode(data);
        N->previous = L->currentCursor;
        N->next = L->currentCursor->next;
        L->currentCursor->next->previous = N;
        L->currentCursor->next = N;
        L->length++;
    }

}

// Delete the front element. Pre: length()>0
void deleteFront(List L){
    checkNullity(L,"deleteFront()");
    if(L->length <= 0){
        printf("List Error: calling deleteFront() on an empty List");
        exit(1);
    }
    Node N = NULL;
    N = L->front;
    if(L->length == 1){
        L->back = NULL;
        L->front = NULL;
        L->currentCursor = NULL;
        L->index = -1;
    }
    else{
        L->front = L->front->next;
        L->front->previous = NULL;
        if(L->index != -1){
            L->index--;
        }
    }
    freeNode(&N);
    L->length--;
}
// Delete the back element. Pre: length()>0
void deleteBack(List L){
    checkNullity(L,"deleteBack()");
    if(L->length < 1){
        printf("List Error: calling deleteBack() on an empty List");
        exit(1);
    }
    Node N = NULL;
    N = L->back;
    if(L->length == 1){
        L->back = NULL;
        L->front = NULL;
        L->currentCursor = NULL;
        L->index = -1;
    }else{
        L->back = L->back->previous;
        L->back->next = NULL;
        if(L->index+1 == L->length){
            L->index = -1;
        }
    }
    freeNode(&N);
    L->length--;
}


// Delete cursor element, making cursor undefined.
// Pre: length()>0, index()>=0
// Other operations -----------------------------------------------------------
void delete(List L){
    checkNullity(L,"delete()");
    if(length(L) <= 0){
        printf("List error: calling delete() an empty list");
    }
    if(index(L) < 0){
        printf("List error: calling delete() an NULL cursor");
    }
    if(L->index == 0){
        deleteFront(L);
    }
    else if(L->index == L->length-1){
        deleteBack(L);
    }
    else{
        Node N = L->currentCursor;
        L->currentCursor->next->previous = L->currentCursor->previous;
        L->currentCursor->previous->next = L->currentCursor->next;
        L->currentCursor = NULL;
        freeNode(&N);
        L->length--;
    }
    L->index = -1;
}

// Prints to the file pointed to by out, a
// string representation of L consisting
// of a space separated sequence of integers,
// with front on left.
void printList(FILE* out, List L){
    out = fopen((const char *) out, "w");
    if( out==NULL ){
        printf("Unable to open file for writing\n");
        exit(1);
    }
    Node iterator = L->front;
    while(iterator->next != NULL){
        fprintf(out," %d ",iterator->data);
        iterator = iterator->next;
    }
    fclose(out);
}


// Returns a new List representing the same integer
// sequence as L. The cursor in the new list is undefined,
// regardless of the state of the cursor in L. The state
// of L is unchanged.
List copyList(List L){
    List tempList = newList();
    Node N = NULL;
    N = L->front;
    for( int i = 0; i < length(L); i++){
        append(tempList,N->data);
        N = N->next;
    }
    return tempList;
}


// Returns a new List which is the concatenation of
// A and B. The cursor in the new List is undefined,
// regardless of the states of the cursors in A and B.
// The states of A and B are unchanged
List concatList(List A, List B){
    List returnList = newList();
    Node N = NULL;
    N = A->front;
    for( int i = 0; i < length(A); i++){
        append(returnList, N->data);
        N = N->next;
    }
    N = B->front;
    for( int i = 0; i < length(B); i++){
        append(returnList, N->data);
        N = N->next;
    }
    return returnList;
}
