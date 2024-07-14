#include <iostream>
#include <typeinfo>

int sum(int a, int b) { return a + b; }

class SomeClass {
    int data;

public:
    SomeClass(int d) : data(d) {}
    SomeClass(const SomeClass& s) : data(s.data) {}
};

int main() {
    auto c = sum(1, 2);  // 함수 리턴 타입으로부터 int라고 추측 가능
    auto num = 1.0 + 2.0;  // double로 추측 가능!

    SomeClass some(10);
    auto some2 = some;

    auto some3(10);  // SomeClass 객체를 만들끼요? -> int를 만든다.

    std::cout << "c의 타입은? :: " << typeid(c).name() << std::endl;  // i
    std::cout << "num의 타입은? :: " << typeid(num).name() << std::endl;  // d
    std::cout << "some2의 타입은? :: " << typeid(some2).name() << std::endl;  // 9SomeClass
    std::cout << "some3의 타입은? :: " << typeid(some3).name() << std::endl;  // i
}