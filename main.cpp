#include "functions.hh"
#include <stdio.h>
#include <cassert>


void test00() {
	Poly p1;
	Poly p2;
	p1.append(1);
	p1.append(2);
	p2.append(3);

	Poly result = addPolynomials(p1, p2);
	assert(result.getHead()->value == 1);
	assert(result.getHead()->next->value == 5);
	printf("Test00 passed!\n");
}

void test01() {
	Poly p1;
	Poly p2;
	p1.append(1);
	p1.append(2);
	p2.append(3);

	Poly result = subtractPolynomials(p1, p2);
	assert(result.getHead()->value == 1);
	assert(result.getHead()->next->value == -1);
	printf("Test01 passed!\n");

	/*//Testing
	Poly p1;
	Poly p2;
	p1.append(3);
	p1.append(2);
	p1.append(1);
	//p1.append(5);
	//p1.append(6);
	//p1.append(7);
	//p2.append(3);
	p2.append(3);
	p2.append(0);
	p2.append(1);
	//p2.append(4);
	Poly result = multiplyPolynomials(p1, p2);
	result.print();
	//assert(result.getHead()->value == 1);
	//assert(result.getHead()->next->value == -1);
	//printf("Test01 passed!\n");*/
}

void test02() {
	Poly p1;
	Poly p2;
	p1.append(1);
	p1.append(2);
	p2.append(3);

	Poly result = multiplyPolynomials(p1, p2);
	assert(result.getHead()->value == 3);
	assert(result.getHead()->next->value == 6);
	printf("Test02 passed!\n");
}

void test03() {
	Poly p1;
	Poly p2;
	p1.append(1);
	p2.append(1);
	Poly result = addPolynomials(p1, p2);
	assert(result.getHead()->value == 2);
	Poly p3;
	p3.append(2);
	result = addPolynomials(p1, p3);
	assert(result.getHead()->value == 3);
	printf("Test03 passed!\n");
}

int main() {
	test00();
	test01();
	test02();
	test03();
}