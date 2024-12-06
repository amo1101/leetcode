#include <stdlib.h>
#include <time.h>
#include <vector>
#include <stack>
#include <queue>
#include <unordered_map>
#include <algorithm>

using namespace std;

class CircularQueue {
public:
	CircularQueue(int k) : head(-1), tail(-1), size(k) {
		data.resize(k);
	}
	bool enQueue(int value);
	bool deQueue();
	int front();
	int rear();
	bool isEmpty();
	bool isFull();

private:
	vector<int> data;
	int head;
	int tail;
	int size;
};

bool CircularQueue::enQueue(int value) {
	if (isFull()) {
		return false;
	}

	if (isEmpty()) {
		head = 0;
	}
	
	tail = (tail + 1) % size;
	data[tail] = value;
	return true;
}

bool CircularQueue::deQueue() {
	if (isEmpty()) {
		return true;
	}

	if (head == tail) {
		head = -1;
		tail = -1;
		return true;
	}

	head = (head + 1) % size;
	return true;
}

int CircularQueue::front() {
	if (isEmpty()) {
		return -1;
	}

	return data[head];
}

int CircularQueue::rear() {
	if (isEmpty()) {
		return false;
	}

	return data[tail];
}

bool CircularQueue::isEmpty() {
	return head == -1;
}

bool CircularQueue::isFull() {
	return (tail + 1) % size == head;
}



void testQueue() {

}