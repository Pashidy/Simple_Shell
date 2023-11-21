#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define _GNU_SOURCE

#define MAX_ARGS 100
#define MAX_INPUT_SIZE 1024
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

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
 * @info: Pointer to the information structure
 * @buffer: Buffer to store the current directory
 * @histcount: the history line number count
 * @str: String to be converted
 * @b: The character to check
 * @delimiters: Delimiter string
 * @mes: Structure containing potential arguments
 * @mes: the parameter struct
 * @linecount_flag: if on count this line of input
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: the history node
 * @alias: the alias node
 * @env_changed: on if environ was changed
 * @buf: buffer
 * @inf: structure containing potential arguments used to maintain function prototype.
 * @nam: env variable name
 * @linecount: the history linecount, histcount
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
	char **environ;
	int env_changed;
	int status;
	ssize_t fileDescriptor;
	char *f_name = getHistoryFile(mes);
	list_t *nod = NULL;
	char *dir = get_environment_variable(info, "HOME=");
	char *f_name = concatenate_strings(dir, "/", HIST_FILE);
	struct stat fileStat;
	char *buf = NULL, *f_name = getHistoryFile(mes);
	list_t *nod = mes->history;
	int e = 0;
	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}


/** interractiv.c **/
int checkInteractiveMode(info_t *info);
int isDelimiter(char b, char *delimiters);
int isAlphabetic(int b);
int convertStringToInt(char *str);

/** creatin.c **/
int exit_shell(info_t *info);
char *get_current_directory(char *buffer);
int change_directory(info_t *info);
int help_command(info_t *info);

/** histor **/
char *get_history_file(info_t *info);
int writeHistoryToFile(info_t *mes);
int readHistoryFromFile(info_t *mes);
int buildHistoryList(info_t *mes, char *buf, int linecount);
int renumberHistory(info_t *mes);

/** bt_env **/
int my_env(info_t *inf);
char *get_env(info_t *inf, const char *nam);
int my_setenv(info_t *inf);
int my_unsetenv(info_t *inf);
int populate_env_list(info_t *inf);

#endif
