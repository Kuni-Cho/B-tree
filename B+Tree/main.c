#include "function_set.h"

int main() {
	size = 100;

	// 2. Create Tree
	struct BP_tree BP_tree = CreateTree();

	//// 3. Create Node in Tree
	for (int i = 1; i <= size; i++) {
		InsertKey(&BP_tree, i);
	}
	printf("*****************\n");
	Visual(BP_tree.root, 0);
	Visual_head(&BP_tree);

	// 4. Create Test Case
	int* out_arr = (int*)malloc(sizeof(int) * size);

	for (int i = 0; i < size; i++) {
		out_arr[i] = size - i;
	}
	//for (int i = 0; i < size; i++) {
	//	out_arr[i] = i + 1;
	//}

	// 5. create database
	database = (int*)malloc(sizeof(int) * size);

	for (int i = 0; i < size; i++) {
		printf("*****************\n");
		bool result = Search(BP_tree.root, out_arr[i]);
		if (result) {
			printf("Target to Delete : %d\n", out_arr[i]);
			printf("*****************\n");
			Delete_key(&BP_tree, BP_tree.root, out_arr[i]);
			Visual(BP_tree.root, 0);
			Visual_head(&BP_tree);
			printf("\n\n");
		}
		else {
			printf("Target Not Found, Target is : %d\n\n", out_arr[i]);
		}
	}
	//free(out_arr);
	return 0;
}