#include "function_set.h"


struct Node* CreateNode(int min_degree) {

	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	newNode->leaf = false;
	newNode->key_len = 0;
	newNode->child_len = 0;
	newNode->key_arr = (int*)malloc(sizeof(int) * (2*min_degree - 1));
	newNode->child_arr = (struct Node*)malloc(sizeof(struct Node) * (2 * min_degree));

	return newNode;
};

struct B_tree* CreateTree(int min_degree) {
	struct B_tree* tree = (struct B_tree*)malloc(sizeof(struct B_tree));
	tree->root = CreateNode(min_degree);
	tree->root->leaf = true;
	tree->min_degree = min_degree;

	return tree;
}

void InsertKey(struct B_tree* tree, int key) {
	struct Node* origin_root = tree->root;
	int child_num = tree->min_degree;

	if (origin_root->key_len == (2*child_num-1)) {
		struct Node* newNode = CreateNode(child_num);
		tree->root = newNode;
		tree->root->leaf = false;
		tree->root->child_arr[tree->root->child_len] = *origin_root;
		tree->root->child_len++;
		
	}
	else {
		NonFull(origin_root, key);
	}
}

void NonFull(struct Node* node, int key) {
	int i = node->key_len;

	if (node->leaf) {
		while (i >= 1 && key < node->key_arr[i]) {
			node->key_arr[i + 1] = node->key_arr[i];
			i = i - 1;
		}

		if (i == 0) {
			node->key_arr[i] = key;
		}
		else {
			node->key_arr[i + 1] = key;
		}

		//(i == 0) ? node->key_arr[i] = key : node->key_arr[i + 1] = key;
		node->key_len++;
	}
	else {
		// 자식 노드 타고 내려갈 것
	}
}

void SplitChild() {

}