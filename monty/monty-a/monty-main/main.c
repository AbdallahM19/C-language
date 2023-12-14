#include "monty.h"

stack_t *head = NULL;

/**
 * main - Entry point for the Monty interpreter.
 * @argc: Number of command-line arguments.
 * @argv: Array of command-line argument strings.
 * Return: 0 on success.
 */
int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}
	open_file(argv[1]);
	free_nodes();
	return (0);
}

/**
 * create_node - Creates a new stack/queue node.
 * @n: Value to be stored in the new node.
 * Return: a pointer to the newly created node.
 */
stack_t *create_node(int n)
{
	stack_t *node;

	node = malloc(sizeof(stack_t));
	if (node == NULL)
		err(4);
	node->next = NULL;
	node->prev = NULL;
	node->n = n;
	return (node);
}

/**
 * free_nodes - Frees all nodes in the stack/queue.
 */
void free_nodes(void)
{
	stack_t *temp;

	if (head == NULL)
		return;
	while (head != NULL)
	{
		temp = head;
		head = head->next;
		free(temp);
	}
}


/**
 * add_queue - Adds a node to the queue.
 * @stack: Pointer to the new node.
 * @line_number: Interger representing the line number of of the opcode.
 */
void add_queue(stack_t **stack, unsigned int line_number)
{
	stack_t *temp;

	(void) line_number;
	if (stack == NULL || *stack == NULL)
		exit(EXIT_FAILURE);
	if (head == NULL)
	{
		head = *stack;
		return;
	}
	temp = head;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = *stack;
	(*stack)->prev = temp;
}

