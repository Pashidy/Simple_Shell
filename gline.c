#include "shell.h"

/**
 * bufferInput - buffers chained commands
 * @info: parameter struct
 * @buffer: address of buffer
 * @length: address of length variable
 *
 * Return: bytes read
 */
ssize_t bufferInput(info_t *info, char **buffer, size_t *length)
{
	ssize_t bytesRead = 0;
	size_t bufferLength = 0;

	if (!*length)
	{
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, sigintHandler);

#if USE_GETLINE
		bytesRead = getline(buffer, &bufferLength, stdin);
#else
		bytesRead = customGetline(info, buffer, &bufferLength);
#endif

		if (bytesRead > 0)
		{
			if ((*buffer)[bytesRead - 1] == '\n')
			{
				(*buffer)[bytesRead - 1] = '\0'; /* remove trailing newline */
				bytesRead--;
			}
			info->linecount_flag = 1;
			removeComments(*buffer);
			buildHistoryList(info, *buffer, info->histcount++);

			if (_strchr(*buffer, ';')) /* is this a command chain? */
			{
				*length = bytesRead;
				info->cmd_buf = buffer;
			}
		}
	}
	return (bytesRead);
}

/**
 * getInput - gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t getInput(info_t *info)
{
	static char *buffer; /* the ';' command chain buffer */
	static size_t i, j, length;
	ssize_t bytesRead = 0;
	char **bufferPointer = &(info->arg), *position;

	_putchar(BUF_FLUSH);
	bytesRead = bufferInput(info, &buffer, &length);

	if (bytesRead == -1) /* EOF */
		return (-1);

	if (length) /* we have commands left in the chain buffer */
	{
		j = i; /* init new iterator to current buffer position */
		position = buffer + i; /* get pointer for return */

		checkChain(info, buffer, &j, i, length);
		while (j < length) /* iterate to semicolon or end */
		{
			if (isChain(info, buffer, &j))
				break;
			j++;
		}

		i = j + 1; /* increment past nulled ';' */
		if (i >= length) /* reached end of buffer? */
		{
			i = length = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*bufferPointer = position;
		return (_strlen(position));
	}

	*bufferPointer = buffer;
	return (bytesRead);
}

/**
 * readBuffer - reads a buffer
 * @info: parameter struct
 * @buffer: buffer
 * @size: size
 *
 * Return: bytesRead
 */
ssize_t readBuffer(info_t *info, char *buffer, size_t *size)
{
	ssize_t bytesRead = 0;

	if (*size)
		return (0);

	bytesRead = read(info->readfd, buffer, READ_BUF_SIZE);

	if (bytesRead >= 0)
		*size = bytesRead;

	return (bytesRead);
}

/**
 * customGetline - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: size
 */
int customGetline(info_t *info, char **ptr, size_t *length)
{
	static char buffer[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t bytesRead = 0, size = 0;
	char *position = NULL, *newPosition = NULL, *c;

	position = *ptr;
	if (position && length)
		size = *length;
	if (i == len)
		i = len = 0;

	bytesRead = readBuffer(info, buffer, &len);
	if (bytesRead == -1 || (bytesRead == 0 && len == 0))
		return (-1);

	c = _strchr(buffer + i, '\n');
	k = c ? 1 + (unsigned int)(c - buffer) : len;
	newPosition = _realloc(position, size, size ? size + k : k + 1);

	if (!newPosition) /* MALLOC FAILURE! */
		return (position ? free(position), -1 : -1);

	if (size)
		_strncat(newPosition, buffer + i, k - i);
	else
		_strncpy(newPosition, buffer + i, k - i + 1);

	size += k - i;
	i = k;
	position = newPosition;

	if (length)
		*length = size;

	*ptr = position;
	return (size);
}

/**
 * sigintHandler - blocks ctrl-C
 * @sigNum: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sigNum)
{
	_puts("\n$ ");
	_putchar(BUF_FLUSH);
}

