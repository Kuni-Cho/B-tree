#include "function_set.h"
int front = -1;
int rear = -1;
int queue[MAX];
int IsEmpty(void) {
	if (front == rear)//front와 rear가 같으면 큐는 비어있는 상태
		return true;
	else return false;
}
int IsFull(void) {
	int tmp = (rear + 1) % MAX; //원형 큐에서 rear+1을 MAX로 나눈 나머지값이
	if (tmp == front)//front와 같으면 큐는 가득차 있는 상태
		return true;
	else
		return false;
}
void addq(int value) {
	if (IsFull())
		printf("Queue is Full.\n");
	else {
		rear = (rear + 1) % MAX;
		queue[rear] = value;
	}
}
int deleteq() {
	if (IsEmpty())
		printf("Queue is Empty.\n");
	else {
		front = (front + 1) % MAX;
		return queue[front];
	}
}

//addq(4);
//addq(7);
//addq(12);
//printf("%d\n", deleteq());
//printf("%d\n", deleteq());
//printf("%d\n", deleteq());
//deleteq();