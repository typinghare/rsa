#ifndef RSA_INFANT_HPP
#define RSA_INFANT_HPP

#include <cmath>
#include <random>

/**
 * @brief Checks if a given unsigned integer is a prime number.
 *
 * A prime number is defined as a natural number greater than 1 that has no
 * positive divisors other than 1 and itself. This function uses trial division
 * up to the square root of the number to determine primality.
 *
 * @param n The unsigned integer to check for primality.
 * @return true if n is prime; false otherwise.
 */
inline bool is_prime(const long n) {
    if (n < 2) {
        return false;
    }
    if (n == 2) {
        return true;
    }
    if (n % 2 == 0) {
        return false;
    }

    const auto sqrt_n = std::ceil(std::sqrt(n));
    for (unsigned i = 3; i <= sqrt_n; i += 2) {
        if (n % i == 0) {
            return false;
        }
    }

    return true;
}

/**
 * @brief The result of the extended_gcd function.
 */
struct extended_gcd_r {
    long gcd;  // The greatest common divisor
    long x;  // Coefficient for the first number
    long y;  // Coefficient for the second number
};

/**
 * @brief Finds the greatest common divisor of two whole numbers.
 *
 * This functions uses Extended Euclidean Algorithm to find the greatest common
 * divisor of the two whole numbers. Note that one of the numbers must be
 * positive.
 *
 * @param p The first whole numbers.
 * @param q The second whole numbers.
 * @return The greatest common divisor of two positive integers and
 * coefficients.
 */
inline extended_gcd_r
extended_gcd(const long p, const long q) {  // NOLINT(*-no-recursion)
    if (p == 0) {
        return extended_gcd_r{ q, 0, 1 };
    }

    const auto [gcd, x, y] = extended_gcd(q % p, p);

    return extended_gcd_r{ gcd, y - q / p * x, x };
}

/**
 * @brief Determines if two unsigned integers are coprime.
 *
 * Two integers are considered coprime if their greatest common divisor (GCD)
 * is 1, meaning they have no common positive integer factors other than 1.
 *
 * @param p The first unsigned integer.
 * @param q The second unsigned integer.
 * @return true if p and q are coprime (GCD is 1); otherwise, false.
 */
inline bool is_coprime(const long p, const long q) {
    return extended_gcd(p, q).gcd == 1;
}

/**
 * Finds the least common multiplier of two whole numbers.
 *
 * @param p The first whole numbers.
 * @param q The second whole numbers.
 * @return The least common multiplier of two whole numbers.
 */
inline long lcm(const long p, const long q) {
    const auto gcd =
        extended_gcd(static_cast<long>(p), static_cast<long>(q)).gcd;

    return p * q / gcd;
}

/**
 * Finds the result of Carmichael function of the multiplication of two
 * positive integers.
 *
 *     λ(n) = λ(pq) = lcm(p - 1, q - 1)
 *
 * @param p The first positive integer.
 * @param q The second positive integer.
 * @return The result of λ(n), where n = pq.
 */
inline long carmichael(const long p, const long q) { return lcm(p - 1, q - 1); }

/**
 * Find the modular inverse of a given number using the Extended Euclidean
 * Algorithm.
 *
 * @param num The number to find the modular inverse of.
 * @param modulus The modulus.
 * @return The modular inverse.
 */
inline long modular_inverse(const long num, const long modulus) {
    const auto [gcd, x, y] = extended_gcd(num, modulus);

    return (x % modulus + modulus) % modulus;
}

inline long generate_prime_candidate(const unsigned bits) {
    static auto generator = std::random_device{ std::random_device() };
    static auto distribution = std::uniform_int_distribution{ 0, 1 };

    long result = 1;
    for (auto i = 0; i < bits - 1; ++i) {
        result <<= 1;
        result |= distribution(generator);
    }

    // Ensure that the last bit is 1
    result <<= 1;
    result |= 1;

    return result;
}

inline long generate_prime(const unsigned bits) {
    auto candidate = generate_prime_candidate(bits);
    while (!is_prime(candidate)) {
        candidate = generate_prime_candidate(bits);
    }

    return candidate;
}

struct public_key {
    long n;
    long e;
};

struct private_key {
    long n;
    long d;
};

struct key_pair {
    public_key public_key;
    private_key private_key;
};

inline key_pair generate_pairs(const unsigned p, const unsigned q) {
    const long n = p * q;
    const long lambda_n = carmichael(p, q);

    long e = 65537;
    while (e <= lambda_n && !is_coprime(e, lambda_n)) {
        e += 2;
    }

    const long d = modular_inverse(e, lambda_n);

    return { { n, e }, { n, d } };
}

inline key_pair generate_pairs() {
    static constexpr auto BITS = 12;

    const auto p = generate_prime(BITS);
    const auto q = generate_prime(BITS);
    std::cout << "[SECRET] p = " << p << std::endl;
    std::cout << "[SECRET] q = " << q << std::endl;
    std::cout << "[PUBLIC] n = p * q = " << p * q << std::endl;

    return generate_pairs(p, q);
}

inline long
modular_exponentiation(long base, long exponent, const long modulus) {
    long long result = 1;
    base %= modulus;

    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result = result * base % modulus;
        }
        exponent >>= 1;
        base = base * base % modulus;
    }

    return result;
}

inline long encrypt(const public_key& public_key, const long plaintext) {
    const auto [n, e] = public_key;
    return modular_exponentiation(plaintext, e, n);
}

inline long decrypt(const private_key& private_key, const long ciphertext) {
    const auto [n, d] = private_key;
    return modular_exponentiation(ciphertext, d, n);
}

#endif
