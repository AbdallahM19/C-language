#include "shell.h"
/**
* _strdup - duplicates a string
*
* @str: a string to be duplicated
*
* Return: pointer to the duplicated string
*/
char *_strdup( const char *str)
{
	int i;
	char *p;
	int length = strlen(str);
	if (str == NULL)
		return (NULL);
	p = malloc(length + 1 * sizeof(char));
	if (p == 0)
		return (NULL);
	for (i = 0; i < length; i++)
		p[i] = str[i];
	return (p);
}
/**
 * char_duplicate - dublicate a char
 * 
 * @place: path
 * 
 * @x: start
 * 
 * @y: stop
 *
 * Return: pointer to new buffer
 */
char *char_duplicate(char *place, int x, int y)
{
	static char buffer[1024];
	int i = 0, k = 0;
	for (k = 0, i = x; i < y; i++)
		if (place[i] != ':')
			buffer[k++] = place[i];
	buffer[k] = 0;
	return (buffer);
}
