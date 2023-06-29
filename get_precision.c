#include "main.h"

/**
 * get_precision - calculates precision for printing and returns
 * result to stdout
 * @format: format string for argument print
 * @w: List of arguments to be printed.
 * @args_list: arguments list
 *
 * Return: Precision.
 */
int get_precision(const char *format, int *w, va_list args_list)
{
	int curr_w = *w + 1;
	int precision = -1;

	if (format[curr_w] != '.')
		return (precision);

	precision = 0;

	for (curr_w += 1; format[curr_w] != '\0'; curr_w++)
	{
		if (is_digit(format[curr_w]))
		{
			precision *= 10;
			precision += format[curr_w] - '0';
		}
		else if (format[curr_w] == '*')
		{
			curr_w++;
			precision = va_arg(args_list, int);
			break;
		}
		else
			break;
	}

	*w = curr_w - 1;

	return (precision);
}
