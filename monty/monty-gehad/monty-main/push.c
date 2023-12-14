#include "monty.h"
/**
*push_error - print eerror massege when feild to push
*@num: unsinged int
*@first: pointer of pointer to the stack
*/
void push_error(unsigned int num, stack_t **first)
{
	fprintf(stderr, "L%d: usage: push integer\n", num);
	error(first);
}
/**
*mypush - push elements to the stack
*@first: pointer of pointer to the stack
*@num: unsigned int to be pushed
*/
void mypush(stack_t **first, unsigned int num)
{
int n, count = 0, checker = 0;
	if (args.buf)
{
		if (args.buf[0] == '-')
			count++;
		for (; args.buf[count] != '\0'; count++)
		if (args.buf[count] > '9' || args.buf[count] < '0')
			checker = 1;
				if (checker == 1)
					push_error(num, first);
}
	else
		push_error(num, first);
	n = atoi(args.buf);
	if (args.lilo == 0)
		node_add(first, n);
	else
		queue_add(first, n);
}
