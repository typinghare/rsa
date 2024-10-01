#include "rsa.hpp"
#include <random>

bool primality_test(mpz_class& candidate, const int iteration) {
    return mpz_probab_prime_p(candidate.get_mpz_t(), iteration) != 0;
}

mpz_class generate_prime_candidate(gmp_randclass& gmp_rand, const int bits) {
    mpz_class candidate = gmp_rand.get_z_bits(bits);
    mpz_setbit(candidate.get_mpz_t(), 0);
    mpz_setbit(candidate.get_mpz_t(), bits - 1);

    return candidate;
}

mpz_class generate_prime(const int bits) {
    static constexpr auto PRIMALITY_TEST_ITERATION = 25;

    gmp_randclass gmp_rand(gmp_randinit_default);
    gmp_rand.seed(std::random_device{}());

    mpz_class candidate = generate_prime_candidate(gmp_rand, bits);
    while (primality_test(candidate, PRIMALITY_TEST_ITERATION)) {
        candidate = generate_prime_candidate(gmp_rand, bits);
    }

    return candidate;
}
