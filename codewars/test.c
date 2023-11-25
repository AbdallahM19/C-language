#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char* reverseWords(const char* text)
{
	if (text == NULL)
		return (NULL);
	size_t len = strlen(text);
	char *reversed = (char *)malloc((len + 1) * sizeof(char));
	if (reversed == NULL)
		return (NULL);
	size_t i = 0, j = 0, start;
	while (i < len)
	{
		while (i < len && text[i] == ' ')
		{
			reversed[j++] = text[i++];
		}
		start = j;
		while (i < len && text[i] != ' ')
		{
			reversed[j++] = text[i++];
		}
		for (size_t k = 0; k < (j - start) / 2; k++)
		{
			char temp = reversed[start + k];
			reversed[start + k] = reversed[j - k - 1];
			reversed[j - k - 1] = temp;
		}
		while (i < len && text[i] == ' ')
		{
			reversed[j++] = text[i++];
		}
	}
	reversed[j] = '\0';
	return (reversed);
}