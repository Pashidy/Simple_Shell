#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_ARGS 100
#define MAX_INPUT_SIZE 1024

char *read_input(void);
void process_input(char *input);

int tokenize_input(char *input, char *args[])
void execute_command(char *args[])
void process_input(char *input)
int main(void)

/** interractiv.c **/
int checkInteractiveMode(info_t *info)
int isDelimiter(char b, char *delimiters)
int isAlphabetic(int b)
int convertStringToInt(char *str)

/** creatin.c **/
int exit_shell(info_t *info)
char *get_current_directory(char *buffer)
int change_directory(info_t *info)
int help_command(info_t *info)

/** crt_alias **/
void display_history(list_t *history)
int my_history(info_t *info)
int remove_alias(info_t *info, char *str)
int add_alias(info_t *info, char *str)
int display_alias(list_t *node)
char *find_separator(char *alias, char separator)
void output_character(char c)
void output_string(char *str)
void display_all_aliases(list_t *alias_list)
int _myalias(info_t *info)

/** envir.c  **/
void display_environment(list_t *environment)
char *find_environment_variable(list_t *environment, const char *name)
int initialize_environment_variable(info_t *info)
int delete_environment_variable(info_t *info)

#endif

