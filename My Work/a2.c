hsh.c
#include "shell.h"
/**
 * find_builtin - finds a builtin command
 * 
 * @info: struct include arguments
 * 
 * Return: -1 or 0 or -2 or 1
*/
int find_builtin(info_t *info)
{
	int i, built_in_ret = -1;

	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsentenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[i].func(info);
		}
	return (built_in_ret);
}

/**
 * find_cmd - finds a command in path
 * @info: struct argument
 * Return: void
*/
void find_cmd(info_t *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];

	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, k = 0; info->argv[i]; i++)
		if (!is_delim(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;
	path = find_path(info, _getenv(info, "PATH= "), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH=") ||
			info->argv[0][0] == '/' )&&  is_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * fork_cmd - forks a process
 * @info: struct include arguments
 * Return: void
*/
void fork_cmd(info_t *info)
{
	pid_t child_pid;
	child_pid = fork();

	if (child_pid == -1)
	{
		perror("Error: ");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission donied\n");
		}
	}
}

info.c
#include"shell.h"

/**
 * clear_info - initializes info_t struct
 * @info: struct address
*/
void clear_info (info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * set info - initializes info_t struct
 * @info: struct address
 * @av: argument vector
 */
void set_info (info_t *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		else
		{
			info->argv[0] = strtok_custom(info->arg, " \t");
		}

		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;
		replace_alias(info);
		replace_vars(info);
	}
}


/**
 * free_info - frees info_t struct fields
 * @info: struct address
 * @all: true if freeing all fields
*/
void free_info (info_t *info, int all)
{
	ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			free_list(&(info->env));
		if (info->history)
			free_list(&(info->history));
		if (info->alias)
			free_list(&(info->alias));
		ffree (info->environ);
			info->environ = NULL;
		bfree ((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}
liststr.c
#include "shell.h" 
/**
 * add_node - adds a node to the start of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 * Return: size of list
*/
list_t *add_node (list_t **head, const char *str, int num)
{
	list_t *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof (list_t));
	if (!new_head)
		return (NULL);
	_memset((void *) new_head, 0, sizeof(list_t));
	new_head->num = num;
	if (str)
	{
		new_head->str = _strdup(str);
		if (!new_head->str)
		{
			free (new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * add_node_end - adds a node to the end of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 * Return: size of list
*/
list_t *add_node_end (list_t **head, const char *str, int num)
{
	list_t *new_node, *node;

	if (!head)
		return (NULL);
	node = *head;
	new_node = malloc(sizeof (list_t));
	if (!new_node)
		return (NULL);
	_memset((void *) new_node, 0, sizeof(list_t));
	new_node->num = num;
	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free (new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * print_list_str - prints only the str element of a list_t linked list
 * @h: pointer to first node
 * Return: size of list
*/
size_t print_list_str (const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts (h->str ? h->str : "(nil)");
		_puts ("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * deleternode_at_index - deletes node at given index
 * @head: address of pointer to first node
 * @index: index of node to delete
 * Return: 1 on success, 0 on failure
*/
int delete_node_at_index (list_t **head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);
	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_list - frees all nodes of a list
 * @head_ptr: address of pointer to head node 
 * Return: void
*/
void free_list (list_t **head_ptr)
{
	list_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}
liststr2.c
#include "shell.h" 

/**
 * list_len - get the length of the list
 * @head: pointer to the list
 * Return: the length 
*/
size_t list_len(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * list_to_strings - print all elements in a list
 * @head: pointer to the struct
 * Return: the count of the node
*/
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t i = list_len(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc (_strlength(node->str) + 1);
		if (!str)
		{
			for (j=0; j < i; j++)
				free (strs[j]);
			free (strs);
			return (NULL);
		}
		str = _strcpy(str, node->str);
		strs[i]= str;
	}
	strs[i] = NULL;
	return (strs);
}

/**
 * print_list - printa a const list
 * @head: pointer to the list
 * Return: count of the bytes
*/
size_t print_list(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * ode_starts_with - returns node whose string starts with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 * Return: match node or null
*/
list_t *node_starts_with (list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * Jet_node_index gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 * Return: index of node or -1
*/
ssize_t get_node_index (list_t *head, list_t *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}
test.c
#include "shell.h"

void execute_command(char *command, int interactive)
{
	pid_t pid;
	char *args[READ_BUF_SIZE];
	int i = 0;

	char *token = strtok_custom(command, " \n");
	while (token != NULL && i < READ_BUF_SIZE- 1)
	{
		args[i++] = token;
		token = strtok_custom(NULL, " \n");
	}
	args[i] = NULL;

	if (args[0] == NULL)
	{
		return;
	}

	if (_strcmp(args[0], "exit") == 0)
	{
		if (interactive)
			exit(EXIT_SUCCESS);
	}

	if (_strcmp(args[0], "cd") == 0)
	{
		if (args[1] == NULL)
		{
			fprintf(stderr, "cd: missing argument\n");
			return;
		}
		if (chdir(args[1]) != 0)
		{
			perror("chdir");
		}

		return;
	}

	if (_strcmp(args[0], "pwd") == 0)
	{
		char cwd[READ_BUF_SIZE];
		if (getcwd(cwd, sizeof(cwd)) != NULL)
		{
			printf("%s\n", cwd);
		}
		else
		{
			perror("getcwd");
		}
		return;
	}
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		execvp(args[0], args);
		perror("execvp");
		exit(EXIT_FAILURE);
	}
	else
	{
		int status;
		if (interactive)
			waitpid(pid, &status, 0);
	}
}
void non_interactive()
{
	char buffer[BUF_Wr_ON];

	while (1) {
		fflush(stdout);

		if (fgets(buffer, BUF_Wr_ON, stdin) == NULL) {
			break;
		}

		buffer[strcspn(buffer, "\n")] = '\0';

		if (_strcmp(buffer, "exit") == 0)
			break;
		execute_command(buffer, 1);
	}
}
void interactive_mode()
{
	char buffer[BUF_Wr_ON];

	while (1) {
		printf("($) ");
		fflush(stdout);

		if (fgets(buffer, BUF_Wr_ON, stdin) == NULL) {
			printf("\n");
			break;
		}

		buffer[strcspn(buffer, "\n")] = '\0';

		if (_strcmp(buffer, "exit") == 0)
			break;
		execute_command(buffer, 1);
	}
}

int main(int argc, char *argv[]) {
	char buffer[BUF_Wr_ON];
	int interactive = isatty(STDIN_FILENO);

	if (argc > 1)
	{
		FILE *file = fopen(argv[1], "r");
		if (!file) {
			perror("Error opening file");
			exit(EXIT_FAILURE);
		}
		while (fgets(buffer, BUF_Wr_ON, file) != NULL)
		{
			buffer[strcspn(buffer, "\n")] = '\0';
			execute_command(buffer, interactive);
		}
		fclose(file);
	}
	else
	{
		if (interactive)
		{
			interactive_mode();
		} else {
			non_interactive();
		}
	}
	return (0);
}

memory_functions.c
#include "shell.h"

/**
 ** memset fills memory with a constant byte *
 * @s: the pointer to the memory area
 * @b: the byte to fill *s with
 * @n: the amount of bytes to be filled
 * Return: (s) a pointer to the memory area S
*/
char *_memset (char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i]= b;
	return (s);
}

/**
 * ffree frees a string of strings
 * @pp: string of strings
*/
void ffree (char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free (*pp++);
	free (a);
}

/**
 * realloc reallocates a block of memory
 * @ptr: pointer to previous malloc'ated block
 * @old_size: byte size of previous block
 * @new_size: byte size of new block
 * Return: pointer to da ol'block nameen.
*/
void *_realloc (void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc (new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc (new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}
memory_functions2.c
#include "shell.h"

/**
 * bfree frees a pointer and NULLS the address
 * @ptr: address of the pointer to free
 * Return: 1 if freed, otherwise 0.
*/
int bfree (void **ptr)
{
	if (ptr && *ptr)
	{
		free (*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
more_functions.c
#include"shell.h"

/**
 * interactive - returns true if shell is interactive mode
 * @info: struct address
 * Return: 1 if interactive mode, 0 otherwise
 */
int interactive (info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim checks if character is a delimeter
 * @c: the char to check
 * @delim: the delimeter string
 * Return: 1 if true, 0 if false
*/
int is_delim (char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * isalpha- checks for alphabetic character
 * @c: The character to input
 * Return: 1 if c is alphabetic, 0 otherwise
*/
int isalpha (int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
*/
int _atoi (char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0; s[i] != '\0' && flag != 2; i++)
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
more_functions2.c
#include"shell.h"

/**
 * erratoi - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise -1 on error
 */
int _erratoi(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;
	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_error prints an error message
 * @info: the parameter & return info struct
 * @estr: string containing specified error type
 * Return: 0 if no numbers in string,
 * converted number otherwise -1 on error
*/
void print_error (info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_d = function prints a decimal (integer) number (base 10)
 * @input: the input
 * @fd: the filedescriptor to write to
 * Return: number of characters printed
*/
int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar ('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar ('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar ('0' + current);
	count++;
	return (count);
}


/**
 * convert_number - converter function,
 * a clone of itoa
 * @num: number
 * @base: base
 * @flags: argument flags
 * Return: string
*/
char *convert_number (long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign  = '-';
	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';
	do {
		*--ptr = array [n % base];
		n /= base;
	} while (n != 0);
	if (sign)
		*--ptr = sign;
	return (ptr);
}

void _commentremover(char *cat)
{
	int c = 0;
	while (cat[c] != '\0')
	{
		if(cat[c] == '#')
		{
			cat[c] = '\0';
			break;
		}
		else if (!c || cat[c - 1] == ' ')
		{
			cat[c] = '\0';
			break;
		}
		c++;
	}
}
path.c
#include "shell.h"

/**
 * is_cmd - check if the command is executable
 * @info: struct include the arguments
 * @path: path of the file
 * Return: 1 or 0
*/
int is_cmd(info_t *info, char *path)
{
	struct stat st;
	(void)info;

	if (!path || stat(path, &st) != 0)
		return (0);
	if (S_ISREG(st.st_mode))
		return (1);
	return (0);
}

/**
 *dup_chars - duplicate char
 *@pathstr: path string
 *@start: index to start
 *@stop: index to stop
 * Return: pointer
*
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	buf[k] = 0;
	return (buf);
}*/
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	if (!pathstr)
		return (NULL);
	if (start < 0 || stop > _strlength(pathstr))
		return (NULL);

	for (k = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	buf[k] = 0;
	return (buf);
}

/**
 * findpath - find the cmd in the path
 * @info: struct include the arguments
 * @pathstr: the PATH
 * @cmd: what we will search
 * Return: the path
*/
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlength(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = dup_chars(pathstr, curr_pos, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathstr[i])
				break;
			curr_pos = i + 1;  
		}
		i++;
	}
	return (NULL);
}
string_functions1.c
#include "shell.h"

/**
 * _strlen - Write a function that returns the length of a string.
 * @s: string parameter input
 * Return: length string
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
 * _strcmp - a function that compares two strings
 * @s1: string 1 input to compare
 * @s2: against this other string 2
 * Return: 0 / postive / negative
*/

int _strcmp(char *s1, char *s2)
{
	int i;
	int result = 0;

	for (i = 0; s1[i] != '\0' && result == 0; i++)
	{
		result = s1[i] - s2[i];
	}
	return (result);
}

/**
 * start_with - chaecks if needle starts with haystack
 * @haystack: string to seach
 * @needle: substring to find
 * Return: address
*/
char *starts_with(const char *cat, const char *kitty)
{
	while (*kitty)
	{
		if (*kitty != *cat)
			return NULL;
		kitty++;
		cat++;
	}
	return (char *)cat;
}

/**
 * _strcat - Write a function that concatenates two strings.
 * @dest: pointer to destnation input
 * @src: pointer to source input
 * Return: pointer to resulting string @dest
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
string_functions2.c
#include "shell.h"

int _putchar(char cat)
{
	static int count;
	static char BUF[BUF_Wr_ON];

	if (cat == NEGATIVE || count >= BUF_Wr_ON)
	{
		write(1, BUF, count);
		count = 0;
	}
	if (cat != BUF_FLUSH)
		BUF[count++] = cat;
	return (1);
}

void _puts(char *argv)
{
	int x;

	for (x = 0; argv[x] != '\0'; x++)
		_putchar(argv[x]);
}

char *_strdup( const char *str) /*dublicate a string*/
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

char *_strcpy(char *cat, char *kitty)
{
	int x = 0;

	if (cat == kitty || kitty == 0)
		return (cat);
	for (; kitty[x] != '\0'; x++)
		cat[x] = kitty[x];
	cat[x] = '\0';
	return (cat);
}
string_functions3.c
#include "shell.h"

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
string_functions4.c
#include "shell.h"

int _strspn(const char *str, const char *accept) {
    int i, j;

    for (i = 0; str[i] != '\0'; i++) {
        for (j = 0; accept[j] != '\0'; j++)
        {
            if (str[i] == accept[j])
                break;
        }
        if (accept[j] == '\0')
            return i;
    }
    return i;
}

char *_strpbrk(char *str, const char *accept)
{
    int i, j;
    for (i = 0; str[i] != '\0'; i++) {
        for (j = 0; accept[j] != '\0'; j++)
        {
            if (str[i] == accept[j])
                return &str[i];
        }
    }
    return NULL;
}

char *strtok_custom(char *str, const char *delimiters)
{
	char *token;
    static char *next_token = NULL;

    if (str != NULL)
    {
        next_token = str;
    }
    else if (next_token == NULL)
    {
        return (NULL);
    }
    next_token += _strspn(next_token, delimiters);
    if (*next_token == '\0')
    {
        next_token = NULL;
        return (NULL); 
    }
    token = next_token;
    next_token = _strpbrk(next_token, delimiters);
    if (next_token != NULL)
    {
        *next_token = '\0';
        next_token++;
    }
    return (token);
}