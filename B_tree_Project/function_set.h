#ifndef FUNCTION_SET
# define FUNCTION_SET

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

// function
struct B_tree* CreateTree();
struct Node* CreateNode();
void InsertKey(struct B_tree* tree, int key);
void NonFull(struct Node* node, int key);

#endif
