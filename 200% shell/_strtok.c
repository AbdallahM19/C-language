#include "shell.h"

/**
 * _strtok - split the string to toknizer
 * @str: string to be toknized
 * @delim: char
 * Return: the words splited
*/
char *_strtok(char *str, char *delim)
{
	static char *last_str;
	char *return_of_the_rest = NULL;

	if (!str)
		str = last_str;
	if (!str)
		return (NULL);
	while (1)
	{
		if (delim_check(*str, delim))
		{
			str++;
			continue;
		}
		if (*str == '\0')
			return (NULL);
		break;
	}
	return_of_the_rest = str;
	while (1)
	{
		if (*str == '\0')
		{
			last_str = str;
			return (return_of_the_rest);
		}
		if (delim_check(*str, delim))
		{
			*str = '\0';
			last_str = str + 1;
			return (return_of_the_rest);
		}
		str++;
	}
}

/**
 * make_array_str - copy string in the heap
 * @str: string
 * @delim: char
 * Return: strings
*/
char **make_array_str(char *str, char *delim)
{
	int i = 0;
	char *token, **array_str = malloc(sizeof(char *) * 100);
	char *str_cp = _strdup(str);

	token = _strdup(str_cp, delim);
	while (token != NULL)
	{
		array_str[i] = malloc(sizeof(char) * _strlen(token) + 1);
		_strcpy(array_str[i], token);
		token = _strtok(NULL, delim);
		i++;
	}
	free(str_cp);
	array_str[i] = NULL;
	return(array_str);
}

/**
 * make_array_str - copy string in the heap
 * @str: string
 * @delim: char
 * Return: strings
*
char **make_array_str(char *str, char *delim)
{
    int i = 0;
    char *token, **array_str = NULL;
    char *str_cp = _strdup(str);

    array_str = malloc(sizeof(char *) * INITIAL_SIZE);

    token = _strdup(str_cp, delim);
    while (token != NULL)
    {
        array_str[i] = _strdup(token);

        token = _strtok(NULL, delim);
        i++;

        if (i % INITIAL_SIZE == 0)
            array_str = realloc(array_str, sizeof(char *) * (i + INITIAL_SIZE));
    }

    free(str_cp);
    array_str[i] = NULL;
    return array_str;
} */