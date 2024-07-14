#include <iostream>

class A {
	int i;

	public:
		A(int i) : i(i + 5) {}
		void print() { std::cout << i << std::endl; }
};

int main() {
	A a = 5;
	a.print();
	return 0;
}
