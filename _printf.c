#include "main.h"
#include <stdarg.h>
#include <stdio.h>

void print_buffer(char buff[], int *buff_ind);

/**
 * _printf - Printf function
 * @fmt: Format string
 * Return: Number of printed characters
 */
int _printf(const char *fmt, ...)
{
	int b, printed = 0, printed_chars = 0;
	int fl, wid, prec, sz, buff_ind = 0;
	va_list lst;
	char buff[BUFF_SIZE];

	if (fmt == NULL)
		return (-1);

	va_start(lst, fmt);

	for (b = 0; fmt && fmt[b] != '\0'; b++)
	{
		if (fmt[b] != '%')
		{
			buff[buff_ind++] = fmt[b];
			if (buff_ind == BUFF_SIZE)
				print_buffer(buff, &buff_ind);
			printed_chars++;
		}
		else
		{
			print_buffer(buff, &buff_ind);
			fl = get_flags(fmt, &b);
			wid = get_width(fmt, &b, lst);
			prec = get_precision(fmt, &b, lst);
			sz = get_size(fmt, &b);
			++b;
			printed = handle_print(fmt, &b, lst, buff,
				fl, wid, prec, sz);
			if (printed == -1)
				return (-1);
			printed_chars += printed;
		}
	}

	print_buffer(buff, &buff_ind);

	va_end(lst);

	return (printed_chars);
}

/**
 * print_buffer - Prints the contents of the buffer if it exists
 * @buff: Array of characters
 * @buff_ind: Index at which to add the next character, represents the length
 */
void print_buffer(char buff[], int *buff_ind)
{
	if (*buff_ind > 0)
		write(1, &buff[0], *buff_ind);

	*buff_ind = 0;
}
