#include "shell.h"
/**
 * remove_comments - removecoments
 * 
 * @cat: pointer
 *
 * Return: Always 0;
 */
void remove_comments(char *cat)
{
	int x;
	for (x = 0; cat[x] != '\0'; x++)
		if (cat[x] == '#' && (!x || cat[x - 1] == ' '))
		{
			cat[x] = '\0';
			break;
		}
}