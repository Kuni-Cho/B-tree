#include "function_set.h"

struct test {
	int a, b;
};


int main() {
	struct B_tree* B_Tree = CreateTree(2);
	InsertKey(B_Tree, 10);

	printf("%d, %d", B_Tree->root->key_arr[0], B_Tree->root->key_len);

	return 0;
}


// true / false�� ���׿����ڷ� �����ϰų�, 0/1�� Ȯ���� ��.
// �迭�� �� �ε��� ���� �ʱ�ȭ�Ҷ���, �ֽ��͸���ũ ���� ��.