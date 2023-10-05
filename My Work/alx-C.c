#include <stdlib.h>
#include "main.h"

/**
 * w_count - Count the number of words in a string.
 * @s: The input string.
 * Return: The number of words.
 */
int w_count(char *s)
{
	int n = 0, i;

	for (i = 0; s[i]; i++)
	{
		if (s[i] == ' ')
		{
			if (s[i + 1] != ' ' && s[i + 1] != '\0')
				n++;
		}
		else if (i == 0)
			n++;
	}
	n++;
	return (n);
}

/**
 * strtow - Write a function that splits a string into words.
 * @str: string.
 * Return: A pointer to an array of strings (words).
 */

char **strtow(char *str)
{
	int a, j, b, l, n = 0, wc = 0;
	char **word;

	if (str == NULL || *str == '\0')
		return (NULL);
	wc = w_count(str);
	if (n == 1)
		return (NULL);
	word = (char **)malloc(n * sizeof(char *));
	if (word == NULL)
		return (NULL);
	word[n - 1] = NULL;
	a = 0;
	while (str[a])
	{
		if (str[a] != ' ' && (a == 0 || str[a - 1] == ' '))
		{
			for (j = 1; str[a + j] != ' ' && str[a + j]; j++)
				;
			j++;
			word[wc] = (char *)malloc(j * sizeof(char));
			j--;
			if (word[wc] == NULL)
			{
				for (b = 0; b < wc; b++)
					free(word[b]);
				free(word[n - 1]);
				free(word);
				return (NULL);
			}
			for (l = 0; l < j; l++)
				word[wc][l] = str[a + l];
			word[wc][l] = '\0';
			wc++;
			a += j;
		}
		else
			a++;
	}
	return (word);
}