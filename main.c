#include "function_set.h"

int main() {
    min_degree = 2;
    struct B_tree* B_Tree = CreateTree(2);


//    for (int i = 0; i < 20; i++){
//        srand(i);
//        int r = rand()%100;
//        printf("%d  ", r);
//        InsertKey(B_Tree, r);
//    }
//    printf("\n");

    for (int i = 0; i < 20; i++){
        InsertKey(B_Tree, i);
    }
    printf("\n");


    /*struct Node* Node1 = CreateNode();
    for (int i = 0; i < 2 * min_degree; i++)
    {
        struct Node* Node1 = CreateNode();
        Node1->child_arr[i]
    }*/

    Visual(B_Tree->root, 0);
    Search(B_Tree->root, 10, 1);
    return 0;
}