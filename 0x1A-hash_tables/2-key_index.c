#include "hash_tables.h"

/**
 * key_index - Calculates the index for a given key
 * in a hash table array.
 * @key: The key
 * @size: The size
 * Return: The index at which the key/value pair should be stored.
 */
unsigned long int key_index(const unsigned char *key, unsigned long int size)
{
	return (hash_djb2(key) % size);
}
