#include "info_handler.h"

/**
 * initializeInfo - initializes info_t struct
 * @info: struct address
 */
void initializeInfo(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * populateInfo - initializes info_t struct
 * @info: struct address
 * @args: argument vector
 */
void populateInfo(info_t *info, char **args)
{
	int i = 0;

	info->fname = args[0];

	if (info->arg)
	{
		info->argv = splitString(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = duplicateString(info->arg);
				info->argv[1] = NULL;
			}
		}

		for (i = 0; info->argv && info->argv[i]; i++)
			;

		info->argc = i;

		replaceAlias(info);
		replaceVariables(info);
	}
}

/**
 * freeInfo - frees info_t struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void freeInfo(info_t *info, int all)
{
	freeStringArray(info->argv);
	info->argv = NULL;
	info->path = NULL;

	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);

		freeList(&(info->env));
		freeList(&(info->history));
		freeList(&(info->alias));

		freeStringArray(info->environ);
		info->environ = NULL;

		freeStringArray(info->cmd_buf);

		if (info->readfd > 2)
			close(info->readfd);

		flushBuffer();
	}
}

