#include "main.h"

/**
 * _printf - Prints formmated data to stdout.
 * @format: Pointer to different formats.
 *
 * Return: Number of characters printed to stdout.
 */
int _printf(const char *format, ...)
{
	int len;
	va_list args;
	char *fmt_spec = "%";

	if (format == NULL)
	{
		fprintf(stderr, "%s", "Null format string\n");
		return (1);
	}
	va_start(args, format);
	while (format)
	{
		if (format == fmt_spec)
			format++;
		switch(format)
		{
			case 'c':
				printf("%c"va_arg(args, int));
				break;
			case 's':
			printf("%s", va_arg(args, char *));
		}
		format++;
	}
	len = strlen(format);
	va_end(args);
	return (len);
}
