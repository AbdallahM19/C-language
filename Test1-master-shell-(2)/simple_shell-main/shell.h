#ifndef SHELL_H
#define SHELL_H

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

#define USE_GETLINE 0
#define USE_STRTOK 0
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3
#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096
#define BUFFER_RD	 1024
#define BUFFER_WR 	1024
#define NEGATTIVE	-1

#define ARGU_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

extern char **environ;

/**
 * struct list - struct of linked list
 *
 * @n: the number field
 *
 * @string: a string
 *
 * @next: pointer
 */
typedef struct list
{
	int n;
	char *string;
	struct list *next;
} list_t;

/**
 *struct holder - control the argumentrmation
 *@arg: first member
 *@argv: seconed
 *@path: control path
 *@argc: count of argument
 *@line_count: counter
 *@err_num: renum
 *@linecount_flag: handle line
 *@fname: filename
 *@env: to handle the environment
 *@environ: copy to env
 *@history: list of the history
 *@alias: list of alias
 *@env_changed: ochange of env
 *@status: status of the command
 *@cmd_buf: pointer
 *@cmd_buf_type: determine the type
 *@readfd: read line
 *@histcount: count of history
 */
typedef struct holder
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
	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} struct_t;

/**
 * struct command - handle the built in command
 * @name: first parameter
 * @job: seconed one
 */
typedef struct command
{
	char *name;
	int (*job)(struct_t *);
} builtin_command;

/*_atoi.c*/
int _atoi(char *num);

/*_strtok.c*/
char **str_tokn(char *command, char *delim);

/*add_node.c*/
list_t *add_node_end(list_t **head, const char *string, int n);
list_t *add_node_head(list_t **head, const char *string, int n);

/*command_built.c*/
int my_exit(struct_t *argument);
int my_cd(struct_t *argument);
int my_help(struct_t *argument);

/*command_built1.c*/
int my_history(struct_t *argument);
int unset_alias(struct_t *argument, char *str);
int set_alias(struct_t *argument, char *str);
int print_alias(list_t *cat);
int my_alias(struct_t *argument);

/*check.c*/
int check_builtin(struct_t *argument);
char *starts_with(const char *cat, const char *kitty);
int is_command(struct_t *argument, char *place);
int alpha_check(int s);
int delim_check(char c, char *d);

/*check1.c*/
int interactive_mode(struct_t *argument);
void check_chain(struct_t *, char *, size_t *, size_t x, size_t l);
int is_chain(struct_t *argument, char *cat, size_t *ptr);

/*compare.c*/
char *_strncat(char *cat, char *kitty, int num);
int _strcmp(char *s1, char *s2);
char *_strcat(char *dest, char *src);

/*convert.c*/
char **list_to_strings(list_t *h);
int convert_string(char *string);
char *convert_number(long int n, int base, int flag);

/*dublicate.c*/
char *char_duplicate(char *place, int x, int y);
char *_strdup(const char *str);

/*environment.c*/
int populate_env_list(struct_t *argument);
int my_unsetenv(struct_t *argument);
int my_setenv(struct_t *argument);
char *get_env(struct_t *argument, const char *name);
int my_env(struct_t *argument);

/*execute.c*/
int execute_command(struct_t *argument, char **argv);
void fork_command(struct_t *argument);
int file_mode(char **av, struct_t *argument);

/*fd.c*/
int print_integer(int num, int file);
int _putfd(char ch, int file);
int _putsfd(char *cat, int file);

/*getenviron.c*/
char **get_environ(struct_t *argument);
int _setenv(struct_t *argument, char *var, char *value);
int _unsetenv(struct_t *argument, char *var);

/*handle.c*/
void handle_sign(int sig);

/*history.c*/
char *start_history(struct_t *argument);
int history_writing(struct_t *argument);
int history_reading(struct_t *argument);
int create_history_list(struct_t *argument, char *buffer, int count);
int history_renum(struct_t *argument);

/*length.c*/
size_t list_length(const list_t *head);
int _strlength(char *string);

/*letfree.c*/
void free_argument(struct_t *argument, int dl);
void free_string(char **ptr);
void list_free(list_t **ptr);
int free_pointer(void **cat);

/*makecopy.c*/
char *_strncpy(char *cat, char *kitty, int num);
char *_memset(char *s, char b, unsigned int n);
char *_strcpy(char *cat, char *kitty);

/*path.c*/
char *path_finder(struct_t *argument, char *place, char *commandd);
void command_placeholder(struct_t *argument);

/*print.c*/
size_t print_list_str(const list_t *head);
size_t print_list(const list_t *head);
void _puts(char *cat);
int _putchar(char cat);

/*reading_line.c*/
ssize_t get_input(struct_t *argument);
ssize_t handle_input(struct_t *argument, char **buffer, size_t *length);
int _getline(struct_t *argument, char **buffer, size_t *length);
ssize_t buffer_reading(struct_t *argument, char *buffer, size_t *size);

/*realloc.c*/
void *_realloc(void *ptr, unsigned int old, unsigned int new);

/*remove.c*/
void remove_comments(char *cat);

/*replace.c*/
int new_alias(struct_t *argument);
int new_vars(struct_t *argument);
int new_string(char **kitty, char *cat);

/*set_struct.c*/
void delete_argument(struct_t *argument);
void init_argument(struct_t *argument, char **argv);

/*specific.c*/
char *_strchr(char *p, char x);
int delete_node_at_index(list_t **h, unsigned int index);
ssize_t get_node_index(list_t *head, list_t *cat);
list_t *node_starts_with(list_t *cat, char *pref, char ch);

/*stderr.c*/
int _eputchar(char ch);
void _eputs(char *cat);
void print_error(struct_t *argument, char *string);
#endif
