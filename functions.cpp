#include "functions.hh"

/*int getLength(Poly p3) {
	Node* list = p3.getHead();
	int length = 0;
	while (list != nullptr) {
		length++;
		list = list->next;
	}
	return length;
}*/

void addToPosition(Poly p3, int position, int value) {
	Node *temp, *cur;
	int counter = 0;

	for (counter = 0, cur = p3.getHead(); cur != nullptr && counter < position; cur = cur->next, counter++);
	cur->value += value;
}

Poly addPolynomials(Poly p1, Poly p2) {
	Poly p;
	Node* temp1;
	Node* temp2;
	int pos1 = 0;
	int pos2 = 0;

	temp1 = p1.getHead();
	temp2 = p2.getHead();

	//p1 length
	pos1 = p1.length();
	//p2 length
	pos2 = p2.length();

	while (pos1 != 0 && pos2 != 0) {
		if (pos1 > pos2) {
			p.append(temp1->value);
			temp1 = temp1->next;
			pos1--;
		}
		if (pos2 > pos1) {
			p.append(temp2->value);
			temp2 = temp2->next;
			pos2--;
		}
		if (pos1 == pos2) {
			p.append(temp1->value + temp2->value);
			temp1 = temp1->next;
			temp2 = temp2->next;
			pos1--;
			pos2--;
		}
	}
	return p;
}

Poly subtractPolynomials(Poly p1, Poly p2) {
	Poly p;
	Node* temp1;
	Node* temp2;
	int pos1 = 0;
	int pos2 = 0;

	temp1 = p1.getHead();
	temp2 = p2.getHead();

	//p1 length
	pos1 = p1.length();
	//p2 length
	pos2 = p2.length();

	while (pos1 != 0 && pos2 != 0) {
		if (pos1 > pos2) {
			p.append(temp1->value);
			temp1 = temp1->next;
			pos1--;
		}
		if (pos2 > pos1) {
			p.append(temp2->value);
			temp2 = temp2->next;
			pos2--;
		}
		if (pos1 == pos2) {
			p.append(temp1->value - temp2->value);
			temp1 = temp1->next;
			temp2 = temp2->next;
			pos1--;
			pos2--;
		}
	}

	//Check zero head Testing
	Node* temp = p.getHead();
	Node* tempnext = p.getHead()->next;
	while (temp->value == 0 && tempnext != nullptr) {
		p.nextHead();
		delete temp;
		temp = tempnext;
		tempnext = tempnext->next;
	}
	if (temp->value == 0) {
		p.nextHead();
		delete temp;
	}
	return p;
}

Poly multiplyPolynomials(Poly p1, Poly p2) {
	Poly p;
	Node* temp1;
	Node* temp2;
	int pos1 = 0;
	int pos2 = 0;
	int pos = 0;
	int value = 0;
	int index = 0;
	int counter = 0;

	temp1 = p1.getHead();
	temp2 = p2.getHead();

	//p1 length
	pos1 = p1.length();
	//p2 length
	pos2 = p2.length();

	//get total positions
	pos = pos1 + pos2 - 1;

	//set template
	while (pos > 0) {
		p.append(0);
		pos--;
	}

	//loop through 
	while (temp1 != nullptr) {
		while (temp2 != nullptr) {
			value = temp1->value * temp2->value;
			addToPosition(p, index, value);
			temp2 = temp2->next;
			index++;
		}
		counter++;
		index = counter;
		temp1 = temp1->next;
		temp2 = p2.getHead();
	}
	return p;
}

