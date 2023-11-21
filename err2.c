#include "shell.h"

/**
 * convert_str_to_int - Converts a string to an integer.
 * @r: The string to be converted.
 *
 * Return: The converted number if successful, -1 on error.
 */
int convert_str_to_int(char *r)
{
	int result = 0;

	if (*r == '+')
	r++;

	while (*r != '\0')
	{
	if (*r >= '0' && *r <= '9')
	{
		result *= 10;
		result += (*r - '0');

	if (result > INT_MAX)
		return (-1);
	}
	else
	{
		return (-1);
	}

	r++;
	}

	return (result);
}

/**
 * print_custom_error - Prints a custom error message.
 * @mes: The parameter and return info struct.
 * @e_type: String containing the specified error type.
 *
 * Return: Nothing.
 */
void print_custom_error(info_t *mes, char *e_type)
{
	_eputs(mes->fname);
	_eputs(": ");
	print_d(mes->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(mes->argv[0]);
	_eputs(": ");
	_eputs(e_type);
}

/**
 * print_decimal - Prints a decimal (integer) number (base 10).
 * @n: The number to print.
 * @fw: The file descriptor to write to.
 *
 * Return: The number of characters printed.
 */
int print_decimal(int n, int fw)
{
	int (*output_char)(char) = (fw == STDERR_FILENO) ? _eputchar : _putchar;
	int count = 0;
	unsigned int absolute = (n < 0) ? -n : n;

	if (n < 0)
	{
	output_char('-');
	count++;
	}

	int current = absolute;
	int p;

	for (p = 1000000000; p > 1; p /= 10)
	{
	if (absolute / p)
	{
	output_char('0' + current / p);
	count++;
	}
	current %= p;
	}

	output_char('0' + current);
	count++;

	return (count);
}

/**
 * convert_to_string - Converts a number to a string.
 * @val: The number to convert.
 * @bas: The base for conversion.
 * @fl_gs: Argument flags.
 *
 * Return: The converted string.
 */
char *convert_to_string(long int val, int bas, int fl_gs)
{
	static char buffer[50];
	char *ptr = &buffer[49];
	*ptr = '\0';
	char hint = 0;
	unsigned long v = val;

	if (!(fl_gs & CONVERT_UNSIGNED) && val < 0)
	{
	v = -val;
	sign = '-';
	}

	char *array = (fl_gs & CONVERT_LOWERCASE)
		? "0123456789abcdef" : "0123456789ABCDEF";

	do {
	*--ptr = array[v % bas];
	v /= bas;
	} while (v != 0);

	if (hint)
	*--ptr = hint;

	return (ptr);
}

/**
 * remove_first_comment - Replaces the first instance of '#' with '\0'.
 * @buff: Address of the string to modify.
 *
 * Return: Always 0.
 */
void remove_first_comment(char *buff)
{
	int c = 0;

	while (buff[c] != '\0')
	{
	if (buff[c] == '#' && (!c || buff[c - 1] == ' '))
	{
	buff[c] = '\0';
	break;
	}
	c++;
	}
}
