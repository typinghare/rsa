#ifndef RSA_HPP
#define RSA_HPP

#include <gmpxx.h>

/**
 * @brief Checks if a given candidate number is probably prime.
 *
 * This function uses the Miller-Rabin primality test to determine
 * whether the provided candidate number is likely to be prime.
 * The test is probabilistic, meaning it can yield false positives
 * (indicating a composite number as prime). The reliability of the
 * test increases with the number of iterations specified.
 *
 * @param candidate The number to test for primality. It should be a
 *                  positive integer of type mpz_class.
 * @param iteration The number of iterations for the primality test.
 *                  More iterations increase the confidence that the
 *                  candidate is prime.
 * @return true if the candidate is probably prime, false otherwise.
 */
bool primality_test(mpz_class& candidate, int iteration);

/**
 * @brief Generates a random prime candidate of the specified bit length.
 *
 * This function generates a random integer with the given number of bits,
 * ensuring that the least significant bit (LSB) is set to 1 (to make
 * the number odd) and that the most significant bit (MSB) is set (to
 * ensure the candidate has the desired bit length).
 *
 * @param gmp_rand The random number generator instance used to create
 *                 the candidate.
 * @param bits The desired bit length for the generated candidate.
 *             The candidate will have exactly this many bits.
 * @return A randomly generated mpz_class number that serves as a
 *         potential prime candidate.
 */
mpz_class generate_prime_candidate(gmp_randclass& gmp_rand, int bits);

/**
 * @brief Generates a prime number of the specified bit length.
 *
 * This function creates a prime number by generating random candidates
 * of the specified bit length and testing each one for primality. It
 * continues generating candidates until a prime number is found. The
 * Miller-Rabin primality test is used for this purpose, with a fixed
 * number of iterations to ensure a high level of confidence in the result.
 *
 * @param bits The desired bit length for the generated prime number.
 * @return A mpz_class number that is a verified prime of the
 *         specified bit length.
 */
mpz_class generate_prime(int bits);

#endif
