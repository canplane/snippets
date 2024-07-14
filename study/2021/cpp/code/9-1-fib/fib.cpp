#include <iostream>

template <int N>
struct fib {
    static const int result = fib<N - 1>::result + fib<N - 2>::result;
};
template <>
struct fib<1> { 
    static const int result = 1;
};
template <>
struct fib<2> {
    static const int result = 1;
};

int main() {
    std::cout << "5 번째 피보나치 수 :: " << fib<5>::result << std::endl;  // 5
}