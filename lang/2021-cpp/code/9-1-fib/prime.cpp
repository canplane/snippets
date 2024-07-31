#include <iostream>

template <int N, int D>
struct _is_prime {
    static const bool result = (N % D) && _is_prime<N, D - 1>::result;
};
template <int N>
struct _is_prime<N, 2> {
    static const bool result = (N % 2);
};

template <int N>
struct is_prime {
    static const bool result = _is_prime<N, N / 2>::result;
};
template <>
struct is_prime<2> {
    static const bool result = true;
};
template <>
struct is_prime<3> {
    static const bool result = true;
};

int main() {
    std::cout << std::boolalpha;
    std::cout << "Is prime ? :: " << is_prime<2>::result << std::endl;  // true
    std::cout << "Is prime ? :: " << is_prime<2049>::result << std::endl;  // false

    std::cout << "Is prime ? :: " << is_prime<2000>::result << std::endl;  // true
    std::cout << "Is prime ? :: " << is_prime<2000>::result << std::endl;  // true
}