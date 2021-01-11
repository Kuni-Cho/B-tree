#include "function_set.h"

int main() {
	min_degree = 2;
	struct B_tree* B_Tree = CreateTree(2);

	for (int i = 0; i < 20; i++) {
		InsertKey(B_Tree, i);
	}

	InsertKey(B_Tree, 30);
	Visual(B_Tree->root, 0);

	////int out_arr[10] = {0, 1, 20, 30, 100 };
	int out_arr[20];
	for (int i = 0; i < 20; i++) {
		out_arr[i] = 20 - 1 - i;
	}

	for (int i = 0; i < 20; i++) {
		bool result = Search(B_Tree->root, out_arr[i]);
		if (result) {
			printf("������ ��ȣ : %d\n\n", out_arr[i]);
			Delete_key(B_Tree, B_Tree->root, out_arr[i]);
			printf("\n");
			Visual(B_Tree->root, 0);
			printf("\n\n");
		}
		else {
			printf("ã�� ���� �����ϴ� Key : %d\n\n", out_arr[i]);
		}
	}

	return 0;
}