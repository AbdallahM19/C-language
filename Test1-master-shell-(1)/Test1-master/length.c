#include "shell.h"
/**
* list_length - get the length of a list
* 
* @head: pointer to the list
*
* Return: the length of list
*/
size_t list_length(const list_t *head)
{
size_t count = 0;
	while (head)
	{
		head = head->next;
		count++;
	}
	return (count);
}
/**
* _strlength - calculate the length of a string
*
*@string: string to be checked
*
* Return: the count
*/
int _strlength(char *string)
{
	int count = 0;

	while (*string != '\0')
	{
		count++;
		string++;
	}
	return (count);
}
