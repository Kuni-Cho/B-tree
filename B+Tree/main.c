#include "function_set.h"
#include<time.h>
int main() {
	// 1. Input Min_degree
	printf("*****************\n");
	printf("** Enter the min_degree ** ");
	scanf_s("%d", &min_degree);
	printf("** Enter the number of index ** ");
	scanf_s("%d", &size);
	printf("\n** Init Tree ** \n");

	// 2. Create Tree
	struct BP_tree BP_tree = CreateTree();

	//// 3. Create Node in Tree
	/*for (int i = 1; i <= size; i++) {
		InsertKey(&BP_tree, i);
	}*/
	//printf("*****************\n");
	//Visual(BP_tree.root, 0);
	//Visual_head(&BP_tree);

	//4. Create Test Case
	int* out_arr = (int*)malloc(sizeof(int) * size);
	for (int i = 0; i < size; i++) {
		out_arr[i] = i;
	}
	for (int i = 0; i < size; i++)
	{
		int j = i + rand() / (RAND_MAX / (size - i) + 1);
		int t = out_arr[j];
		out_arr[j] = out_arr[i];
		out_arr[i] = t;
	}
	for (int i = 0; i < size; i++) {
		int r = out_arr[i];
		InsertKey(&BP_tree, r);
	}
	/*for (int i = 0; i < size; i++) {
		out_arr[i] = size - i;
	}*/
	//for (int i = 0; i < size; i++) {
	//	out_arr[i] = i + 1;
	//}
	//for (int i = 0; i < size; i++) {
	//	srand(i * 77);
	//	int r = rand() % 1000;
	//	InsertKey(&BP_tree, r);
	//	out_arr[i] = r;
	//}

	printf("*****************\n");
	Visual(BP_tree.root, 0);
	Visual_head(&BP_tree);
	/*size = 10;
	int out_arr[10] = { 38, 365, 691, 18, 344, 671, 997, 324, 651, 977 };*/
	printf("out_Arr: ");
	for (int i = 0; i < size; i++)
	{
		printf("%d ", out_arr[i]);
	}
	printf("\n");
	/*for (int i = 0; i < size; i++) {
		InsertKey(&BP_tree, out_arr[i]);
	}*/

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
			//Visual_head(&BP_tree);
			printf("\n\n");
		}
		else {
			printf("Target Not Found, Target is : %d\n\n", out_arr[i]);
		}
	}
	Visual_head(&BP_tree);

	free(out_arr);
	printf("Finish");
	return 0;
}