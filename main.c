#include "function_set.h"
#include <time.h>
int main()
{
	// 1. Input Min_degree
	printf("*****************\n");
	printf("** Enter the min_degree ** ");
	scanf_s("%d", &min_degree);
	printf("** Enter the number of index ** ");
	scanf_s("%d", &size);
	printf("\n** Init Tree ** \n");

	// 2. Create Tree
	struct BP_tree BP_tree = CreateTree();

	int *out_arr = (int *)malloc(sizeof(int) * size);
	for (int i = 0; i < size; i++)
	{
		out_arr[i] = i;
	}
	for (int i = 0; i < size; i++)
	{
		int j = i + rand() / (RAND_MAX / (size - i) + 1);
		int t = out_arr[j];
		out_arr[j] = out_arr[i];
		out_arr[i] = t;
	}
	for (int i = 0; i < size; i++)
	{
		int r = out_arr[i];
		InsertKey(&BP_tree, r);
	}

	Visual(BP_tree.root, 0);
	Visual_head(&BP_tree);

	// 5. create database
	database = (int *)malloc(sizeof(int) * size);
	for (int i = 0; i < size; i++)
	{
		database[i] = -i - 1;
	}

	// 5. Start Test
	for (int i = 0; i < size; i++)
	{
		bool result = Search(BP_tree.root, out_arr[i]);
		if (result)
		{
			Delete_key(&BP_tree, BP_tree.root, out_arr[i]);
		}
	}
	Visual_head(&BP_tree);

	free(out_arr);
	return 0;
}