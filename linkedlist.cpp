#include <stdio.h>

class LinkedList {

private:
	struct Node {
		int value;
		Node *next;
	};

	Node *head;	//points to first node
	int pos;

public:
	LinkedList() {	//constructor
		head = nullptr;
		pos = 0;
	}
	~LinkedList() { //destructor
		Node *current = head;
		Node *nextptr = nullptr;
		while (current != nullptr) {
			nextptr = current;
			current = current->next;
			delete nextptr;
		}
		nextptr = nullptr;
		current = nullptr;
	}

	Node* getHead() {
		return head;
	}

	//checked
	void addToListAtPosition(int position, int value) {
		Node *temp = new Node;
		temp->value = value;

		Node *cur, *prev;
		int counter = 0;

		//if position greater than length
		if (position > getListLength()) {
			//printf("over length\n");
			return;
		}

		if (position == 0) {
			temp->value = value;
			temp->next = head;
			head = temp;
			return;
		}

		pos = 0;
		for (counter = 0, cur = head, prev = nullptr; cur != nullptr && counter < position; pos++, prev = cur, cur = cur->next, counter++);
		prev->next = temp;
		temp->next = cur;
		int check = pos;
	}

	//checked
	void addToHead(int value) {
		Node *temp = new Node;
		temp->value = value;
		temp->next = head;
		head = temp;
	}

	//checked
	void appendToList(int value) {
		Node *tail = new Node;
		tail->value = value;

		Node *cur = head;
		Node *prev = nullptr;

		//if nothing in list
		if (cur == nullptr) {
			head = tail;
			head->next = nullptr;
			return;
		}

		for (; cur != nullptr; prev = cur, cur = cur->next);
		prev->next = tail;
		tail->next = nullptr;
	}

	//checked
	void removeFromListAtPosition(int position) {
		Node *cur = head;
		Node *prev = nullptr;
		int counter = 0;
		for (counter = 0; cur != nullptr && counter < position; prev = cur, cur = cur->next, counter++);

		//if greater than length
		if (cur == nullptr) {
			//printf("overlength\n");
			return;
		}

		//if removing first position
		if (position == 0) {
			head = cur->next;
			delete cur;
			return;
		}

		//if removing last position
		if (cur->next == nullptr) {
			prev->next = nullptr;
		}
		else {
			prev->next = cur->next;
		}
		delete cur;
	}

	//checked
	void removeFromHead() {
		Node *temp = head;

		//if list empty
		if (temp == nullptr) {
			//printf("Empty list\n");
			return;
		}
		head = head->next;
		delete temp;
	}

	//checked
	void removeFromEnd() {
		Node *cur = head;
		Node *prev = nullptr;

		//if list empty
		if (cur == nullptr) {
			//printf("Empty list\n");
			return;
		}
		Node *forward = head->next;

		//if only one node
		if (forward == nullptr) {
			head = head->next;
			delete cur;
			return;
		}

		//greater than one node
		for (; forward != nullptr; forward = forward->next, prev = cur, cur = cur->next);
		prev->next = nullptr;
		delete cur;
	}

	//checked
	bool find(int value) {
		Node *temp;
		for (temp = head; temp != nullptr; temp = temp->next) {
			if (temp->value == value) {
				return true;
			}
		}
		return false;
	}

	//checked
	void reverseList() {

		//if empty list 
		if (head == nullptr) {
			//printf("Empty list\n");
			return;
		}

		//if one node 
		if (head->next == nullptr) {
			//printf("One node\n");
			return;
		}
		Node *tail = head;
		Node *cur = tail->next;
		Node *front = cur->next;

		tail->next = nullptr;

		//if only 2 nodes
		if (front == nullptr) {
			head = cur;
			cur->next = tail;
			return;
		}

		while (front != nullptr) {
			cur->next = tail;
			tail = cur;
			cur = front;
			front = front->next;
		}
		cur->next = tail;
		head = cur;
	}

	//checked
	int getListLength() {
		Node *list = head;
		int length = 0;
		while (list != nullptr) {
			length++;
			list = list->next;
		}
		return length;
	}
};