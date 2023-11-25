#include "shell.h"
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
/**
* _strcmp - compare two strings
* 
* @s1: first member
* @s2: seconed one
*
* Return: the result
*/
int _strcmp(char *s1, char *s2)
{
	int i;
	int result = 0;
/* use for loop*/
/*calculate the result to compare*/
	for (i = 0; s1[i] != '\0' && result == 0; i++)
	{
		result = s1[i] - s2[i];
	}
	return (result);
}
/**
 * starts_with - checks if specific word start with specific char
 * 
 * @cat: first member
 * 
 * @kitty: seconed one
 *
 * Return: pointer
 */
char *starts_with(const char *cat, const char *kitty)
{
    while (*kitty) {
        if (*kitty != *cat)
            return NULL;
        kitty++;
        cat++;
    }
    return ((char *)cat);
}

/**
 * _strcat - concatenates two strings
 * 
 * @dest: first member
 * 
 * @src: tsecond one
 *
 * Return: dest
 */
char *_strcat(char *dest, char *src)
{
	int i = 0, j = 0;

	while (dest[j] != '\0')
		j++;
	while (src[i] != '\0')
	{
		dest[j] = src[i];
		j++;
		i++;
	}
	dest[j] = '\0';
	return (dest);
}
