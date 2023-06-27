#include "main.h"
#include <stdarg.h>

/**
 * printchar - a functiom tha prints a character.
 * @value: arguments.
 * Return: 1 is success
 */
int printchar(va_list value)
{
	char c;

	c = va_arg(value, int);
	_putchar(c);
	return (1);
}
