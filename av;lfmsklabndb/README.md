# 0x16. C - Simple Shell
 Project to be done in teams of 2 people (your team: Abdallah Mohamed, Gehad Gamal)

# Shell Functions

This shell program contains various functions for different tasks. Here's a brief description of each function:

## _atoi.c

### `_atoi(char *num)`

Simulates the atoi function in C. Converts a string to an integer.

## built_in_1.c

***The content of built_in_1.c has been truncated.***

## built_in_2.c

***The content of built_in_2.c has been truncated.***

## get_env.c

### `my_env(struct_t *argument)`

Prints the new environment.

### `get_env(struct_t *argument, const char *name)`

Gets the value of an environment variable.

### `my_setenv(struct_t *argument)`

Initializes or modifies an environment variable.

### `my_unsetenv(struct_t *argument)`

Removes an environmental variable.

### `populate_env_list(struct_t *argument)`

Populates the environment linked list.

## history.c

### `start_history(struct_t *argument)`

Gets the history file.

### `history_writing(struct_t *argument)`

Creates or appends to a history file.

### `history_reading(struct_t *argument)`

Reads the history from a file.

### `create_history_list(struct_t *argument, char *buffer, int count)`

Creates a list to handle the history.

### `history_renum(struct_t *argument)`

Updates the history.

## AUTHORS

***The content of AUTHORS has been truncated.***

## check.c

### `delim_check(char c, char *d)`

Checks if a character is a delimiter.

### `alpha_check(int s)`

Tests if a character is an alphabet character.

### `is_command(struct_t *argument, char *place)`

Checks if a given path is a command.

### `starts_with(const char *cat, const char *kitty)`

Checks if a specific word starts with a specific character.

### `check_builtin(struct_t *argument)`

Executes the built-in command.

# Learning Objectives
At the end of this project, you are expected to be able to explain to anyone, without the help of Google:

# General
Who designed and implemented the original Unix operating system
Who wrote the first version of the UNIX shell
Who invented the B programming language (the direct predecessor to the C programming language)
Who is Ken Thompson
How does a shell work
What is a pid and a ppid
How to manipulate the environment of the current process
What is the difference between a function and a system call
How to create processes
What are the three prototypes of main
How does the shell use the PATH to find the programs
How to execute another program with the execve system call
How to suspend the execution of a process until one of its children terminates
What is EOF / “end-of-file”?

# Requirements

#  General
Allowed editors: vi, vim, emacs
All your files will be compiled on Ubuntu 20.04 LTS using gcc, using the options -Wall -Werror -Wextra -pedantic -std=gnu89
All your files should end with a new line
A README.md file, at the root of the folder of the project is mandatory
Your code should use the Betty style. It will be checked using betty-style.pl and betty-doc.pl
Your shell should not have any memory leaks
No more than 5 functions per file
All your header files should be include guarded
Use system calls only when you need to (why?)
# GitHub
*There should be one project repository per group. If you and your partner have a repository with the same name in both your accounts, you risk a 0% score. Add your partner as a collaborator. *

# List of allowed functions and system calls
access (man 2 access)
chdir (man 2 chdir)
close (man 2 close)
closedir (man 3 closedir)
execve (man 2 execve)
exit (man 3 exit)
_exit (man 2 _exit)
fflush (man 3 fflush)
fork (man 2 fork)
free (man 3 free)
getcwd (man 3 getcwd)
getline (man 3 getline)
getpid (man 2 getpid)
isatty (man 3 isatty)
kill (man 2 kill)
malloc (man 3 malloc)
open (man 2 open)
opendir (man 3 opendir)
perror (man 3 perror)
read (man 2 read)
readdir (man 3 readdir)
signal (man 2 signal)
stat (__xstat) (man 2 stat)
lstat (__lxstat) (man 2 lstat)
fstat (__fxstat) (man 2 fstat)
strtok (man 3 strtok)
wait (man 2 wait)
waitpid (man 2 waitpid)
wait3 (man 2 wait3)
wait4 (man 2 wait4)
write (man 2 write)

# Compilation
## Your shell will be compiled this way:

`gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh`

More Info
Output
Unless specified otherwise, your program must have the exact same output as sh (/bin/sh) as well as the exact same error output.
The only difference is when you print an error, the name of the program must be equivalent to your argv[0] (See below)
Example of error with sh:

$ echo "qwerty" | /bin/sh
/bin/sh: 1: qwerty: not found
$ echo "qwerty" | /bin/../bin/sh
/bin/../bin/sh: 1: qwerty: not found
$
Same error with your program hsh:

$ echo "qwerty" | ./hsh
./hsh: 1: qwerty: not found
$ echo "qwerty" | ./././hsh
./././hsh: 1: qwerty: not found
$

# files
- README.md - description about the project repo
- AUTHORS - file at the root of your repository, listing all individuals having contributed content to the repository.
- shell.h - is the header file which contains the standared header file and prototype of o function used in the program.
- main.c - initialize the program with infinite loop by call the prompt function
- execute.c - execute the command.
- _atoi.c - simuilte atoi
- command_built.c - exit the program (Handles the 'exit' command), changes the current directory of the process and displays argumentrmation about shell commands or functions
- command_built.c - print history, remove alias, set alias to string, print an alas string and manages shell aliases
- command_built1.c - checks if character is a delimeter and checks if specific word start with specific char
- fd.c - print an integer to a filedescriptor
- check.c - checks if character is a delimeter, test if it is char
- check1.c - check if it works in interactve mode and non interactive mode, check the last status and check if it is the chain
- compare.c - concatenates two strings, compare and concatenates
- convert.c - convert a number, string to an integer and list to string
- duplicate.c - duplicates a string and char
- environ.c - prints the new environment, gets the value of an environ variable and Initialize a new environment variable, or modify an existing one
- execute.c - to check the input, fork to execute a command and to execute from a file
- fd.c - print an integer to a filedescriptor.
- get_env.c - returns the string array copy of our environ, Initialize a few environment variable and Remove an environment variable
- handle.c - handle ctrl-C or handle ctrl-D
- history.c - get file of history, creat or append a file, reads history and make a list to handle the history
- length.c - get the length of a list and calculate the length of a string
- letfree.c - free pointeres
- make_copy.c - copies a string, fills memory with a constant byte and copy string to another
- path.c - finds a command in PATH and find the path
- print.c - print one char, string, element of a list and specific element
- reading_line.c - buffer reading, read from line, handle buffer and read from a line
- realloc.c - reallocates a memory block using malloc and free
- remove.c - remove_coments
- replace.c - replaces string, replaces vars and change an alias
- set_struct.c - set a struct and clear the stuct
- specifir.c - get a node, get an index, delete specific node and find specific characther in string
- stderr.c - print a char to stderr, print a string to stderr and print error massage to stderr

# SHELL.H #

has library
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

all functions or prototype

<<" <THANKS FOR WATCHING> ">>
