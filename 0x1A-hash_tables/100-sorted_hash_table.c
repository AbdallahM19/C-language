#include "hash_tables.h"

/**
 * shash_table_create - Creates a sorted hash table
 * @size: The size of the array
 * Return: A pointer to the created sorted hash table, or NULL on failure
 */
shash_table_t *shash_table_create(unsigned long int size)
{
	unsigned long int i = 0;
	shash_table_t *hash_table;

	hash_table = malloc(sizeof(shash_table_t));
	if (hash_table == NULL)
		return (NULL);
	hash_table->size = size;
	hash_table->array = malloc(sizeof(shash_node_t *) * size);
	hash_table->shead = NULL;
	hash_table->stail = NULL;
	if (hash_table->array == NULL)
	{
		free(hash_table);
		return (NULL);
	}
	while (i < size)
	{
		hash_table->array[i] = NULL;
		i++;
	}
	return (hash_table);
}

/**
 * shash_table_set - Adds or updates an element in the sorted hash table
 * @ht: The sorted hash table
 * @key: The key string
 * @value: The value string
 * Return: 1 if success, 0 otherwise
 */
int shash_table_set(shash_table_t *ht, const char *key, const char *value)
{
	shash_node_t *new_node, *node;

	if (ht == NULL || key == NULL || *key == '\0')
		return (0);
	node = ht->shead;
	while (node != NULL && strcmp(key, node->key) > 0)
		node = node->snext;
	if (node != NULL && strcmp(key, node->key) == 0)
	{
		free(node->value);
		node->value = strdup(value);
		return (1);
	}
	new_node = create_new_node(key, value);
	if (new_node == NULL)
		return (0);
	insert_node(ht, new_node);
	return (1);
}

/**
 * create_new_node - create new node shash_node_t
 * @key: The key string
 * @value: The value string
 * Return: new node, null if not
*/
shash_node_t *create_new_node(const char *key, const char *value)
{
	shash_node_t *node;

	node = malloc(sizeof(shash_node_t));
	if (node == NULL)
		return (NULL);
	node->key = strdup(key);
	node->value = strdup(value);
	if (node->key == NULL || node->value == NULL)
	{
		free(node->key);
		free(node->value);
		free(node);
		return (NULL);
	}
	node->sprev = NULL;
	node->snext = NULL;
	return (node);
}

/**
 * insert_node - create new node shash_node_t
 * @ht: The sorted hash table
 * @new_node: new shash_node_t new_node
*/
void insert_node(shash_table_t *ht, shash_node_t *new_node)
{
	shash_node_t *node;

	if (ht->shead == NULL)
	{
		ht->shead = new_node;
		ht->stail = new_node;
	}
	else
	{
		node = ht->shead;
		while (node != NULL && strcmp(new_node->key, node->key) > 0)
			node = node->snext;

		if (node == NULL)
		{
			new_node->sprev = ht->stail;
			ht->stail->snext = new_node;
			ht->stail = new_node;
			new_node->snext = NULL;
		}
		else
		{
			if (node->sprev == NULL)
			{
				new_node->snext = node;
				node->sprev = new_node;
				ht->shead = new_node;
			}
			else
			{
				new_node->sprev = node->sprev;
				node->sprev->snext = new_node;
				new_node->snext = node;
				node->sprev = new_node;
			}
		}
	}
}

/**
 * shash_table_get - Retrieves the value associated with a key in the sorted hash table.
 * @ht: The sorted hash table
 * @key: The key to search for
 * Return: The value associated with the key, or NULL if the key couldn't be found.
 */
char *shash_table_get(const shash_table_t *ht, const char *key)
{
	shash_node_t *node;

	if (ht == NULL || key == NULL || *key == '\0')
		return (NULL);
	node = ht->shead;
	while (node != NULL && strcmp(key, node->key) > 0)
		node = node->snext;
	if (node != NULL && strcmp(key, node->key) == 0)
		return (node->value);
	return (NULL);
}

/**
 * shash_table_print - Prints the sorted hash table using the sorted linked list.
 * @ht: The sorted hash table.
 */
void shash_table_print(const shash_table_t *ht)
{
	shash_node_t *node;

	if (ht == NULL)
		return;
	printf("{");
	node = ht->shead;
	while (node != NULL)
	{
		printf("'%s': '%s'", node->key, node->value);
		node = node->snext;
		if (node != NULL)
			printf(", ");
	}
	printf("}\n");
}

/**
 * shash_table_print_rev - Prints the sorted hash table in reverse order.
 * @ht: The sorted hash table.
 */
void shash_table_print_rev(const shash_table_t *ht)
{
	shash_node_t *node;

	if (ht == NULL)
		return;
	printf("{");
	node = ht->stail;
	while (node != NULL)
	{
		printf("'%s': '%s'", node->key, node->value);
		node = node->sprev;
		if (node != NULL)
			printf(", ");
	}
	printf("}\n");
}

/**
 * shash_table_delete - Deletes a sorted hash table.
 * @ht: The sorted hash table to be deleted.
 */
void shash_table_delete(shash_table_t *ht)
{
	shash_node_t *current_node, *node;

	if (ht == NULL)
		return;
	current_node = ht->shead;
	while (current_node != NULL)
	{
		node = current_node->snext;
		free(current_node->key);
		free(current_node->value);
		free(current_node);
		current_node = node;
	}
	free(ht->array);
	free(ht);
}
