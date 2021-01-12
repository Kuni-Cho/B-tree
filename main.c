#include "function_set.h"

int main() {

	// 1. Input Min_degree
	min_degree = 2;

	// 2. Create Tree
	struct B_tree B_Tree = CreateTree();

	// 3. Create Node in Tree
	int size = 100;
	for (int i = 0; i < size; i++) {
		InsertKey(&B_Tree, i);
	}
	Visual(B_Tree.root, 0);

	// 4. Create Test Case
	int out_arr[100];
	for (int i = 0; i < size; i++) {
		out_arr[i] = size - 1 - i;
	}

	// 5. Start Test
	for (int i = 0; i < size; i++) {
		bool result = Search(B_Tree.root, out_arr[i]);
		if (result) {
			printf("Target to Delete : %d\n\n", out_arr[i]);
			Delete_key(&B_Tree, B_Tree.root, out_arr[i]);
			printf("\n");
			Visual(B_Tree.root, 0);
			printf("\n\n");
		}
		else {
			printf("Target Not Found, Target is : %d\n\n", out_arr[i]);
		}
	}

	return 0;
}