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
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <elf.h>
#include <elf.h>
#include <sys/types.h>
#include <sys/wait.h>

#define READ_BUF_SIZE 1024
#define write_BUF_SIZE 1024
#define BUF_FLUSH -1

#define CMD_NORM    0
#define CMD_OR      1
#define CMD_AND		2
#define CMD_CHAIN	3

#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_FILE	4096

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

/* comments */
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

	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
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

/* err_string_functions.c*/
void _myputs(char *cat);
int _myputchar(char cat);
int _myputinto(char i, int place);
int _myputsinto(char *cat, int place);

/* string_functions.c*/
int _strlen(char *s);
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
char *_strtow(char *, char *);
char *_strtow2(char *, char);

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

/*builtin_emulators.c*/
int _myexit (info_t *);
int _mycd (info_t *);
int _myhelp (info_t *);

/* builtin_emulators2.c*/
int _myhistory (info_t *);
int _myalias (info_t *);

/*linkedlist.c*/
char **convert_tostring (list_t *head);
list_t *add_node(list_t **head, const char *str);
list_t *add_node_end(list_t **head, const char *str);
void free_list(list_t*head);
int delete_nodeint_at_index(list_t **head, unsigned int index);

/*list2*/
size_t get_listleng(const list_t *head);
size_t print_stringlist(const list_t *h);
size_t _puts_list(const list_t *head);
ssize_t _getindex (list_t *head, list_t *kitty);
list_t *startofnode (list_t *kitty, char *start, char cat);

#endif /* SHELL_H */