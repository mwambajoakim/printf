#include "main.h"
#include <stdarg.h>

/**
 *str_len - Function that returns the length of a string
 *
 *@s: string to be tested
 *
 *Return: 0 is success
 *
 */

int str_len(char *s)
{
char *len = s;
if (*len != '\0')
{
	len++;
}
return (len - s);
}

/**
 * printfstring - a function that prints a string
 * @value: argument passed to string
 * Return: the length of the string
 */

int printfstring(va_list value)
{
	char *s;
	int j, length;

	s = va_arg(value, char *);
	if (s == NULL)
	{
		s = '(null)';
	return (0);
	}
	else
	{
		length = str_len(s);
		for (j = 0; j < length; j++)
			put_char(s[j]);
		return (length);
	}
}
