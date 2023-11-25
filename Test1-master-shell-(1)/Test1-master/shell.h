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
#include <sys/stat.h>

/*BUFFERs*/
#define BUFFER_RD 1024
#define BUFFER_WR 1024
#define NEGATTIVE -1

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
 * struct list - struct of linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct list
{
	int n;
	char *string;
	struct list *next;
} list_t;

/**
 * struct holder - control the argumentrmation
 * @arg: a string generated from getline containing argumentements
 * @argv: an array of strings generated from arg
 * @path: a string path for the current command
 * @argc: the argumentment count
 * @line_count: the error count
 * @err_num: the error code for exit()s
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

#define ARGU_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

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


/* toem_shloop.c */
int file_mode(char **av, struct_t *argument);
int execute_command(struct_t *, char **);
int check_builtin(struct_t *);
void command_placeholder(struct_t*);
void fork_command(struct_t *);

/* toem_parser.c */
int is_command(struct_t *, char *);
char *char_duplicate(char *, int, int);
char *path_finder(struct_t *, char *, char *);

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
int interactive_mode(struct_t *);
int delim_check(char, char *);
int alpha_check(int);
int _atoi(char *);

/* toem_errors1.c */
int convert_string(char *);
void print_error(struct_t *, char *);
int print_integer(int num, int file);
char *convert_number(long int, int, int);
void remove_comments(char *buf);

/* toem_builtin.c */
int _myexit(struct_t *);
int _mycd(struct_t*);
int _myhelp(struct_t *);

/* toem_builtin1.c */
int _myhistory(struct_t *);
int _myalias(struct_t *);

/*toem_getline.c */
ssize_t get_input(struct_t *);
int _getline(struct_t *, char **, size_t *);
void handle_sign(int);
ssize_t buffer_reading(struct_t *argument, char *buffer, size_t *size);
ssize_t handle_input(struct_t *argument, char **buf, size_t *len);

/* toem_getargument.c */
void delete_argument(struct_t *);
void init_argument(struct_t *argument, char **argv);
void free_argument(struct_t *, int);

/* toem_environ.c */
char *_getenv(struct_t *, const char *);
int _myenv(struct_t *);
int _mysetenv(struct_t *);
int _myunsetenv(struct_t *);
int populate_env_list(struct_t *);

/* toem_getenv.c */
char **get_environ(struct_t *);
int _unsetenv(struct_t *, char *);
int _setenv(struct_t *, char *, char *);

/* toem_history.c */
char *start_history(struct_t *argument);
int history_writing(struct_t *argument);
int history_reading(struct_t *argument);
int create_history_list(struct_t *argument, char *buf, int linecount);
int history_renum(struct_t *argument);

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
int is_chain(struct_t *, char *, size_t *);
void check_chain(struct_t *, char *, size_t *, size_t, size_t);
int new_alias(struct_t *);
int new_vars(struct_t *);
int new_string(char **, char *);

#endif