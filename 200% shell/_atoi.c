#include "shell.h"

/**
 *_atoi - simuilte atoi
 *@num: the string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
*/
int _atoi(char *num)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0;  num[i] != '\0' && flag != 2; i++)
	{
		if (num[i] == '-')
			sign *= -1;

		if (num[i] >= '0' && num[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (num[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}