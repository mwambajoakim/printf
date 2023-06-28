#include "main.h"

/**
 * print_char - Prints a character.
 * @c: The character to print.
 * @buffer: Buffer array to handle print.
 * @flags: Calculates active flags.
 * @width: Width.
 * @precision: Precision specification.
 * @size: Size specifier.
 *
 * Return: 1.
 */
int print_char(char c, char *buffer, int flags, int width, int precision, int size)
{
	return (handle_write_char(c, buffer, flags, width, precision, size));
}

/**
 * print_string - Prints a string.
 * @str: The string to print.
 * @buffer: Buffer array to handle print.
 * @flags: Calculates active flags.
 * @width: Width.
 * @precision: Precision specification.
 * @size: Size specifier.
 *
 * Return: The number of characters printed.
 */
int print_string(char *str, char *buffer, int flags, int width, int precision, int size)
{
	return (handle_write_string(str, buffer, flags, width, precision, size));
}

/* Additional function definitions */

