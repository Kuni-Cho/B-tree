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


// true / false는 삼항연산자로 구분하거나, 0/1로 확인할 것.
// 배열의 각 인덱스 값을 초기화할때는, 애스터리스크 붙일 것.