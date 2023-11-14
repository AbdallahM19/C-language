shell.h
#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include <elf.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/stat.h>

#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1


#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;

/**
 * struct liststr - singly linked list
 * @num: number of field
 * @str: string
 * @next: points to the next mode
*/
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;


/**
 * struct passinfo - contains pseudo-arguements to pass into a function,
 * allowing uniform prototype for function pointer struct
 * @arg: a string generated from getline containing arguements
 * @argv: an array of strings generated from arg
 * @path: a string path for the current command
 * @arge: the argument count
 * @line_count: the error count
 * @err_num: the error code for exit() s
 * @linecount_flag: if on count this line of input
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: the history node
 * @alias: the alias node
 * @env_changed: on if environ was changed
 * @status: the return status of the last exec'd command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: the fd from which to read line input
 * @histcount: the history line number count
*/
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
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
	int argc;
	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, 0, NULL, \
        0, 0, 0}
/**
 * struct builtin - contains a builtin string and related function
 * @type: builtin commend flag
 * @func: function
*/
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

/* hsh.c */
int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

/* path.c */
int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/*builtin_emulators.c*/
int _myexit (info_t *);
int _mycd (info_t *);
int _myhelp (info_t *);

/* builtin_emulators2.c*/
int _myhistory (info_t *);
int _myalias (info_t *);

/* getline.c module */
ssize_t get_input (info_t *);
int _getline (info_t *, char **, size_t *);
void sigintHandler(int);

/* info.c */
void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);

/* env.c module */
char *_getenv(info_t *, const char *);
int _myenv(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);

/* env2.c module */
char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

/* file_io_functions.c */
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

/* err_string_functions.c*/
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* main.c */
void execute_command(char *, int);
/* string_functions.c*/
int _strlength(char *);
int _strcmp(char *s, char *b);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* string_functions2.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char c);

/* string_functions3.c */
char *_strcpy(char *dest, char *src);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* string_functions4.c */
char **_strtow(char *, char *);
char **_strtow2(char *, char);

/* memory_functions.c */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* memory_functions2.c */
int bfree(void **);

/* more_functions.c*/
int interactive (info_t *);
int is_delim (char, char *);
int isalpha (int);
int _atoi (char *);

/* more_functions2.c*/
int _erratoi (char *);
void print_error (info_t *, char *);
int print_d(int, int);
char *convert_number (long int, int, int);
void remove_comments (char *);

char *strtok_custom(char *str, const char *delimiters);
char *_strpbrk(char *str, const char *accept);
int _strspn(const char *str, const char *accept);

/**/
void print_env(char **env);
/**/


/* liststr.c */
list_t *add_node (list_t **head, const char *str, int num);
list_t *add_node_end (list_t **head, const char *str, int num);
size_t print_list_str (const list_t *h);
int delete_node_at_index (list_t **head, unsigned int index);
void free_list (list_t **head_ptr);

/* liststr2.c */
size_t list_len(const list_t *h);
char **list_to_strings(list_t *head);
size_t print_list(const list_t *h);
list_t *node_starts_with (list_t *node, char *prefix, char c);
ssize_t get_node_index (list_t *head, list_t *node);

/* chain.c */
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);

char *_strncpy(char *dest, char *src, int n);

/* main.h */
void _puts(char *argv);
int _putchar(char cat);
char *_strdup(const char *str);
char *_strcpy(char *cat, char *kitty);
char *_strncat(char *cat, char *kitty, int num);
char *_strncpy(char *cat, char *kitty, int num);
char *_strchr(char *p, char x);
int _strlength(char *);
void _commentremover(char *cat);
void filemode(char *);
void interactivemode(char *argv);
int _putchar(char);

#define LENGTH_COMMAnd 1024
#define NEGATIVE -1
#define BUF_Wr_ON 5000
#define BUF_RD_ON 5000

#endif /* SHELL_H */

builtin_emulators.c
#include "shell.h"
/**
 * _myexit - exit the program
 * @info: struct contain the arguments
 * Return: the error number
*/
int _myexit (info_t *info)
{
	int exitchek;

	if (info->argv[1])
	{
		exitchek = _erratoi(info->argv[1]);
		if (exitchek == -1)
		{
			info->status = 2;
			print_error(info, "Illegal numbers: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
		}
	info->err_num = _erratoi(info->argv[1]);
	return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _mycd - change the current directory
 * @info: struct include the arguments
 * Return: 0
*/
int _mycd (info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
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
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdir_ret = chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
	chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]), _putchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD"));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 *_myhelp - change the directory
 *@info: struct contain the arguments
 *Return: 0 
*/
int _myhelp (info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("help call works, Function not yet implemented \n");
	if (0)
		_puts(*arg_array);
	return (0);
}
builtin_emulators2.c
#include "shell.h"

/**
 * _myhistory - print the history of used commands
 * @info: struct include the arguments
 * Return: 0
*/
int _myhistory (info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - remove alias
 * @info: first parameter
 * @str: seconed parameter
 * Return: 0 or 1
*/
int unset_alias(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_at_index(&(info->alias),
	get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*p = c;
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
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(info, str));
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
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - mimics the alias builtin
 * @info: struct contain the arguments
 * Return: 0
*/
int _myalias (info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = _strchr(info->argv[i], '=');
		if (p)
		set_alias(info, info->argv[i]);
		else
		print_alias(node_starts_with(info->alias, info->argv[i], '='));
	}
	return (0);
}
chain.c
#include "shell.h"

/**
 * is_chain - check the char if it is a chain
 * @info: first parameter
 * @buf: seconed one
 * @p: third one
 * Return: 1 or 0
*/
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j+1] == '&')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';')
	{
		buf[j] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
	return (0);
	*p = j;
	return (1);
}

/**
 * check_chain - check the last status
 * @info: first parameter
 * @buf: seconed one
 * @p: pointer 
 * @i: start of the buf
 * @len: size of the buf
 * Return: Don't return anything
*/
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;
	(void) i;
	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[j] = 0;
			j = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (info->status)
		{
			buf[j] = 0;
			j = len;
		}
	}
	*p = j;
}

/**
 * replace_alias - replace an alias 
 * @info: struct include arguments
 * Return: 1 or 0
*/
int replace_alias(info_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if(!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - replace one vars
 * @info: struct
 * Return: 1 or 0
*/
int replace_vars(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;
		if (!_strcmp(info->argv[i], "$?"))
		{
			replace_string(&(info->argv[i]),
			_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[i], "$$"))
		{
			replace_string(&(info->argv[i]),
			_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[i][1], '=');
		if (node)
		 {
			replace_string(&(info->argv[i]),
			_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&(info->argv[i]),_strdup(""));
	}
	return (0);
}

/**
 * replace_string - change the string
 * @old: first parameter
 * @new: second one
 * Return: 1 or 0
*/
int replace_string(char **old, char *new)
{
	free(*old);

	*old = new;

	return (1);
}
env.c
#include"shell.h"

/**
 * _myenv - prints the current environment
 * @info: Structure containing potential arguments.
 * Used to maintain constant function prototype.
 * Return: Always O
*/
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - gets the value of an environ variable
 * @info: Structure containing potential arguments
 * 		Used to maintain
 * @name: env var name
 * Return: the value
*/
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - Initialize a new environment variable,
 * or modify an existing one
 * @info: Structure containing potential arguments.
 * Used to maintain constant function prototype.
 * Return: Always O
 */
int _mysetenv (info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
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
		_unsetenv(info, info->argv[i]);
	return (0);
}

/**
 * populate_env_list - populates env linked list.
 * Used to maintain constant function prototype.
 * @info: Structure containing potential arguments.
 * Used to maintain constant function prototype.
 * Return: Always 0
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}
env2.c
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
 * _unsetenv - Remove an environment variable
 * @info: Structure containing potential arguments.
 * Used to maintain constant function prototype.
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
		return (0);

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
	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}
err_strings_functions.c
#include "shell.h"

/**
 * _eputs - print a string to the standered error
 * @str: pointer to the string
 * Return: void
*/
void _eputs(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_eputchar(str[i]);
		i++;
	}
}

/**
 * _eputchar - print one characther to the standered error
 * @c: charachter to be printed
 * Return: the bytes we will print
*/
int _eputchar(char c)
{
	static char buf[WRITE_BUF_SIZE];
	static int i;

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * _putfd - print a one char to specific place
 * @c: characther to be printed
 * @fd: where we will print
 * Return: 1 
*/
int _putfd(char c, int fd)
{
	static char buf[WRITE_BUF_SIZE];
	static int i;

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * _putsfd - print a string to specific place
 * @str: pointer to string to be printed
 * @fd: where we will print
 * Return: the string printed
*/
int _putsfd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += _putfd(*str++, fd);
	}
	return (i);
}
file_io_functions.c
#include"shell.h"

/**
 * get_history_file gets the history file
 * @info: parameter struct
 * Return: allocated string containg history file
*/
char *get_history_file (info_t *info)
{
	char *buf, *dir;

	dir = _getenv(info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlength(dir) + _strlength(HIST_FILE) + 2));
	if (buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * write_history - creates a file, or appends to an existing file
 * @info: the parameter struct
 * Return: 1 on success, else -1
 */
int write_history(info_t *info)
{
	ssize_t fd;
	char *filename = get_history_file(info);
	list_t *node = NULL;

	if (filename)
		return (-1);
	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history - reads history from file
 * @info: the parameter struct
 * Return: histcount on success, 0 otherwise
*/
int read_history (info_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize= 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(info);

	if (!filename)
		return (0);
	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat (fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close (fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			build_history_list(info, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		build_history_list(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history_list - adds entry to a history linked list
 * @info: Structure containing potential arguments
 * Used to maintain
 * @buf: buffer
 * @linecount: the history linecount, histcount
 * Return: Always O
*/
int build_history_list (info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buf, linecount);
	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renumber_history - renumbers the history linked list after changes
 * @info: Structure containing potential arguments.
 * Used to maintain
 * Return: the new histcount
*/
int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (info->histcount = i);
}
getline.c
#include "shell.h"

/**
 * input_buf - buffers chaind commands
 * @info: first member
 * @buf: second one
 * @len: third member
 * Return: bytes read
*/
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
	#if USE_GETLINE
		r = getline(buf, &len_p, stdin)
	#else
		r = _getline(info, buf, &len_p);
	#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0';
				r--;
			}
			info->linecount_flag = 1;
			_commentremover(*buf);
			build_history_list(info, *buf, info->histcount++);
			/* if (_strchr(*buf, ';')) is a cmmand chain?*/
			{
				*len = r;
				info->cmd_buf = buf;
			}
		}
	}
	return (r);
}
/**
 * get_input - gets a line minus the new line
 * 
 * @info: first parameter
 * 
 * Return: bytes read
*/
ssize_t get_input(info_t *info)
{
	static char *buf;
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;
	_putchar(BUF_FLUSH);
	r = input_buf(info, &buf, &len);
	if (r == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = buf + i;
		check_chain(info, buf, &j, i, len);
		while (j < len)
		{
			if (is_chain(info, buf, &j))
				break;
			j++;
		}
		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}
		*buf_p = p;
		return (_strlength(p));
	}
	*buf_p = buf;
	return (r);
}
/**
 * read_buf - read a buffer
 * @info: first member
 * @buf: seconed one
 * @i: third one
 * 
 * Return: r
*/
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	size_t r = 0;

	if (*i)
		return (0);
	r = read(info->readfd, buf, READ_BUF_SIZE);
	if (r > 0)
		*i = r;
	return (r);
}

/**
 * _getline - read the line from stdin
 * @info: first member
 * @ptr: seconed one
 * @length: third one
 * Return: s
*/
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;
	p = *ptr;

	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;
	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 1 && len == 0))
		return (-1);
	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int) (c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);
	if (s)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i +1);
	s += k = i;
	i = k;
	p = new_p;
	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - blocks ctrl+c
 * @sig_num: the signal number
 * 
 * Return: void
*/
void sigintHandler(__attribute__((unused)) int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}