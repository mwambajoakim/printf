#include "main.h"
#include <stdarg.h>
/**
 * _printf - is a function that selects the correct function to print.
 * @format: identifier to look for.
 * Return: the length of the string.
 */
int _printf(const char * const format, ...)
{
	conversion_spec m[] = {
		{"%s", printfstring}, {"%c", printchar},
		{"%%", print_percent}
		};

	va_list arguments;
	int j = 0, k, len = 0;

	va_start(arguments, format);
	if (format == NULL || (format[0] == '%' && format[1] == '\0'))
		return (-1);

	Here:
	while (format[j] != '\0')
	{
		k = 13;
		while (k >= 0)
		{
			if (m[k].spec[0] == format[j] && m[k].spec[1] == format[j + 1])
			{
				len += m[k].spec_func(arguments);
				j = j + 2;
				goto Here;
			}
			k--;
		}
		put_char(format[j]);
		len++;
		j++;
	}
	va_end(arguments);
	return (len);
}
