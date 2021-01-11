#ifndef UNTITLED1_FUNCTION_SET_H
#define UNTITLED1_FUNCTION_SET_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int min_degree;

// structure

struct Node {
    bool leaf;
    int key_len;
    int child_len;
    int* key_arr;
    struct Node* child_arr;
};

struct B_tree {
    struct Node* root;
};

struct Searched {
    struct Node* node;
    int index;
};

// function
struct B_tree* CreateTree();
struct Node* CreateNode();

void Visual(struct Node* node, int level);
bool Search(struct Node* node, int key);

// Insert
void InsertKey(struct B_tree* tree, int key);
void NonFull(struct Node* node, int key);
void SplitChild(struct Node* node_x, int index);

// Delete
void Delete_key(struct B_tree* tree, struct Node* x, int key);
void Borrow_Right(struct Node* x, int idx);
void Borrow_Left(struct Node* x, int idx);
bool Change_Root(struct B_tree* tree, struct Node* x);
void merge(struct Node* x, int idx);
int Succ(struct Node* child_x);
int Pred(struct Node* child_x);

//Queue
#define MAX 10000
int IsEmpty(void);
int IsFull(void);
void addq(int value);
int deleteq();

#endif //UNTITLED1_FUNCTION_SET_H
