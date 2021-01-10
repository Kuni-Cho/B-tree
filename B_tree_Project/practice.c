//
//struct Node* CreateNode(int min_degree) {
//
//	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
//	newNode->leaf = false;
//	newNode->key_len = 0;
//	newNode->child_len = 0;
//	newNode->key_arr = (int*)malloc(sizeof(int) * (2 * min_degree - 1));
//	newNode->child_arr = (struct Node*)malloc(sizeof(struct Node) * (2 * min_degree));
//
//	return newNode;
//};