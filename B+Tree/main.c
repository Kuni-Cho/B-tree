#include "function_set.h"
#include<time.h>
int main() {
	//// 1. Input Min_degree
	//printf("*****************\n");
	//printf("** Enter the min_degree ** ");
	//scanf_s("%d", &min_degree);
	printf("** Enter the number of index ** ");
	scanf_s("%d", &size);
	//printf("\n** Init Tree ** \n");

	// 2. Create Tree
	struct BP_tree BP_tree = CreateTree();

	//// 3. Create Node in Tree
	//for (int i = 1; i <= size; i++) {
	//	InsertKey(&BP_tree, i);
	//}
	//printf("*****************\n");
	//Visual(BP_tree.root, 0);
	//Visual_head(&BP_tree);

	// 4. Create Test Case
	int* out_arr = (int*)malloc(sizeof(int) * size);

	/*for (int i = 0; i < size; i++) {
		out_arr[i] = size - i;
	}*/
	//for (int i = 0; i < size; i++) {
	//	out_arr[i] = i + 1;
	//}
	for (int i = 0; i < size; i++) {
		//296
		srand(i * 100);
		int r = rand() % 1000;
		InsertKey(&BP_tree, r);
		out_arr[i] = r;
	}
	printf("*****************\n");
	Visual(BP_tree.root, 0);
	Visual_head(&BP_tree);

	// 5. create database
	database = (int*)malloc(sizeof(int) * size);
	printf("db\n");
	for (int i = 0; i < size; i++) {
		database[i] = -i - 1;
		printf("%d ", database[i]);
	}
	printf("\n");

	// 5. Start Test
	for (int i = 0; i < size; i++) {
		printf("*****************\n");
		bool result = Search(BP_tree.root, out_arr[i]);
		if (result) {
			printf("Target to Delete : %d\n", out_arr[i]);
			printf("*****************\n");
			Delete_key(&BP_tree, BP_tree.root, out_arr[i]);
			//Visual(BP_tree.root, 0);
			Visual_head(&BP_tree);
			printf("\n\n");
		}
		else {
			printf("Target Not Found, Target is : %d\n\n", out_arr[i]);
		}
	}
	for (int i = 0; i < size; i++)
	{
		printf("%d ", out_arr[i]);
	}
	free(out_arr);
	return 0;
}