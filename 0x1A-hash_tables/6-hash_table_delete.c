#include "hash_tables.h"

/**
 * hash_table_delete - Deletes a hash table
 * @ht: The hash table to be deleted
 */
void hash_table_delete(hash_table_t *ht)
{
    unsigned long int i = 0;
    hash_node_t *node, *current_node;

    if (ht == NULL)
        return;
    while (i < ht->size)
    {
        node = ht->array[i];
        while (node != NULL)
        {
            current_node = node->next;
            free(node->key);
            free(node->value);
            free(node);
            node = current_node;
        }
        i++;
    }
    free(ht->array);
    free(ht);
}
