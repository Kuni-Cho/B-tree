#include "function_set.h"

int main() {
    min_degree = 2;
    struct B_tree* B_Tree = CreateTree(2);

    for (int i = 0; i < 20; i++){
        InsertKey(B_Tree, i);        
    }

    InsertKey(B_Tree, 30);
    Visual(B_Tree->root, 0);

    int out_arr[10] = {0, 1, 20, 30, 100};

    for (int i = 0; i < 5; i++) {                
        bool result = Search(B_Tree->root, out_arr[i]);
        if (result) {
            printf("삭제할 번호 : %d", out_arr[i]);
            Delete_key(B_Tree, B_Tree->root, out_arr[i]);
            printf("\n\n\n\n");
            Visual(B_Tree->root, 0);
        }
        else {
            printf("찾는 값이 없습니다 Key : %d\n\n", out_arr[i]);
        }
    }   

    return 0;
}