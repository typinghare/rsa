#include <iostream>
#include "rsa_infant.hpp"

int main() {
    const auto [public_key, private_key] = generate_pairs();
    std::cout << "[PUBLIC] public key: (" << public_key.n << ", "
              << public_key.e << ")" << std::endl;
    std::cout << "[SECRET] private key: (" << private_key.n << ", "
              << private_key.d << ")" << std::endl;

    constexpr unsigned plaintext = 114514;
    std::cout << "[SECRET] plaintext: " << plaintext << std::endl;

    const unsigned ciphertext = encrypt(public_key, plaintext);
    std::cout << "[PUBLIC] ciphertext: " << ciphertext << std::endl;
    std::cout << "[SECRET] decrypted plaintext: "
              << decrypt(private_key, ciphertext) << std::endl;

    return 0;
}
