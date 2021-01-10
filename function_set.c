#include "function_set.h"

void Visual(struct Node* node, int level) {
//    //queue
//    printf("key len, %d\n", B_Tree->root->key_len);
//
//    for (int i = 0; i < B_Tree->root->key_len; i++)
//    {
//        printf("%d ", B_Tree->root->key_arr[i]);
//    }
    for(int i = 0; i <= node->key_len; i++){
        if (node->child_len > 0){
            Visual(&node->child_arr[i], level+1);
        }
        if (i <= node->key_len-1) {
            for (int j = 0; j < level; j++) {
                printf("--|");
            }
            printf("%d\n", node->key_arr[i]);
        }
    }

}


struct Node* CreateNode() {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->leaf = false;
    newNode->key_len = 0;
    newNode->child_len = 0;
    newNode->key_arr = (int*)malloc(sizeof(int) * (2 * min_degree - 1));
    newNode->child_arr = (struct Node*)malloc(sizeof(struct Node) * (2 * min_degree));

    return newNode;
};

struct B_tree* CreateTree() {
    struct B_tree* tree = (struct B_tree*)malloc(sizeof(struct B_tree));
    tree->root = CreateNode(min_degree);
    tree->root->leaf = true;
    return tree;
}

void InsertKey(struct B_tree* tree, int key) {
    struct Node* origin_root = tree->root;

    //á����
    if (origin_root->key_len == (2 * min_degree - 1)) {
        struct Node* newNode = CreateNode(min_degree);
        tree->root = newNode;
        tree->root->leaf = false;
        tree->root->child_arr[tree->root->child_len] = *origin_root;
        tree->root->child_len++;
        SplitChild(tree->root, 0); //tree, index
        NonFull(tree->root, key); // tree, key
    }
        //��á����
    else {
        NonFull(origin_root, key);
    }
}

void NonFull(struct Node* node, int key) {
    int i = node->key_len - 1;

    if (node->leaf) {
        while (i >= 0 && key < node->key_arr[i]) {
            node->key_arr[i + 1] = node->key_arr[i];
            i--;
        }
        i++;
        node->key_arr[i] = key;
        node->key_len++;
    }
    else {
        // �ڽ� ��� Ÿ�� ������ ��
        while (i >= 0 && key < node->key_arr[i]) {   //�ε��� ã��
            i--;
        }
        i++;
        if (node->child_arr[i].key_len == (2 * min_degree - 1)) {
            SplitChild(node, i);
            NonFull(node, key);
        }
        else {
            NonFull(&node->child_arr[i], key);
        }
    }
}

void SplitChild(struct Node* node_x, int index) {
    struct Node* node_z = CreateNode();
    struct Node* node_y = &node_x->child_arr[index];
    node_z->leaf = node_y->leaf;
    node_z->key_len = min_degree - 1;
    node_z->child_len = min_degree;
    for (int j = 0; j < min_degree - 1; j++) {
        node_z->key_arr[j] = node_y->key_arr[j + min_degree];
    }
    if (!node_y->leaf) {
        for (int j = 0; j < min_degree; j++) {
            node_z->child_arr[j] = node_y->child_arr[j + min_degree];
        }
    }
    //y�� ������ �ʱ�ȭ

    node_y->key_len = min_degree - 1;
    node_y->child_len = min_degree;
    // x���� chidren index�� �ڷ� �Ѱ���
    for (int j = node_x->child_len - 1; j > index; j--)
    {
        node_x->child_arr[j + 1] = node_x->child_arr[j];
    }
    node_x->child_arr[index + 1] = *node_z;

    for (int j = node_x->key_len - 1; j >= index; j--)
    {
        node_x->key_arr[j + 1] = node_x->key_arr[j];
    }
    node_x->key_arr[index] = node_y->key_arr[min_degree - 1];
    node_x->key_len++;
}

struct Searched Search(struct Node* node, int key, int num){
    struct Searched result;
    printf("%d\n", num);
    int i =0;
    for (; i < node->key_len; ++i) {
        if (key == node->key_arr[i]){
            result.node = node;
            result.index = i;
            printf("success %d %d\n", i, key);
            return result;
        }
        if (key < node->key_arr[i]){
            if (node->leaf){
                printf("fail");
                return result;
            }
            else {
                break;
            }
        }
    }
    printf("in %d %d\n", i, key);
    return result = Search(&node->child_arr[i], key, num+1);
}