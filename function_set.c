#include "function_set.h"

void Visual(struct Node* node, int level) {
	for (int i = 0; i <= node->key_len; i++) {
		if (node->child_len > 0 && !node->leaf) {
			Visual(node->child_arr[i], level + 1);
		}
		if (i <= node->key_len - 1) {
			for (int j = 0; j < level; j++) {
				printf("--|");
			}
			printf("%d\n", node->key_arr[i]);
		}
	}
}

void free_node(struct Node* node) {	
	free(node->child_arr);
	free(node->key_arr);
	free(node);
	printf("Free Complete\n");
}

struct Node* CreateNode() {
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	newNode->leaf = false;
	newNode->key_len = 0;
	newNode->child_len = 0;
	return newNode;
};

struct B_tree CreateTree() {
	struct B_tree tree;
	tree.root = CreateNode(min_degree);
	tree.root->leaf = true;
	return tree;
}

void InsertKey(struct B_tree* tree, int key) {
	struct Node* origin_root = tree->root;
	
	if (origin_root->key_len == (2 * min_degree - 1)) {
		struct Node* newNode = CreateNode(min_degree);
		tree->root = newNode;
		tree->root->leaf = false;
		tree->root->child_arr[tree->root->child_len] = origin_root;
		tree->root->child_len++;
		SplitChild(tree->root, 0);
		NonFull(tree->root, key);
	}	
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
		while (i >= 0 && key < node->key_arr[i]) { 
			i--;
		}
		i++;
		if (node->child_arr[i]->key_len == (2 * min_degree - 1)) {
			SplitChild(node, i);
			NonFull(node, key);
		}
		else {
			NonFull(node->child_arr[i], key);
		}
	}
}

void SplitChild(struct Node* node_x, int index) {
	struct Node* node_z = CreateNode();
	struct Node* node_y = node_x->child_arr[index];

	// 1. Arragne z node's env & Move y node's key & child to z node

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

	node_y->key_len = min_degree - 1;
	node_y->child_len = min_degree;

	// 2. Rearrange x node's env
	for (int j = node_x->child_len - 1; j > index; j--)
	{
		node_x->child_arr[j + 1] = node_x->child_arr[j];
	}
	node_x->child_arr[index + 1] = node_z;
	if(!node_x->leaf) node_x->child_len++;

	for (int j = node_x->key_len - 1; j >= index; j--)
	{
		node_x->key_arr[j + 1] = node_x->key_arr[j];
	}
	node_x->key_arr[index] = node_y->key_arr[min_degree - 1];
	node_x->key_len++;
}

bool Search(struct Node* node, int key) {	
	int i = 0;
	bool result = false;
	for (; i < node->key_len; ++i) {
		if (key == node->key_arr[i]) {
			printf("Search Success : %d\n", key);
			return true;
		}
		if (key < node->key_arr[i]) {
			break;
		}
	}
	if (node->child_len > 0) {
		result = Search(node->child_arr[i], key);
	}
	else {
		printf("Search Failed %d\n", key);
	}
	return result;
}

// Find x node's predecessor child
int Pred(struct Node* child_x) {
	int result = -1;
	if (!child_x->leaf) {
		result = Pred(child_x->child_arr[child_x->child_len - 1]);
	}
	else {
		return result = child_x->key_arr[child_x->key_len - 1];
	}
	return result;
}

// Find x node's successor child
int Succ(struct Node* child_x) {
	int result = -1;
	if (!child_x->leaf) {
		result = Succ(child_x->child_arr[0]);
	}
	else {
		return result = child_x->key_arr[0];
	}
	return result;
}

void merge(struct Node* x, int idx) {
	struct Node* y = x->child_arr[idx];
	struct Node* z = x->child_arr[idx + 1];

	// 1. Move all z node's keys and children to y node.
	for (int i = 0; i < z->key_len; i++) {
		y->key_arr[y->key_len + i] = z->key_arr[i];
	}	
	for (int i = 0; i < z->child_len; i++) {
		y->child_arr[y->child_len + i] = z->child_arr[i];
	}

	y->child_len = (2 * min_degree) - 1;
	y->key_len = (2 * min_degree) - 2;

	// 2. Add count number of z node's keys and children to y node.
	for (int i = idx; i < x->key_len; i++) {
		x->key_arr[i] = x->key_arr[i + 1];
	}
	x->key_len--;

	for (int i = idx + 1; i < x->child_len - 1; i++) {
		x->child_arr[i] = x->child_arr[i + 1];
	}
	x->child_len--;

	// 3. Free z node
	free_node(z);
}

bool Change_Root(struct B_tree* tree, struct Node* x) {
	bool result = false;
	if (x->key_len == 0) {
		printf("Root Changed\n");
		tree->root = x->child_arr[0];
		
		// Free original root
		free_node(x);
		result = true;
		return result;
	}
	printf("Root_not Changed\n");
	return result;
}

void Borrow_Left(struct Node* x, int idx) {
	struct Node* y = x->child_arr[idx - 1];
	struct Node* z = x->child_arr[idx];

	// 1. Make z node's extra space(Z[0]) for X[idx]
	for (int i = 0; i < z->key_len; i++) {
		z->key_arr[z->key_len - i] = z->key_arr[z->key_len - i - 1];
	}
	for (int i = 0; i < z->child_len; i++) {
		z->child_arr[z->child_len - i] = z->child_arr[z->child_len - i - 1];
	}
	z->key_len++;
	if(!z->leaf) z->child_len++;

	// 2. Rotate keys (y[-1] - > x[idx] -> z[0] )
	z->key_arr[0] = x->key_arr[idx - 1];
	z->child_arr[0] = y->child_arr[y->child_len - 1];
	x->key_arr[idx - 1] = y->key_arr[y->key_len - 1];	
	y->key_len--;
	y->child_len--;
}

void Borrow_Right(struct Node* x, int idx) {
	struct Node* y = x->child_arr[idx];
	struct Node* z = x->child_arr[idx + 1];

	// 1. Make y node's extra space(z[-1]) for x[idx]
	y->key_arr[y->key_len] = x->key_arr[idx];
	y->child_arr[y->child_len] = z->child_arr[0];
	y->key_len++;
	if(!y->leaf) y->child_len++;

	// 2. Rotate keys (y[-1] < x[idx] < z[0] )
	x->key_arr[idx] = z->key_arr[0];

	for (int i = 0; i < z->key_len - 1; i++) {
		z->key_arr[i] = z->key_arr[i + 1];
	}
	for (int i = 0; i < z->child_len - 1; i++) {
		z->child_arr[i] = z->child_arr[i + 1];
	}
	z->key_len--;
	if(!z->leaf) z->child_len--;
}

void Delete_key(struct B_tree* tree, struct Node* x, int key) {
	
	int idx = 0; // idx of child

	for (; idx < x->key_len; idx++) {
		if (key <= x->key_arr[idx]) {
			break;
		}
	}
	int key_idx = idx;
	if (key_idx == x->key_len) {
		key_idx--;
	}

	if (key == x->key_arr[key_idx]) {
		// case 1
		if (x->leaf) {
			printf("case 1\n");
			for (int i = idx; i < x->key_len - 1; i++) {
				x->key_arr[i] = x->key_arr[i + 1];
			}
			x->key_len--;
			x->child_len--;

			return;
		}
		// case 2
		else {
			// case 2 - A
			if (x->child_arr[idx]->key_len > min_degree - 1) {				
				int k_prime = Pred(x->child_arr[idx]);
				Delete_key(tree, x->child_arr[idx], k_prime);
				x->key_arr[idx] = k_prime;
				return;

				// case 2 - B
			}
			else if (x->child_arr[idx + 1]->key_len > min_degree - 1) {				
				int k_prime = Succ(x->child_arr[idx + 1]);
				Delete_key(tree, x->child_arr[idx + 1], k_prime);
				x->key_arr[idx] = k_prime;
				return;
			}
			else {
				// case 2 - C				
				merge(x, idx);
				Change_Root(tree, x);
				return;
			}
		}
	}
	// case 3
	else {
		if (x->child_arr[idx]->key_len > min_degree - 1) {			
			Delete_key(tree, x->child_arr[idx], key);
			return;
		}
		else {
			// case 3-A-1
			if (idx != 0 && x->child_arr[idx - 1]->key_len > min_degree - 1) {				

				Borrow_Left(x, idx);
				Delete_key(tree, x, key);
				return;
			}
			// case 3-A-2
			else if (idx != x->child_len - 1 && x->child_arr[idx + 1]->key_len > min_degree - 1) {				

				Borrow_Right(x, idx);
				Delete_key(tree, x, key);
				return;
			}
			// case 3-B
			else {
				
				struct Node* y = x->child_arr[key_idx];
				struct Node* z = x->child_arr[key_idx + 1];				

				// Merge all x, y, z node's keys and children into y node
				
				y->key_arr[y->key_len] = x->key_arr[key_idx];
				y->key_len++;

				for (int i = 0; i < z->key_len; i++) {					
					y->key_arr[y->key_len] = z->key_arr[i];
					y->key_len++;
				}

				for (int i = 0; i < z->child_len; i++)
				{
					printf("z %d\n", z->key_arr[i]);
				}
				printf("z len2 %d\n", z->child_len);

				for (int i = 0; i < z->child_len; i++) {
					y->child_arr[y->child_len] = z->child_arr[i];
					if (!y->leaf) { y->child_len++; }
				}				
				// Free z node
				free_node(z);

				// Rearrange x node's key and children
				for (int i = key_idx; i < x->key_len - 1; i++) {
					x->key_arr[i] = x->key_arr[i + 1];
				}
				x->key_len--;

				for (int i = key_idx + 1; i < x->child_len - 1; i++) {
					x->child_arr[i] = x->child_arr[i + 1];
				}
				x->child_len--;

				// Check root and start deletion
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