#include "shell.h"

/**
 * get_history_file - Gets the history file.
 * @info: Parameter struct.
 *
 * Return: Allocated string containing the history file.
 */
char *get_history_file(info_t *info)
{
	char *dir = get_environment_variable(info, "HOME=");

	if (!dir)
	return (NULL);

	char *f_name = concatenate_strings(dir, "/", HIST_FILE);
		free(dir);

	return (f_name);

}

/**
 * writeHistoryToFile - creates a file, or appends to an existing file
 * @mes: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int writeHistoryToFile(info_t *mes)
{
	ssize_t fileDescriptor;
	char *f_name = getHistoryFile(mes);
	list_t *nod = NULL;

	if (!f_name)
		return (-1);

	fileDescriptor = open(f_name, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(f_name);

	if (fileDescriptor == -1)
		return (-1);

	for (nod = mes->history; nod; nod = nod->next)
	{
		writeToFile(nod->str, fileDescriptor);
		writeToFile("\n", fileDescriptor);
	}

	writeToFile(BUF_FLUSH, fileDescriptor);
	close(fileDescriptor);

	return (1);
}

/**
 * readHistoryFromFile - reads history from file
 * @mes: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int readHistoryFromFile(info_t *mes);
int readHistoryFromFile(info_t *mes)
{
	int i, end = 0, linecount = 0;
	ssize_t fileDescriptor, readLength, f_Size = 0;
	struct stat fileStat;
	char *buf = NULL, *f_name = getHistoryFile(mes);

	if (!f_name)
		return (0);

	fileDescriptor = open(f_name, O_RDONLY);
	free(f_name);

	if (fileDescriptor == -1)
		return (0);

	if (!fstat(fileDescriptor, &fileStat))
		f_Size = fileStat.st_size;

	if (f_Size < 2)
		return (0);

	buf = allocateMemory(sizeof(char) * (f_Size + 1));

	if (!buf)
		return (free(buf), 0);

	readLength = read(fileDescriptor, buf, f_Size);
	buf[f_Size] = 0;

	if (readLength <= 0)
		return (free(buf), 0);

	close(fileDescriptor);

	for (i = 0; i < f_Size; i++)
	{
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			buildHistoryList(mes, buf + end, linecount++);
			end = i + 1;
		}
	}

	if (end != i)
		buildHistoryList(mes, buf + end, linecount++);

	free(buf);
	mes->histcount = linecount;

	while (mes->histcount-- >= HIST_MAX)
		deleteNodeAtIndex(&(mes->history), 0);

	renumberHistory(mes);

	return (mes->histcount);
}

/**
 * buildHistoryList - adds entry to a history linked list
 * @mes: Structure containing potential arguments.
 * @buf: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int buildHistoryList(info_t *mes, char *buf, int linecount)
{
	list_t *nod = NULL;

	if (mes->history)
		nod = mes->history;

	addNodeEnd(&nod, buf, linecount);

	if (!mes->history)
		mes->history = nod;

	return (0);
}

/**
 * renumberHistory - renumbers the history linked list after changes
 * @mes: Structure containing potential arguments.
 *
 * Return: the new histcount
 */
int renumberHistory(info_t *mes)
{
	list_t *nod = mes->history;
	int e = 0;

	while (nod)
	{
		nod->num = e++;
		nod = nod->next;
	}

	return (mes->histcount = e);
}
