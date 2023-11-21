#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


#define MAX_ARGS 100
#define MAX_INPUT_SIZE 1024
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/**
 * struct builtin - contains a builtin string and related function
 * @type: the builtin command flag
 * @func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_tab

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

/** pars.c **/
int is_executable(char *_path);
char *duplicate_substring(char *input, int begin, int abort);
char *find_executable_in_path(char *p_string, char *com);

/** shell.c **/
void initialize_info(info_t *info);
int handle_file_argument(info_t *info, char *filename);
int main(int ac, char **av);

/** tok.c **/
char **split_string(char *str, char *delimiters);
char **split_string2(char *str, char delimiter);

/** gline **/
ssize_t bufferInput(info_t *info, char **buffer, size_t *length);
ssize_t getInput(info_t *info);
ssize_t readBuffer(info_t *info, char *buffer, size_t *size);
int customGetline(info_t *info, char **ptr, size_t *length);
void sigintHandler(__attribute__((unused))int sigNum);

/** lis_t.c **/
list_t *add_node(list_t **head, const char *str, int num, int at_end);
list_t *create_node(const char *str, int num);
size_t print_list_str(const list_t *head);
int delete_node_at_index(list_t **head, unsigned int index);
void free_list(list_t **head;

char *read_input(void);
void process_input(char *input);
int tokenize_input(char *input, char *args[]);
void execute_command(char *args[]);
int main(void);

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

/** crt_alias **/
void display_history(list_t *history);
int my_history(info_t *info);
int remove_alias(info_t *info, char *str);
int add_alias(info_t *info, char *str);
int display_alias(list_t *node);
void printAliases(list_t *list);
void output_string(char *str);
int _myalias(info_t *info);

/** envir.c  **/
void display_environment(list_t *environment);
char *find_environment_variable(list_t *environment, const char *name);
int initialize_environment_variable(info_t *info);
int delete_environment_variable(info_t *info);

/** exi_t.c **/
char *concatenateString(char *first, char *second, int maxLength);
char *copyString(char *destination, char *source, int length);
char *findCharacter(char *str, char target);

/**lista.c**/
size_t get_list_length(const list_t *head);
char **list_to_strings(list_t *head);
ssize_t get_node_index(list_t *head, list_t *node);
size_t print_list(const list_t *head);
list_t *find_node_starts_with(list_t *head, char *prefix, char c);

#endif
