class Node {

public:
	double value;
	Node* next;
	Node(double v, Node* n);
	Node();

};

class Poly {

public:

	Node* getHead();
	void nextHead(); //Testing
	int length(); //Testing
	Node* head;
	Poly();
	~Poly();
	void print();
	void append(double v);
};
