#include "main.h"

/**
 * _printf - Prints formmated data to stdout.
 * @format: Pointer to different formats.
 *
 * Return: Number of characters printed to stdout.
 */
int _printf(const char *format, ...)
{
	va_list args;
	char *str;
	char chr;
	const char *ptr = format;

	if (format == NULL)
	{
		fprintf(stderr, "%s", "Null format string\n");
		return (1);
	}
	va_start(args, format);
	while (*ptr)
	{
		if (*ptr == '%')
		{
			ptr++;
			switch (*ptr)
			{
				case 'c':
					chr = va_arg(args, int);
					printf("%c", chr);
					break;
				case 's':
					str = va_arg(args, char *);
					if (str == NULL)
						str = "(nil)";
					printf("%s", str);
			}
		}
		else
		{
			_putchar(*ptr);
		}
		ptr++;
	}
	printf("\n");
	va_end(args);
	return (0);
}
