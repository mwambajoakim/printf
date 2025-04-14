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
	char *fmt_spec = "%";
	const char *ptr = format;
	unsigned int i = 0;

	if (format == NULL)
	{
		fprintf(stderr, "%s", "Null format string\n");
		return (1);
	}
	va_start(args, format);
	while (ptr[i])
	{
		if (ptr[i] == fmt_spec[i])
			i++;
		switch (*ptr)
		{
			case 'c':
				printf("%c", va_arg(args, int));
				break;
			case 's':
				printf("%s", va_arg(args, char *));
		}
		i++;
	}
	printf("\n");
	va_end(args);
	return (0);
}
