#include "shell.h"

/**
 * handle_input- handle buffer
 * 
 * @info: first parameter
 * 
 * @buffer: seconed one
 * 
 * @length: third one
 *
 * Return: the input
 */
ssize_t handle_input(info_t *info, char **buffer, size_t *length)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*length)
	{
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, handle_sign);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = _getline(info, buffer, &len_p);
#endif
		if (r > 0)
		{
			if ((*buffer)[r - 1] == '\n')
			{
				(*buffer)[r - 1] = '\0';
				r--;
			}
			info->linecount_flag = 1;
			remove_comments(*buffer);
			create_history_list(info, *buffer, info->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*length = r;
				info->cmd_buf = buffer;
			}
		}
	}
	return (r);
}

/**
 * get_input - read from a line
 * 
 * @info: pointer to struct
 *
 * Return: bytes read
 */
ssize_t get_input(info_t *info)
{
	static char *buffer;
	static size_t i, j, length;
	ssize_t r = 0;
	char **buf_g = &(info->arg), *p;
	_putchar(BUF_FLUSH);
	r = handle_input(info, &buffer, &length);
	if (r == -1)
		return (-1);
	if (length)
	{
		j = i;
		p = buffer + i; 

		check_chain(info, buffer, &j, i, length);
		while (j < length) 
		{
			if (is_chain(info, buffer, &j))
				break;
			j++;
		}

		i = j + 1; 
		if (i >= length) 
		{
			i = length = 0;
			info->cmd_buf_type = CMD_NORM;
		}
		*buf_g = p;
		return (_strlength(p));
	}

	*buf_g = buffer;
	return (r);
}

/**
 * buffer_reading- buffer reading
 * 
 * @info: pointer to struct
 * 
 * @buffer: buffer
 * 
 * @size: size
 *
 * Return: x
 */
ssize_t buffer_reading(info_t *info, char *buffer, size_t *size)
{
	ssize_t x = 0;
	if (*size)
		return (0);
	x = read(info->readfd, buffer, READ_BUF_SIZE);
	if (x >= 0)
		*size = x;
	return (x);
}
/**
 * _getline - read from line
 * 
 * @info: pointer to struct
 * 
 * @buffer: pointer of pointer
 * 
 * @length: length of line
 *
 * Return: s
 */
int _getline(info_t *info, char **buffer, size_t *length)
{
	static size_t i, len;
	static char buf[READ_BUF_SIZE];
	ssize_t r = 0, s = 0;
	size_t k;
	char *p = NULL, *new_p = NULL, *c;
	p = *buffer;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = buffer_reading(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p) 
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

s += k - i;
i = k;
p = new_p;
	if (length)
		*length = s;
	*buffer = p;
	return (s);
}
/**
 * handle_sign - handle ctrl-C
 * 
 * @sig: void integer
 *
 * Return: void
 */
void handle_sign(int sig)
{
	(void) sig;
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

#include "shell.h"
/**
 * start_history - get file of history
 * 
 * @info: pointer to the struct
 *
 * Return: pointer
 */
char *start_history(info_t *info)
{
	char *buffer, *x;
	x = _getenv(info, "HOME=");
	if (!x)
		return (NULL);
	buffer = malloc(sizeof(char) * (_strlength(x) + _strlength(HIST_FILE) + 2));
	if (!buffer)
		return (NULL);
	buffer[0] = 0;
	_strcpy(buffer, x);
	_strcat(buffer, "/");
	_strcat(buffer, HIST_FILE);
	return (buffer);
}
/**
 * history_writing- creat or append a file
 * 
 * @info: pointer to the struct
 *
 * Return: 1 or-1
 */
int history_writing(info_t *info)
{
	ssize_t file;
	char *filename = start_history(info);
	list_t *cat = NULL;
	if (!filename)
		return (-1);

	file = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (file == -1)
		return (-1);
	for (cat = info->history; cat; cat = cat->next)
	{
		_putsfd(cat->str, file);
		_putfd('\n', file);
	}
	_putfd(BUF_FLUSH, file);
	close(file);
	return (1);
}
/**
 * history_reading - reads history 
 * 
 * @info: pointer to a struct
 *
 * Return: histcount 
 */
int history_reading(info_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t file, reading, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = start_history(info);

	if (!filename)
		return (0);

	file = open(filename, O_RDONLY);
	free(filename);
	if (file == -1)
		return (0);
	if (!fstat(file, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	reading = read(file, buf, fsize);
	buf[fsize] = 0;
	if (reading <= 0)
		return (free(buf), 0);
	close(file);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			create_history_list(info, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		create_history_list(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	history_renum(info);
	return (info->histcount);
}

/**
 * create_history_list - make a list to handle the history
 * 
 * @info: first parameter
 * 
 * @buffer: seconed one
 * 
 * @count: third one
 *
 * Return: (0)
 */
int create_history_list(info_t *info, char *buffer, int count)
{
	list_t *cat = NULL;

	if (info->history)
		cat = info->history;
	add_node_end(&cat, buffer, count);

	if (!info->history)
		info->history = cat;
	return (0);
}
/**
 * history_renum - update the history
 * 
 * @info: pointer to Struct
 *
 * Return: the new histcount
 */
int history_renum(info_t *info)
{
	list_t *cat = info->history;
	int x = 0;
	while (cat)
	{
		cat->num = x++;
		cat = cat->next;
	}
	return (info->histcount = x);
}

#include "shell.h"
/**
 * add_node_head - add new node to the head
 * 
 * @head: pfirst member
 * 
 * @string: seconed one
 * 
 * @n: third one
 *
 * Return: size of list
 */
list_t *add_node_head(list_t **head, const char *string, int n)
{
	list_t *new;

	if (!head)
		return (NULL);
	new = malloc(sizeof(list_t));
	if (!new)
		return (NULL);
	_memset((void *)new, 0, sizeof(list_t));
	new->num = n;
	if (string)
	{
		new->str = _strdup(string);
		if (!new->str)
		{
			free(new);
			return (NULL);
		}
	}
	new->next = *head;
	*head = new;
	return (new);
}

/**
 * add_node_end - add b=node to the tail
 * 
 * @head: pfirst member
 * 
 * @string: seconed one
 * 
 * @n: third one
 *
 * Return: size of list
 */
list_t *add_node_end(list_t **head, const char *string, int n)
{
	list_t *new_cat, *cat;
	if (!head)
		return (NULL);
	cat = *head;
	new_cat = malloc(sizeof(list_t));
	if (!new_cat)
		return (NULL);
	_memset((void *)new_cat, 0, sizeof(list_t));
	new_cat->num = n;
	if (string)
	{
		new_cat->str = _strdup(string);
		if (!new_cat->str)
		{
			free(new_cat);
			return (NULL);
		}
	}
	if (cat)
	{
		while (cat->next)
			cat = cat->next;
		cat->next = new_cat;
	}
	else
		*head = new_cat;
	return (new_cat);
}
/**
 * print_list_str - print specific element
 * 
 * @head: pointer to first node
 *
 * Return: the list
 */
size_t print_list_str(const list_t *head)
{
	size_t x = 0;
	while (head)
	{
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
		head = head->next;
		x++;
	}
	return (x);
}
/**
 * delete_node_at_index - delete specific node
 * 
 * @h: pointer of pointer
 * 
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_index(list_t **h, unsigned int index)
{
	list_t *cat, *prev_cat;
	unsigned int i = 0;

	if (!h || !*h)
		return (0);

	if (!index)
	{
		cat = *h;
		*h = (*h)->next;
		free(cat->str);
		free(cat);
		return (1);
	}
	cat = *h;
	while (cat)
	{
		if (i == index)
		{
			prev_cat->next = cat->next;
			free(cat->str);
			free(cat);
			return (1);
		}
		i++;
		prev_cat = cat;
		cat = cat->next;
	}
	return (0);
}
/**
 * list_free - free the nodes of list
 * 
 * @ptr: pointer to list
 *
 * Return: void
 */
void list_free(list_t **ptr)
{
	list_t *cat, *next_node, *head;

	if (!ptr || !*ptr)
		return;
	head = *ptr;
	cat = head;
	while (cat)
	{
		next_node = cat->next;
		free(cat->str);
		free(cat);
		cat = next_node;
	}
	*ptr = NULL;
}

#include "shell.h"

/**
 * list_length - get the length of a list
 * 
 * @head: pointer to the list
 *
 * Return: the length of list
 */
size_t list_length(const list_t *head)
{
	size_t count = 0;

	while (head)
	{
		head = head->next;
		count++;
	}
	return (count);
}

/**
 * list_to_strings - convert a list to string
 * 
 * @h: pointer to the list
 *
 * Return: array
 */
char **list_to_strings(list_t *h)
{
	list_t *cat = h;
	size_t x = list_length(h), y;
	char **strs;
	char *str;

	if (!h || !x)
		return (NULL);
	strs = malloc(sizeof(char *) * (x + 1));
	if (!strs)
		return (NULL);
	for (x = 0; cat; cat = cat->next, x++)
	{
		str = malloc(_strlength(cat->str) + 1);
		if (!str)
		{
			for (y = 0; y < x; y++)
				free(strs[y]);
			free(strs);
			return (NULL);
		}
		str = _strcpy(str, cat->str);
		strs[x] = str;
	}
	strs[x] = NULL;
	return (strs);
}
/**
 * print_list - print the element of a list
 * 
 * @head: pointer to list
 *
 * Return: the list
 */
size_t print_list(const list_t *head)
{
	size_t count = 0;
	while (head)
	{
		_puts(convert_number(head->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
		head = head->next;
		count++;
	}
	return (count);
}

/**
 * node_starts_with - get a node
 * 
 * @cat: pointer to the list
 * 
 * @pref: string
 * 
 * @ch: char
 *
 * Return: match node or null
 */
list_t *node_starts_with(list_t *cat, char *pref, char ch)
{
	char *p = NULL;

	while (cat)
	{
		p = starts_with(cat->str, pref);
		if (p && ((ch == -1) || (*p == ch)))
			return (cat);
		cat = cat->next;
	}
	return (NULL);
}

/**
 * get_node_index - get an index
 * 
 * @head: first member
 * 
 * @cat: seconed
 *
 * Return: index of node or -1
 */
ssize_t get_node_index(list_t *head, list_t *cat)
{
	size_t index = 0;

	while (head)
	{
		if (head == cat)
			return (index);
		head = head->next;
		index++;
	}
	return (-1);
}

#include "shell.h"
/**
 * main - start
 * 
 * @argc: count of arguments
 * 
 * @argv: arguments
 *
 * Return: 0
 */
int main(int argc, char **argv)
{
	info_t info[] = { INFO_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fd)
		: "r" (fd));

	if (argc == 2)
	{
		file_mode(argv, info);
	}
	populate_env_list(info);
	history_reading(info);
	execute_command(info, argv);
	return (EXIT_SUCCESS);
}

#include "shell.h"

/**
 * free_pointer - free  pointeres
 * 
 * @cat: pointer
 *
 * Return: 1 or 0
 */
int free_pointer(void **cat)
{
	if (cat && *cat)
	{
		free(*cat);
		*cat = NULL;
		return (1);
	}
	return (0);
}

#include "shell.h"
/**
 * is_command - check if it is command
 * 
 * @info: pointer to struct
 * 
 * @place: the path
 *
 * Return: 1 if true, 0 otherwise
 */
int is_command(info_t *info, char *place)
{
	struct stat ls;
	(void)info;
	if (!place || stat(place, &ls))
		return (0);

	if (ls.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}
/**
 * char_duplicate - dublicate a char
 * 
 * @place: path
 * 
 * @x: start
 * 
 * @y: stop
 *
 * Return: pointer to new buffer
 */
char *char_duplicate(char *place, int x, int y)
{
	static char buffer[1024];
	int i = 0, k = 0;
	for (k = 0, i = x; i < y; i++)
		if (place[i] != ':')
			buffer[k++] = place[i];
	buffer[k] = 0;
	return (buffer);
}
/**
 * path_finder - find the path
 * 
 * @info: struct
 * 
 * @place: string
 * 
 * @commandd: commandd to find the path
 *
 * Return: full path
 */
char *path_finder(info_t *info, char *place, char *commandd)
{
	int i = 0, p = 0;
	char *path;
	if (!place)
		return (NULL);
	if ((_strlength(commandd) > 2) && starts_with(commandd, "./"))
	{
		if (is_command(info, commandd))
			return (commandd);
	}
	while (1)
	{
		if (!place[i] || place[i] == ':')
		{
			path = char_duplicate(place, p, i);
			if (!*path)
				_strcat(path, commandd);
			else
			{
				_strcat(path, "/");
				_strcat(path, commandd);
			}
			if (is_command(info, path))
				return (path);
			if (!place[i])
				break;
			p = i;
		}
		i++;
	}
	return (NULL);
}

#include "shell.h"
/**
*_memset - fills memory with a constant byte
*
*@s: pointer to the area we will fill
*
*@b: char contain the data
*
*@n: uninsigned int to start with
*
*Return: (*S)
*/
char *_memset(char *s, char b, unsigned int n)
{
int i = 0;
	while (n > 0)
{
	s[i] = b;
	i++;
	n--;
}
	return (s);
}
/**
 * free_string - free memory
 * 
 * @ptr: pointer to the string
 * 
 * Return: void
 */
void free_string(char **ptr)
{
	char **s = ptr;

	if (!ptr)
		return;
	while (*ptr)
		free(*ptr++);
	free(s);
}
/**
*_realloc - reallocates a memory block using malloc and free
*
*@ptr: pointer
*
*@old_size: the size we will change
*
*@new_size: the new size
*
*Return: (ptr or NULL)
*/
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
void *rptr;
	if (new_size == old_size)
		return (ptr);
	if (ptr == NULL)
		return (malloc(new_size));
	if (new_size == 0 && ptr != NULL)
{
		free(ptr);
		return (NULL);
}
rptr = malloc(new_size);
	if (new_size > old_size)
		memcpy(rptr, ptr, old_size);
	else
		memcpy(rptr, ptr, new_size);
	free(ptr);
	return (rptr);
}
#include "shell.h"
/**
* file_mode - to execute from a file
*
*@av: argument
*
*@info: pointer to the struct
*
*Return: which in the file
*/
int file_mode(char **av, info_t *info)
{
    	int fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(av[0]);
				_eputs(": 0: Can't open ");
				_eputs(av[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fd;
        return (EXIT_SUCCESS);
}
/**
* execute_command - to check the input
* 
* @info: the parameter & return info struct
*
* @argv: the argument vector from main()
*
* Return: 0 or 1
*/
int execute_command(info_t *info, char **argv)
{
	ssize_t r = 0;
	int x = 0;

	while (r != -1 && x != -2)
	{
		delete_info(info);
		if (interactive(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		r = get_input(info);
		if (r != -1)
		{
			init_info(info, argv);
			x = check_builtin(info);
			if (x == -1)
				command_placeholder(info);
		}
		else if (interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}
	history_writing(info);
	free_info(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (x == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (x);
}
/**
 * check_builtin - execute the builtin command
 * 
 * @info: pointer to the struct
 *
 * Return: -1 or 0 or 1 or -2
 */
int check_builtin(info_t *info)
{
	int x, built_execut = -1;
	builtin_table builtcommand[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (x = 0; builtcommand[x].type; x++)
		if (_strcmp(info->argv[0], builtcommand[x].type) == 0)
		{
			info->line_count++;
			built_execut = builtcommand[x].func(info);
			break;
		}
	return (built_execut);
}

/**
 * fork_command( - fork to execute a command
 * 
 * @info: pointer to thw struct
 *
 * Return: void
 */
void fork_command(info_t *info)
{
	pid_t child;

	child = fork();
	if (child == -1)
	{
		perror("Error:");
		return;
	}
	if (child == 0)
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
				print_error(info, "Permission denied\n");
		}
	}
}

/**
* command_placeholder - finds a command in PATH
*
* @info: pointer to struct
*
* Return: void
*/
void command_placeholder(info_t *info)
{
	int i, k;
	char *place = NULL;
	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!is_delim(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	place = path_finder(info, _getenv(info, "PATH="), info->argv[0]);
	if (place)
	{
		info->path = place;
		fork_command(info);
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH=")
			|| info->argv[0][0] == '/') && is_command(info, info->argv[0]))
			fork_command(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

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
      if (!is_delim(command[i], delim) && (is_delim(command[i + 1], delim) || !command[i + 1]))
          count++;
  if (count == 0)
      return (NULL);
  s = malloc((1 + count) * sizeof(char *));
  if (!s)
      return (NULL);
  for (i = 0, j = 0; j < count; j++)
  {
      while (is_delim(command[i], delim))
          i++;
      k = 0;
      while (!is_delim(command[i + k], delim) && command[i + k])
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

#include "shell.h"
/**
 * new_string - replaces string
 * 
 * @kitty: first member
 * @cat: seconed one
 *
 * Return: 1 
 */
int new_string(char **kitty, char *cat)
{
	free(*kitty);
	*kitty = cat;
	return (1);
}
/**
 * new_alias - change an alias
 * @info: struct
 *
 * Return: 0 or 1
 */
int new_alias(info_t *info)
{
	int x;
	char *ptr;
	list_t *cat;
	for (x = 0; x < 10; x++)
	{
		cat = node_starts_with(info->alias, info->argv[0], '=');
		if (!cat)
			return (0);
		free(info->argv[0]);
		ptr = _strchr(cat->str, '=');
		if (!ptr)
			return (0);
		ptr = _strdup(ptr + 1);
		if (!ptr)
			return (0);
		info->argv[0] = ptr;
	}
	return (1);
}
/**
 * new_vars - replaces vars 
 * 
 * @info: pointer to struct
 *
 * Return: 1 or 0
 */
int new_vars(info_t *info)
{
	int x = 0;
	list_t *cat;
	for (x = 0; info->argv[x]; x++)
	{
		if (info->argv[x][0] != '$' || !info->argv[x][1])
			continue;

		if (!_strcmp(info->argv[x], "$?"))
		{
			new_string(&(info->argv[x]),
				_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[x], "$$"))
		{
			new_string(&(info->argv[x]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		cat = node_starts_with(info->env, &info->argv[x][1], '=');
		if (cat)
		{
			new_string(&(info->argv[x]),
				_strdup(_strchr(cat->str, '=') + 1));
			continue;
		}
		new_string(&info->argv[x], _strdup(""));
	}
	return (0);
}

/**
 * is_chain - check if it is the chain
 * 
 * @info: first member
 * 
 * @cat: seconed member
 * 
 * @ptr: third member
 *
 * Return: 0 or 1
 */
int is_chain(info_t *info, char *cat, size_t *ptr)
{
	size_t i = *ptr;
	if (cat[i] == '|' && cat[i + 1] == '|')
	{
		cat[i] = 0;
		i++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (cat[i] == '&' && cat[i + 1] == '&')
	{
		cat[i] = 0;
		i++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (cat[i] == ';')
	{
		cat[i] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*ptr = i;
	return (1);
}
/**
 * check_chain - check the last status
 * 
 * @info: first parameter
 * @cat: seconed parameter
 * @ptr: third one
 * @x: parameter number 4
 * @length: the length
 *
 * Return: Void
 */
void check_chain(info_t *info, char *cat, size_t *ptr, size_t x, size_t length)
{
	size_t y = *ptr;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			cat[x] = 0;
			y = length;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			cat[x] = 0;
			y = length;
		}
	}
	*ptr = y;
}