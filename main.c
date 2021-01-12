#include "function_set.h"

int main() {
	// 1. Input Min_degree
	printf("*****************\n");
	printf("** Enter the min_degree ** ");
	scanf_s("%d", &min_degree);
	printf("** Enter the number of index ** ");
	scanf_s("%d", &size);
	printf("\n** Init Tree ** \n");

	// 2. Create Tree
	struct B_tree B_Tree = CreateTree();

	// 3. Create Node in Tree
	for (int i = 0; i < size; i++) {
		InsertKey(&B_Tree, i);
	}
	printf("*****************\n");
	Visual(B_Tree.root, 0);
	printf("\n");

	// 4. Create Test Case
	int* out_arr = (int*)malloc(sizeof(int) * size);

	for (int i = 0; i < size; i++) {
		out_arr[i] = size - 1 - i;
	}

	// 5. Start Test
	for (int i = 0; i < size; i++) {
		printf("*****************\n");
		bool result = Search(B_Tree.root, out_arr[i]);
		if (result) {
			printf("Target to Delete : %d\n", out_arr[i]);
			printf("*****************\n");
			Delete_key(&B_Tree, B_Tree.root, out_arr[i]);
			Visual(B_Tree.root, 0);
			printf("\n\n");
		}
		else {
			printf("Target Not Found, Target is : %d\n\n", out_arr[i]);
		}
	}
	free(out_arr);

	return 0;
}