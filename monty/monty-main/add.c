#include "monty.h"
/**
*stack_add - add top two elements of the stack
*@first: pointer of pointer to the stack
*@num: integer to be addes
*/
void stack_add(stack_t **first, unsigned int num)
{
	int sum;
	stack_t *current = *first;

	if (*first == NULL || first == NULL || (*first)->next == NULL)
	{
		fprintf(stderr, "L%d: can't add, stack too short\n", num);
		error(first);
	}
	current = *first;
	sum = current->n + current->next->n;
	current->next->n = sum;
	*first = current->next;
	free(current);
}
/**
*node_add - add new node to double linked list
*@first: pointer of pointer to the stack
*@num: integer to be addes
*Return: void
*/
void node_add(stack_t **first, int num)
{
stack_t *current, *new_node = malloc(sizeof(stack_t));
	if (new_node == NULL)
		fprintf(stderr, "Error: malloc failed\n"), exit(EXIT_FAILURE);
	current = *first;
	if (current)
		current->prev = new_node;
	new_node->prev = NULL;
	new_node->next = *first;
	new_node->n = num;
	*first = new_node;
}
/**
*queue_add - add a node to quque
*@first: pointer oof pointer to the stack
*@num: integer to be addes
*Return: void
*/
void queue_add(stack_t **first, int num)
{
stack_t *current, *new_node = malloc(sizeof(stack_t));
	if (new_node == NULL)
		fprintf(stderr, "Error: malloc failed\n"), exit(EXIT_FAILURE);
	current = *first;
	new_node->n = num;
	new_node->next = NULL;
	if (current == NULL)
{
		*first = new_node;
		new_node->prev = NULL;
}
	else
{
		while (current->next != NULL)
			current = current->next;
		current->next = new_node;
		new_node->prev = current;
}
}
