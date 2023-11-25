#include "shell.h"
/**
* interactive_mode - check if it works in interactve mode and non interactive mode

* @argument: struct address
*
* Return: 1 or 0
*/
int interactive_mode(struct_t *argument)
{
	return (isatty(STDIN_FILENO) && argument->readfd <= 2);
}
/**
 * check_chain - check the last status
 * 
 * @argument: first parameter
 * @cat: seconed parameter
 * @ptr: third one
 * @x: parameter number 4
 * @length: the length
 *
 * Return: Void
 */
void check_chain(struct_t *argument, char *cat, size_t *ptr, size_t x, size_t length)
{
	size_t y = *ptr;

	if (argument->cmd_buf_type == CMD_AND)
	{
		if (argument->status)
		{
			cat[x] = 0;
			y = length;
		}
	}
	if (argument->cmd_buf_type == CMD_OR)
	{
		if (!argument->status)
		{
			cat[x] = 0;
			y = length;
		}
	}
	*ptr = y;
}
/**
 * is_chain - check if it is the chain
 * 
 * @argument: first member
 * 
 * @cat: seconed member
 * 
 * @ptr: third member
 *
 * Return: 0 or 1
 */
int is_chain(struct_t *argument, char *cat, size_t *ptr)
{
	size_t i = *ptr;
	if (cat[i] == '|' && cat[i + 1] == '|')
	{
		cat[i] = 0;
		i++;
		argument->cmd_buf_type = CMD_OR;
	}
	else if (cat[i] == '&' && cat[i + 1] == '&')
	{
		cat[i] = 0;
		i++;
		argument->cmd_buf_type = CMD_AND;
	}
	else if (cat[i] == ';')
	{
		cat[i] = 0;
		argument->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*ptr = i;
	return (1);
}