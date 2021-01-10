#include "function_set.h"
int front = -1;
int rear = -1;
int queue[MAX];
int IsEmpty(void) {
    if (front == rear)//front�� rear�� ������ ť�� ����ִ� ����
        return true;
    else return false;
}
int IsFull(void) {
    int tmp = (rear + 1) % MAX; //���� ť���� rear+1�� MAX�� ���� ����������
    if (tmp == front)//front�� ������ ť�� ������ �ִ� ����
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