#ifndef MONTY_H
#define MONTY_H
#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
/**
*struct arguments - stuct holds the arguments
*@file: pointer to file
*@buf: pointer to char to hold the command
*@lilo: hold sign to defer stack and queue
*/
typedef struct arguments
{
FILE *file;
char *buf;
int lilo;
} args_t;
extern args_t args;

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


/*push.c*/
void push_error(unsigned int num, stack_t **first);
void mypush(stack_t **first, unsigned int num);

/*add.c*/
void node_add(stack_t **first, int num);
void queue_add(stack_t **first, int num);
void stack_add(stack_t **first, unsigned int num);

/*let_free.c*/
void free_all(char *buf, stack_t *stack, args_t **args, FILE *file);
void stack_free(stack_t *first);
void free_args(args_t *args);
/*pall.c*/
void my_pall(stack_t **first, unsigned int num);
void my_pint(stack_t **first, unsigned int num);
/*check.c*/
int check_func(char *buf, stack_t **stack, unsigned int count, FILE *);
/*pop.c*/
void mypop(stack_t **first, unsigned int num);
/*error.c*/
void error(stack_t **first);

void f_nop(stack_t **first, unsigned int num);

void f_swap(stack_t **first, unsigned int num);
void stack_sub(stack_t **first, unsigned int num);
void stack_div(stack_t **first, unsigned int num);
void stack_mul(stack_t **first, unsigned int num);
void stack_mod(stack_t **first, unsigned int num);
void stack_pchar(stack_t **first, unsigned int num);
void stack_pstr(stack_t **first, unsigned int num);

void f_stack(stack_t **first, unsigned int num);
void f_queue(stack_t **first, unsigned int num);

void stack_rotl(stack_t **first, unsigned int num);
void stack_rotr(stack_t **first, unsigned int num);
#endif
