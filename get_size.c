#include "main.h"

/**
 * get_size - calculates the size to cast the argument
 * and prints it out
 * @format: format specifier for argument printing
 * @w: arguments list to print out.
 *
 * Return: Size.
 */
int get_size(const char *format, int *w)
{
	int curr_w = *w + 1;
	int size = 0;

	if (format[curr_w] == 'l')
		size = S_LONG;
	else if (format[curr_w] == 'h')
		size = S_SHORT;

	if (size == 0)
		*w = curr_w - 1;
	else
		*w = curr_w;

	return (size);
}
