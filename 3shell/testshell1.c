#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <linux/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/stat.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* toem_shloop.c */
int file_mode(char **av, info_t *info);
int execute_command(info_t *, char **);
int check_builtin(info_t *);
void command_placeholder(info_t *);
void fork_command(info_t *);

/* toem_parser.c */
int is_command(info_t *, char *);
char *char_duplicate(char *, int, int);
char *path_finder(info_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* toem_errors.c */
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* toem_string.c */
int _strlength(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* toem_string1.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* toem_exits.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* toem_tokenizer.c */
char **str_tokn(char *, char *);
/* toem_realloc.c */
char *_memset(char *, char, unsigned int);
void free_string(char **ptr);
void *_realloc(void *, unsigned int, unsigned int);

/* toem_memory.c */
int free_pointer(void **cat);

/* toem_atoi.c */
int interactive(info_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

/* toem_errors1.c */
int convert_string(char *);
void print_error(info_t *, char *);
int print_integer(int num, int file);
char *convert_number(long int, int, int);
void remove_comments(char *buf);

/* toem_builtin.c */
int _myexit(info_t *);
int _mycd(info_t *);
int _myhelp(info_t *);

/* toem_builtin1.c */
int _myhistory(info_t *);
int _myalias(info_t *);

/*toem_getline.c */
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void handle_sign(int);
ssize_t buffer_reading(info_t *info, char *buffer, size_t *size);
ssize_t handle_input(info_t *info, char **buf, size_t *len);

/* toem_getinfo.c */
void delete_info(info_t *);
void init_info(info_t *info, char **argv);
void free_info(info_t *, int);

/* toem_environ.c */
char *_getenv(info_t *, const char *);
int _myenv(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);

/* toem_getenv.c */
char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

/* toem_history.c */
char *start_history(info_t *info);
int history_writing(info_t *info);
int history_reading(info_t *info);
int create_history_list(info_t *info, char *buf, int linecount);
int history_renum(info_t *info);

/* toem_lists.c */
list_t *add_node_head(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void list_free(list_t **);

/* toem_lists1.c */
size_t list_length(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/* toem_vars.c */
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int new_alias(info_t *);
int new_vars(info_t *);
int new_string(char **, char *);

#endif

#include "shell.h"

/**
 * interactive - returns true if shell is interactive mode
 * @info: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - checks if character is a delimeter
 * @c: the char to check
 * @delim: the delimeter string
 * Return: 1 if true, 0 if false
 */
int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 *_isalpha - checks for alphabetic character
 *@c: The character to input
 *Return: 1 if c is alphabetic, 0 otherwise
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_atoi - converts a string to an integer
 *@s: the string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 */

int _atoi(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0;  s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
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

#include "shell.h"

/**
 * _myexit - exit the program (Handles the 'exit' command)
 * @info: structure contain information
 * Return:
 * -2: specified exit status.
 * 1: an illegal number as the exit status.
*/
int _myexit(info_t *info)
{
	int exit_check;

	if (info->argv[1])
	{
		exit_check = convert_string(info->argv[1]);
		if (exit_check == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = convert_string(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _mycd - changes the current directory of the process.
 * @info: structure contain information
 * Return: Always 0
*/
int _mycd(info_t *info)
{
	char *curr_dir, *dir, buffer[1024];
	int chdir_ret;

	curr_dir = getcwd(buffer, 1024);
	if (!curr_dir)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
			chdir_ret = chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		dir = _getenv(info, "OLDPWD=");
		if (!dir)
		{
			_puts(curr_dir);
			_putchar('\n');
			return (1);
		}
		_puts(dir), _putchar('\n');
		chdir_ret = chdir(dir);
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
		return (1);
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - displays information about
 * shell commands or functions
 * @info: structure contain information
 * Return: Always 0
*/
int _myhelp(info_t *info)
{
	char **p;

	p = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*p);
	return (0);
}

#include "shell.h"

/**
 * _myhistory - print the history of used commands
 * @info: struct contain arguments
 * Return: 0
*/
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - remove alias ( Unsets an alias )
 * @info: first parameter struct
 * @str: seconed parameter struct
 * Return: 0 on success or 1 on error
*/
int unset_alias(info_t *info, char *str)
{
	char *sign = _strchr(str, '=');
	int ret;

	if (!sign)
		return (1);
	*sign = '\0';
	ret = delete_node_at_index(&(info->alias),
	get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*sign = '=';
	return (ret);
}

/**
 * set_alias - set alias to string
 * @info: first parameter
 * @str: seconed parameter
 * Return: 0 or 1
*/
int set_alias(info_t *info, char *str)
{
	char *sign = _strchr(str, '=');

	if (!sign)
		return (1);
	if (!*++sign)
	{
		unset_alias(info, str);
		return (0);
	}
	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - print an alas string
 * @node: the alias node
 * Return: 0 or 1
*/
int print_alias(list_t *node)
{
	char *sign = _strchr(node->str, '=');
	char *a = node->str;

	if (node)
	{
		while (a <= sign)
		{
			_putchar(*a);
			a++;
		}
		_putchar('\'');
		_puts(sign + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - manages shell aliases
 * @info: struct contain arguments
 * Return: 0
*/
int _myalias(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node_alias = NULL;

	if (info->argc == 1)
	{
		node_alias = info->alias;
		while (node_alias)
		{
			print_alias(node_alias);
			node_alias = node_alias->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = _strchr(info->argv[i], '=');
		if (p)
		{
			if (set_alias(info, info->argv[i]) != 0)
				return (1);
		}
		else
		{
			node_alias = node_starts_with(info->alias, info->argv[i], '=');
			if (node_alias)
				print_alias(node_alias);
			else
			{
				print_error(info, "alias: ");
				print_error(info, info->argv[i]);
				print_error(info, ": not found\n");
				return (1);
			}
		}
	}
	return (0);
}

#include "shell.h"

/**
 * _myenv - prints the new environment
 * @info: Structure containing potential arguments.
 * Used to maintain constant function prototype.
 * Return: Always 0
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - gets the value of an environ variable
 * @info: Structure containing potential arguments
 * @name: environment variable name
 * Return: the value
*/
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;

	while (node != NULL)
	{
		char *p = starts_with(node->str, name);

		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - Initialize a new environment variable,
 * or modify an existing one
 * @info: structure containing potential arguments,
 * Used to maintain constant function prototype.
 * Return: O, 1 if error
 */
int _mysetenv(info_t *info)
{
	char *a = info->argv[1];
	char *b = info->argv[2];

	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, a, b) != 0)
	{
		_eputs("Failed to update environment variable\n");
		return (1);
	}
	return (0);
}

/**
 * _myunsetenv - Remove an environmental variable.
 * @info: Structure containing potential arguments.
 * Used to maintain constant function prototype.
 * Return: Always 0.
 */
int _myunsetenv(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
	{
		if (_unsetenv(info, info->argv[i]) != 0)
		{
			_eputs("Failed to remove environment variable.\n");
			return (1);
		}
	}
	return (0);
}

/**
 * populate_env_list - populates env linked list.
 * @info: structure containing potential arguments.
 * used to maintain constant function prototype.
 * Return: Always 0
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&(node), environ[i], 0);
	info->env = node;
	return (0);
}

#include "shell.h"
/**
* print_error - print error massage to stderr
*
* @info: pointer to the struct
*
* @string: string to be printed
*
* Return: void
*/
void print_error(info_t *info, char *string)
{
	_eputs(info->fname);
	_eputs(": ");
	print_integer(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(string);
}
/**
*_eputs - print a string to stderr
*
* @cat: ta string
*
* Return: void
*/
void _eputs(char *cat)
{
	int i;
	if (!cat)
		return;
	for (i = 0; cat[i] != '\0'; i++)
		_eputchar(cat[i]);
}
/**
 * _eputchar - print a char to stderr
 * 
 * @ch: a char
 *
 * Return: the char
 */
int _eputchar(char ch)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];
	if (ch == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (ch != BUF_FLUSH)
		buf[i++] = ch;
	return (1);
}
/**
* _putfd - print a char to a filedescriptor
* @ch: a character
*
* @fd: a filedescriptor
*
* Return: the char
*/
int _putfd(char ch, int file)
{
	static int x;
	static char buf[WRITE_BUF_SIZE];
	if (ch == BUF_FLUSH || x >= WRITE_BUF_SIZE)
	{
		write(file, buf, x);
		x = 0;
	}
	if (ch != BUF_FLUSH)
		buf[x++] = ch;
	return (1);
}
/**
*_putsfd - print a string to a filedescriptor
*
* @cat: a string
*
* @fd: the filedescriptor to write to
*
* Return: the number of chars put
*/
int _putsfd(char *cat, int file)
{
int x = 0;
	if (!cat)
		return (0);
	while (*cat)
	{
		x += _putfd(*cat++, file);
	}
	return (x);
}

#include "shell.h"
/**
* convert_number - convert a number
* 
* @n: number
*
* @base: base
*
* @flag: argument flags
*
* Return: a string
*/
char *convert_number(long int n, int base, int flag)
{
	static char *array;
	static char buf[50];
	char sign = 0, *p;
	unsigned long num = n;
	if (!(flag & CONVERT_UNSIGNED) && n< 0)
	{
		num = -n;
		sign = '-';
	}
	array = flag & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	p = &buf[49];
	*p = '\0';
	do	{
		*--p = array[num % base];
		num /= base;
	} while (num != 0);

	if (sign)
		*--p = sign;
	return (p);
}
/**
* convert_string - convert a string to an integer
*
* @string: the only member
*
* Return: result or -1
*/
int convert_string(char *string)
{
	int i = 0;
	unsigned long int result = 0;
	if (*string == '+')
		string++;
	for (i = 0;  string[i] != '\0'; i++)
	{
		if (string[i] >= '0' && string[i] <= '9')
		{
			result *= 10;
			result += (string[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}
/**
* print_integer - print an integer to a filedescriptor 
* 
* @num: number
* 
* @file: tfile
*
* Return: character
*/
int print_integer(int num, int file)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (file == STDERR_FILENO)
		__putchar = _eputchar;
	if (num < 0)
	{
		_abs_ = -num;
		__putchar('-');
		count++;
	}
	else
		_abs_ = num;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return (count);
}
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

#include "shell.h"
/**
*_strncpy - copy string to another
*
*@cat: new string
*
*@kitty: the origin string
*
*@num: specific charachthers to copy
*
*Return: cat
*/
char *_strncpy(char *cat, char *kitty, int num)
{
	int x = 0, y = 0;

	for (; kitty[x] != '\0' && x < num-1; x++, y++)
		cat[y] = kitty[x];
	if (y < num)
	{
		for (; y < num; y++)
			cat[y] = '\0';
	}
	return (cat);
}
/**
*_strncat - concatenates two strings
*
*@cat: new string
* 
*@kitty: the origin strin
* 
*@num: 
* 
*Return: cat
 */
char *_strncat(char *cat, char *kitty, int num)
{
	int i, j;

	for (i = 0; kitty[i] != '\0'; i++)
		;
	for (j = 0; cat[j] != 0 && j < num; j++)
	{
		kitty[i + j] = cat[j];
	}
	if (j < num)
		kitty[j] ='\0';
	return (kitty);
}
/**
*_strchr - find specific characther in string
*
*@p: the string
*
*@x: the char
*
*Return: the pointer or NULL
*/
char *_strchr(char *p, char x)
{
	while (*p != '\0')
	{
		if (*p == x)
			return (p);
		p++;
	}
	return (NULL);
}

#include"shell.h"

/**
 * get_environ - returns the string array copy of our environ
 * @info: Structure containing potential arguments.
 * Used to maintain constant function prototype.
 * Return: Always 0
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}
	return (info->environ);
}

/**
 * _setenv - Initialize a few environment variable
 * or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 * Return: Always 0
*/
int _setenv(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (1);

	buf = malloc(_strlength(var) + _strlength(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = info->env;
	while(node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	if (add_node_end(&(info->env), buf, 0) == NULL)
	{
		free(buf);
		return (1);
	}
	info->env_changed = 1;
	return (0);
}

/**
 * _unsetenv - Remove an environment variable
 * @info: structure containing potential arguments.
 * @var: the string env var property
 * Return: 1 on delete, 0 otherwise
 */
int _unsetenv (info_t *info, char *var)
{
	list_t *node = info->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_changed);
}

#include "shell.h"
/**
 * init_info - set info_t struct
 * 
 * @info: struct 
 * 
 * @av: arguments
 * 
 * Return: void
 */
void init_info(info_t *info, char **argv)
{
	int x = 0;
	info->fname = argv[0];
	if (info->arg)
	{
		info->argv = str_tokn(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (x = 0; info->argv && info->argv[x]; x++)
			;
		info->argc = x;
		new_alias(info);
		new_vars(info);
	}
}
/**
 * delete_info - clear the stuct
 * 
 * @info: pointer to the struct
 * 
 * Return: void
 */
void delete_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}
/**
 * free_info - free a struct
 * 
 * @info: pointer to the stuct
 * 
 * @dl: int to check
 * 
 * Return: void
 */
void free_info(info_t *info, int dl)
{
	free_string(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (dl)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			list_free(&(info->env));
		if (info->history)
			list_free(&(info->history));
		if (info->alias)
			list_free(&(info->alias));
		free_string(info->environ);
			info->environ = NULL;
		free_pointer((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}
