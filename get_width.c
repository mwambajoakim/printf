#include "main.h"

/**
 * get_width - calculates the width for printing
 * and returns the result
 * @format: format specifier for argument printing
 * @w: arguments list to print
 * @arguments_list: arguments list
 *
 * Return: width.
 */
int get_width(const char *format, int *w, va_list arguments_list)
{
	int curr_w;
	int width = 0;

	for (curr_w = *w + 1; format[curr_w] != '\0'; curr_w++)
	{
		if (is_digit(format[curr_w]))
		{
			width *= 10;
			width += format[curr_w] - '0';
		}
		else if (format[curr_w] == '*')
		{
			curr_w++;
			width = va_arg(arguments_list, int);
			break;
		}
		else
			break;
	}

	*w = curr_w - 1;

	return (width);
}
