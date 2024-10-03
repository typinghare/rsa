#include <gmpxx.h>
#include <iostream>
#include "rsa.hpp"

int main() {
    constexpr int key_size = 2048;
    constexpr int prime_size = key_size / 2;

    const mpz_class p = generate_prime(prime_size);
    const mpz_class q = generate_prime(prime_size);

    std::cout << "Prime p: " << p.get_str() << std::endl;
    std::cout << "Prime q: " << q.get_str() << std::endl;

    return 0;
}
