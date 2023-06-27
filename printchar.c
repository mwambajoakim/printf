#include "main.h"
#include <stdarg.h>

/**
 * printchar - a functiom tha prints a character.
 * @value: arguments passed to function
 * Return: 1 is success
 */
int printchar(va_list value)
{
	char c;

	c = va_arg(value, int);
	put_char(c);
	return (1);
}
