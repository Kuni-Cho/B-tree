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

bool Search(struct Node* node, int key){
    /*struct Searched result;*/    
    int i =0;
    bool result = false;
    for (; i < node->key_len; ++i) {
        if (key == node->key_arr[i]){
            /*result.node = node;
            result.index = i;*/
            
            printf("success : %d\n",key);
            return true;
        }
        if (key < node->key_arr[i]){           
             break;        
        }
    }    
    if (node->child_len > 0) {
        result = Search(&node->child_arr[i], key);
        
    }
    else {
        printf("failed %d\n", key);
    }
    return result;
}

int Pred(struct Node* child_x) {
    int ret = -1;
    if (!child_x->leaf) {
        ret = Pred(&child_x->child_arr[child_x->child_len - 1]);
    }
    else {
        return ret = child_x->key_arr[child_x->key_len - 1];
    }
    return ret;
}

int Succ(struct Node* child_x) {
    int ret = -1;
    if (!child_x->leaf) {
        ret = Succ(&child_x->child_arr[0]);
    }
    else {
        return ret = child_x->key_arr[0];
    }
    return ret;
}

void merge(struct Node* x, int idx) {
    struct Node* y = &x->child_arr[idx];
    struct Node* z = &x->child_arr[idx+1];    

    for (int i = 0; i < z->key_len; i++) {
        y->key_arr[y->key_len + i] = z->key_arr[i];        
    }

    for (int i = 0; i < z->child_len; i++) {
        y->child_arr[y->child_len+ i] = z->child_arr[i];
    }

    y->child_len = (2 * min_degree) - 1;
    y->key_len = (2 * min_degree) - 2;

    for (int i = idx; i < x->key_len; i++) {
        x->key_arr[i] = x->key_arr[i + 1];
    }
    x->key_len--;

    for (int i = idx + 1; i < x->child_len - 1; i++) {
        x->child_arr[i] = x->child_arr[i + 1];
    }
    x->child_len--;

    free(z);
}

bool Change_Root(struct B_tree* tree, struct Node* x) {
    bool result = false;
    if (x->key_len == 0) {
        tree->root = &x->child_arr[0];
        free(x);
        result = true;
        return result;
    }
    return result;
}

void Borrow_Left(struct Node* x, int idx) {
    struct Node* y = &x->child_arr[idx - 1];
    struct Node* z = &x->child_arr[idx];

    // z 노드 처리
    for (int i = 0; i < z->key_len; i++) {
        z->key_arr[z->key_len - i] = z->key_arr[z->key_len - i - 1];        
    }
    for (int i = 0; i < z->child_len; i++) {
        z->child_arr[z->child_len - i] = z->child_arr[z->child_len - i - 1];
    }
    z->key_len++;
    z->child_len++;
    z->key_arr[0] = x->key_arr[idx - 1];
    z->child_arr[0] = y->child_arr[y->child_len - 1];

    // y 노드 처리
    x->key_arr[idx - 1] = y->key_arr[y->key_len - 1];
    y->key_len--;    
    y->child_len--;
}

void Borrow_Right(struct Node* x, int idx) {
    struct Node* y = &x->child_arr[idx];
    struct Node* z = &x->child_arr[idx + 1];

    // y 노드 처리
    y->key_arr[y->key_len] = x->key_arr[idx];
    y->child_arr[y->child_len] = z->child_arr[0];
    y->key_len++;
    y->child_len++;

    // z 노드 처리
    x->key_arr[idx] = z->key_arr[0];
    
    for (int i = 0; i < z->key_len - 1; i++) {
        z->key_arr[i] = z->key_arr[i+1];
    }
    for (int i = 0; i < z->child_len - 1; i++) {
        z->child_arr[i] = z->child_arr[i + 1];
    }
    z->key_len--;
    z->child_len--;
}


void Delete_key(struct B_tree* tree, struct Node* x, int key) {
    int idx = 0;    
    for (; idx < x->key_len; idx++) {
        if (key <= x->key_arr[idx]) {
            break;
        }
    }

    if (key == x->key_arr[idx]) {
        // case 1
        if (x->leaf) {
            for (int i = idx; i < x->key_len - 1; i++) {
                x->key_arr[i] = x->key_arr[i + 1];
            }
            x->key_len--;
        }
        // case 2
        else {
            // case 2 - a
            if (x->child_arr[idx].key_len > min_degree - 1) {
                int k_prime = Pred(&x->child_arr[idx]);
                Delete_key(tree, &x->child_arr[idx], k_prime);
                x->key_arr[idx] = k_prime;
                return;

                // case 2 - b
            }
            else if (x->child_arr[idx + 1].key_len > min_degree - 1) {
                int k_prime = Succ(&x->child_arr[idx + 1]);
                Delete_key(tree, &x->child_arr[idx + 1], k_prime);
                x->key_arr[idx] = k_prime;
                return;
            }
            else {
                // 병합하고 루트 바꿔서 삭제 진행함
                merge(x, idx);
                if (Change_Root(tree, x)) {
                    Delete_key(tree, tree->root, key);
                    return;
                }
                else {
                    Delete_key(tree, x, key);
                    return;
                }
            }
        }
    }
    // case 3
    else {
        if (x->child_arr[idx].key_len > min_degree - 1) {
            Delete_key(tree, &x->child_arr[idx], key);
            return;
        }
        else {
            // case 3-a
            if (idx != 0 && x->child_arr[idx - 1].key_len > min_degree - 1) {
                Borrow_Left(x, idx);
                Delete_key(tree, x, key);
                return;
            }
            // case 3-b
            else if(idx != x->child_len - 1 && x->child_arr[idx + 1].key_len > min_degree - 1){
                Borrow_Right(x, idx);
                Delete_key(tree, x, key);
                return;
            }
            // case 3-c
            else {
                struct Node* y = &x->child_arr[idx];
                struct Node* z = &x->child_arr[idx + 1];

                // y에 x,z 병합
                y->key_arr[y->key_len] = x->key_arr[idx];
                y->key_len++;

                for (int i = 0; i < z->key_len; i++) {
                    y->key_arr[y->key_len + i] = z->key_arr[i];
                    y->key_len++;
                }
                for (int i = 0; i < z->child_len; i++) {
                    y->child_arr[y->child_len+ i] = z->child_arr[i];
                    y->child_len++;
                }
                free(z);                
                // x 당겨주기
                for (int i = idx; i < x->key_len - 1; i++) {
                    x->key_arr[i] = x->key_arr[i + 1];
                }
                x->key_len--;
                
                for (int i = idx; i < x->child_len - 1; i++) {
                    x->child_arr[i] = x->child_arr[i + 1];
                }
                x->child_len--;

                // 루트확인
                if (Change_Root(tree, x)) {
                    Delete_key(tree, tree->root, key);
                    return;
                }
                else {
                    Delete_key(tree, x, key);
                    return;
                }
            }
        }
    }
}




