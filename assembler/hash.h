/**
 * @file
 * @brief  Hash implementations
 * @author d3phys
 * @date   03.10.2021
 */

#ifndef HASH_H_
#define HASH_H_

/**
 * @brief Murmur2 algorithm hash function.
 *
 * @param key     Hash key pointer
 * @param length  Key length
 * @param seed    Random seed
 *
 * This hash function was originally created by Austin Appleby.
 * It is fast and simple hash algorithm.
 *
 * There are a few assumptions about how your machine behaves:
 * 1. We can read a 4-byte value from any address without crashing
 * 2. sizeof(int) = 4
 *
 * Also there are a few limitations:
 * 1. It will not work incrementally
 * 2. It will not produce the same results on little-endian and big-endian
 *    machines
 */
unsigned int murmur_hash(const void *const key, int length, unsigned int seed);

#endif /* HASH_H_ */

