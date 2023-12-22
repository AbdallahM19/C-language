#include "hash_tables.h"

/**
 * hash_table_print - Prints a hash table
 * @ht: The hash table
 */
void hash_table_print(const hash_table_t *ht)
{
    unsigned long int i = 0;
    hash_node_t *node;
    int first = 1;

    if (ht == NULL)
        return;
    printf("{");
    while (i < ht->size)
    {
        node = ht->array[i];
        while (node != NULL)
        {
            if (!first)
                printf(", ");
            printf("'%s': '%s'", node->key, node->value);
            first = 0;
            node = node->next;
        }
        i++;
    }
    printf("}\n");
}
