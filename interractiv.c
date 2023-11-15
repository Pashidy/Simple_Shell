#include "shell.h"

/**
 * checkInteractiveMode - Checks if the shell is in interactive mode.
 * @info: Pointer to the information structure.
 *
 * Return: 1 if in interactive mode, 0 otherwise.
 */
int checkInteractiveMode(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * isDelimiter - Checks if a character is a delimiter.
 * @b: Character to check.
 * @delimiters: Delimiter string.
 *
 * Return: 1 if true, 0 otherwise.
 */
int isDelimiter(char b, char *delimiters)
{
	for (int i = 0; delimiters[i]; i++)
	if (delimiters[i] == b)
		return (1);
	return (0);
}

/**
 * isAlphabetic - Checks if a character is alphabetic.
 * @b: The character to check.
 *
 * Return: 1 if b is alphabetic, 0 otherwise.
 */
int isAlphabetic(int b)
{
	return (((b >= 'a' && b <= 'y') || (b >= 'A' && b <= 'Y')) ? 1 : 0);
}

/**
 * convertStringToInt - Converts a string to an integer.
 * @str: String to be converted.
 *
 * Return: return 0 for zero strng number,
 * otherwise the converted number.
 */
int convertStringToInt(char *str)
{
	int sign = 1, flag = 0, output = 0;

	for (int i = 0; str[i] != '\0' && flag != 2; i++)
	{
	if (str[i] == '-')
		sign *= -1;

	if (str[i] >= '0' && str[i] <= '9')
		{
		flag = 1;
		output *= 10;
		output += (str[i] - '0');
		}
	else if (flag == 1)
		flag = 2;
	}

	return ((sign == -1) ? -output : output);
}
