#include "function_set.h"

int main() {
	min_degree = 2;
	struct B_tree* B_Tree = CreateTree(2);
	InsertKey(B_Tree, 10);
	printf("%d ", 10);
	InsertKey(B_Tree, 11);
	printf("%d ", 11);
	InsertKey(B_Tree, 12);
	printf("%d ", 12);
	InsertKey(B_Tree, 13);
	printf("%d ", 13);
	InsertKey(B_Tree, 14);
	printf("%d ", 14);
	InsertKey(B_Tree, 15);
	printf("%d ", 15);
	InsertKey(B_Tree, 16);
	printf("%d ", 16);
	printf("\n");

	printf("%d, %d", B_Tree->root->key_arr[0], B_Tree->root->key_len);
	printf("\n");

	/*struct Node* Node1 = CreateNode();
	for (int i = 0; i < 2 * min_degree; i++)
	{
		struct Node* Node1 = CreateNode();
		Node1->child_arr[i]
	}*/

	Visual(B_Tree);

	return 0;
}

// true / false�� ���׿����ڷ� �����ϰų�, 0/1�� Ȯ���� ��.
// �迭�� �� �ε��� ���� �ʱ�ȭ�Ҷ���, �ֽ��͸���ũ ���� ��.