#include "polynomial.hh"
#include <stdio.h>

Node::Node(double v, Node* n) {
	value = v;
	next = n;
}

Node::Node() {
	value = 0;
	next = nullptr;
}

Node* Poly::getHead() {
	return head;
}

//Testing
void Poly::nextHead() {
	head = head->next;
}

//Testing
int Poly::length() {
	Node* list = getHead();
	int length = 0;
	while (list != nullptr) {
		length++;
		list = list->next;
	}
	return length;
}

Poly::Poly() {
	head = nullptr;
}

Poly::~Poly() {
	/*Node *current = head;
	Node *prevptr = nullptr;
	while (current != nullptr) {
		prevptr = current;
		current = current->next;
		delete prevptr;
	}
	prevptr = nullptr;
	current = nullptr;*/
}

void Poly::append(double v) {

	Node* tail = new Node(v, nullptr);
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

void Poly::print() {
	Node* temp = getHead();
	while (temp != 0) {
		printf("%.2f", temp->value);
		temp = temp->next;
	}
}