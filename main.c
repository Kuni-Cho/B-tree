#include "function_set.h"

int main() {
	min_degree = 2;
	struct B_tree* B_Tree = CreateTree(2);

	for (int i = 0; i < 100; i++) {
		InsertKey(B_Tree, i);
	}

	Visual(B_Tree->root, 0);

	/*int out_arr[10] = {0, 1, 20, 30, 100 };*/
	int out_arr[100];
	for (int i = 0; i < 100; i++) {
		out_arr[i] = 100 - 1 - i;
	}

	//for (int i = 0; i < 100; i++) {
	//	out_arr[i] = i;
	//}

	for (int i = 0; i < 100; i++) {
		bool result = Search(B_Tree->root, out_arr[i]);
		if (result) {
			printf("삭제할 번호 : %d\n\n", out_arr[i]);
			Delete_key(B_Tree, B_Tree->root, out_arr[i]);
			printf("\n");
			//Visual(B_Tree->root, 0);
			printf("\n\n");
		}
		else {
			printf("찾는 값이 없습니다 Key : %d\n\n", out_arr[i]);
		}
	}

	return 0;
}