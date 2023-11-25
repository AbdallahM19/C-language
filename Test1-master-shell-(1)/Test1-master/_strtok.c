#include "shell.h"
/**
*str_token - split the string to toknizer
*
*@command: string to be toknized
*
*@delim: char 
*
*Return: the words splited
*/
char **str_tokn(char *command, char *delim)
{
  int i, j, k, m, count = 0;
  char **s;

  if (command == NULL || command[0] == 0)
      return (NULL);
  for (i = 0; command[i] != '\0'; i++)
      if (!delim_check(command[i], delim) && (delim_check(command[i + 1], delim) || !command[i + 1]))
          count++;
  if (count == 0)
      return (NULL);
  s = malloc((1 + count) * sizeof(char *));
  if (!s)
      return (NULL);
  for (i = 0, j = 0; j < count; j++)
  {
      while (delim_check(command[i], delim))
          i++;
      k = 0;
      while (!delim_check(command[i + k], delim) && command[i + k])
          k++;
      s[j] = malloc((k + 1) * sizeof(char));
      if (!s[j])
      {
          for (k = 0; k < j; k++)
              free(s[k]);
          free(s);
          return (NULL);
      }
      for (m = 0; m < k; m++)
          s[j][m] = command[i++];
      s[j][m] = 0;
  }
  s[j] = NULL;
  return (s);
}
