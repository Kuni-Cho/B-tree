#ifndef FUNCTION_SET
# define FUNCTION_SET

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// structure

struct Node {
	bool leaf;
	int key_len;
	int child_len;
	int* key_arr;
	struct Node* child_arr;
};

struct B_tree{	
	struct Node* root;
	int min_degree;
};


// function
struct B_tree* CreateTree(int min_degree);
struct Node* CreateNode(int min_degree);
void InsertKey(struct B_tree* tree, int key);
void NonFull(struct Node* node, int key);

#endif
