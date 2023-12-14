#ifndef MONTY_H
#define MONTY_H

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <stdarg.h>
/**
 * struct stack_s - doubly linked list representation of a stack (or queue)
 * @n: integer
 * @prev: points to the previous element of the stack (or queue)
 * @next: points to the next element of the stack (or queue)
 *
 * Description: doubly linked list node structure
 * for stack, queues, LIFO, FIFO
 */
typedef struct stack_s
{
	int n;
	struct stack_s *prev;
	struct stack_s *next;
} stack_t;

/**
 * struct instruction_s - opcode and its function
 * @opcode: the opcode
 * @f: function to handle the opcode
 *
 * Description: opcode and its function
 * for stack, queues, LIFO, FIFO
 */
typedef struct instruction_s
{
	char *opcode;
	void (*f)(stack_t **stack, unsigned int line_number);
} instruction_t;

extern stack_t *head;
typedef void (*op_func)(stack_t **, unsigned int);

/* file.c */
void open_file(char *);
void read_file(FILE *);
int parse_line(char *, int, int);
void find_func(char *, char *, int, int);
void call_fun(op_func, char *, char *, int, int);

/* errors.c */
void err(int, ...);
void more_err(int, ...);
void string_err(int, ...);

/* main.c */
stack_t *create_node(int);
void free_nodes(void);
void add_queue(stack_t **, unsigned int);

/* opcodes_implementation_1.c */
void add(stack_t **, unsigned int);
void sub(stack_t **, unsigned int);
void divide(stack_t **, unsigned int);
void mul(stack_t **, unsigned int);
void mod(stack_t **, unsigned int);

/* opcodes_implementation.c */
void pop(stack_t **, unsigned int);
void swap(stack_t **, unsigned int);
void nop(stack_t **, unsigned int);
void pchar(stack_t **, unsigned int);
void pstr(stack_t **, unsigned int);

/* push.c */
void push(stack_t **, unsigned int);
void pall(stack_t **, unsigned int);
void pint(stack_t **, unsigned int);

/* rot.c */
void rotl(stack_t **, unsigned int);
void rotr(stack_t **, unsigned int);

#endif

