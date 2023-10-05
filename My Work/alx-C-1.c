#include <stdlib.h>
#include "main.h"

/**
 * w_count - to count the number of words in a string
 * @s: string to evaluate
 * Return: word
 */
int w_count(char *s)
{
	int len, a, b;

	len = 0;
	a = 0;

	for (a = 0; s[a] != '\0'; a++)
	{
		if (s[a] == ' ')
			len = 0;
		else if (len == 0)
		{
			len = 1;
			b++;
		}
	}

	return (b);
}

/**
 * **strtow - Write a function that splits a string into words.
 * @str: string to split
 *
 * Return: pointer to an array
 */

char **strtow(char *str)
{
	char **tab2, *tab;
	int i, k = 0, len = 0, words, c = 0, s, e;

	while (*(str + len))
		len++;
	words = w_count(str);
	if (words == 0)
		return (NULL);

	tab2 = (char **) malloc(sizeof(char *) * (words + 1));
	if (tab2 == NULL)
		return (NULL);

	for (i = 0; i <= len; i++)
	{
		if (str[i] == ' ' || str[i] == '\0')
		{
			if (c)
			{
				e = i;
				tab = (char *) malloc(sizeof(char) * (c + 1));
				if (tab == NULL)
					return (NULL);
				while (s < e)
					*tab++ = str[s++];
				*tab = '\0';
				tab2[k] = tab - c;
				k++;
				c = 0;
			}
		}
		else if (c++ == 0)
			s = i;
	}

	tab2[k] = NULL;

	return (tab2);
}