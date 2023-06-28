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
	for (k = 0; format[k] != '\0'; k++)
	{
		if (format[k] != '%')
		{
			put_char(format[k]);
			len += 1;
		}
	}
	va_end(arguments);
	return (len);
}
