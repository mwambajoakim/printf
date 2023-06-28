#include "main.h"

/************************* WRITE HANDLE *************************/
/**
 * handle_write_char - prints string
 * to stdout
 * @c: character types.
 * @buffer: Buffer array used to handle print
 * @flags:  calculates active flags.
 * @width: get width.
 * @precision: precision specifier
 * @size: Size specifier
 *
 * Return: Number of charscters printed.
 */
int handle_write_char(char c, char buffer[],
	int flags, int width, int precision, int size)
{
	int g = 0;
	char padd = ' ';

	UNUSED(precision);
	UNUSED(size);

	if (flags & F_ZERO)
		padd = '0';

	buffer[g++] = c;
	buffer[g] = '\0';

	if (width > 1)
	{
		buffer[BUFF_SIZE - 1] = '\0';
		for (g = 0; g < width - 1; g++)
			buffer[BUFF_SIZE - g - 2] = padd;

		if (flags & F_MINUS)
			return (write(1, &buffer[0], 1) +
					write(1, &buffer[BUFF_SIZE - g - 1], width - 1));
		else
			return (write(1, &buffer[BUFF_SIZE - g - 1], width - 1) +
					write(1, &buffer[0], 1));
	}

	return (write(1, &buffer[0], 1));
}

/************************* WRITE NUMBER *************************/
/**
 * write_number - Prints a number
 * @is_negative: Number indicating if the number is negative
 * @g: char types
 * @buffer: Buffer array to handle print
 * @flags: Calculates active flags
 * @width: get width
 * @precision: Precision specifier
 * @size: Size specifier
 *
 * Return: Number of chars printed
 */
int write_number(int is_negative, int g, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = BUFF_SIZE - g - 1;
	char padd = ' ', extra_char = 0;

	UNUSED(size);

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (is_negative)
		extra_char = '-';
	else if (flags & F_PLUS)
		extra_char = '+';
	else if (flags & F_SPACE)
		extra_char = ' ';

	return (write_num(g, buffer, flags, width, precision,
		length, padd, extra_char));
}

/**
 * write_num - Writes a number using a buffer
 * @g: Index at which the number starts on the buffer
 * @buffer: Buffer
 * @flags: Flags values
 * @width: get width
 * @prec: Precision specifier
 * @length: Number length
 * @padd: Padding char
 * @extra_char: extra char
 *
 * Return: Number of chars printed
 */
int write_num(int g, char buffer[],
	int flags, int width, int prec,
	int length, char padd, char extra_char)
{
	int i, padd_start = 1;

	if (prec == 0 && g == BUFF_SIZE - 2 && buffer[g] == '0' && width == 0)
		return (0); /* printf(".0d", 0)  no char is printed */
	if (prec == 0 && g == BUFF_SIZE - 2 && buffer[g] == '0')
		buffer[g] = padd = ' ';
	if (prec > 0 && prec < length)
		padd = ' ';
	while (prec > length)
		buffer[--g] = '0';
	length++;
	if (extra_char != 0)
		length++;
	if (width > length)
	{
		for (i = 1; i < width - length + 1; i++)
			buffer[i] = padd;
		buffer[i] = '\0';
		if (flags & F_MINUS && padd == ' ')/* Assign extra char to left of buffer */
		{
			if (extra_char)
				buffer[--g] = extra_char;
			return (write(1, &buffer[g], length) + write(1, &buffer[1], i - 1));
		}
		else if (!(flags & F_MINUS) && padd == ' ')/* extra char to left of buff */
		{
			if (extra_char)
				buffer[--g] = extra_char;
			return (write(1, &buffer[1], i - 1) + write(1, &buffer[g], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')/* extra char to left of padd */
		{
			if (extra_char)
				buffer[--padd_start] = extra_char;
			return (write(1, &buffer[padd_start], i - padd_start) +
				write(1, &buffer[g], length - (1 - padd_start)));
		}
	}
	if (extra_char)
		buffer[--g] = extra_char;
	return (write(1, &buffer[g], length));
}

/**
 * write_unsigned - Writes an unsigned number
 * @is_negative: Number indicating if the number is negative
 * @g: Index at which the number starts on the buffer
 * @buffer: Buffer
 * @flags: Flags values
 * @width: get width
 * @precision: Precision specifier
 * @size: Size specifier
 *
 * Return: Number of chars printed
 */
int write_unsigned(int is_negative, int g, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = BUFF_SIZE - g - 1, i = 0;
	char padd = ' ';

	UNUSED(is_negative);
	UNUSED(size);

	if (precision == 0 && g == BUFF_SIZE - 2 && buffer[g] == '0')
		return (0); /* printf(".0d", 0)  no char is printed */
	if (precision > 0 && precision < length)
		padd = ' ';

	while (precision > length)
	{
		buffer[--g] = '0';
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';

	if (width > length)
	{
		for (i = 0; i < width - length; i++)
			buffer[i] = padd;

		buffer[i] = '\0';

		if (flags & F_MINUS) /* Assign extra char to left of buffer [buffer > padd]*/
		{
			return (write(1, &buffer[g], length) + write(1, &buffer[0], i));
		}
		else /* Assign extra char to left of padd [padd > buffer]*/
		{
			return (write(1, &buffer[0], i) + write(1, &buffer[g], length));
		}
	}

	return (write(1, &buffer[g], length));
}

/**
 * write_pointer - Write a memory address
 * @buffer: Buffer
 * @g: Index at which the number starts on the buffer
 * @length: Number length
 * @width: get width
 * @flags: Flags values
 * @padd: Padding char
 * @extra_char: Extra char
 * @padd_start: Index at which padding should start
 *
 * Return: Number of chars printed
 */
int write_pointer(char buffer[], int g, int length,
	int width, int flags, char padd, char extra_char, int padd_start)
{
	int i;

	if (width > length)
	{
		for (i = 3; i < width - length + 3; i++)
			buffer[i] = padd;
		buffer[i] = '\0';
		if (flags & F_MINUS && padd == ' ')/* Assign extra char to left of buffer */
		{
			buffer[--g] = 'x';
			buffer[--g] = '0';
			if (extra_char)
				buffer[--g] = extra_char;
			return (write(1, &buffer[g], length) + write(1, &buffer[3], i - 3));
		}
		else if (!(flags & F_MINUS) && padd == ' ')/* extra char to left of buffer */
		{
			buffer[--g] = 'x';
			buffer[--g] = '0';
			if (extra_char)
				buffer[--g] = extra_char;
			return (write(1, &buffer[3], i - 3) + write(1, &buffer[g], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')/* extra char to left of padding */
		{
			if (extra_char)
				buffer[--padd_start] = extra_char;
			buffer[1] = '0';
			buffer[2] = 'x';
			return (write(1, &buffer[padd_start], i - padd_start) +
				write(1, &buffer[g], length - (1 - padd_start) - 2));
		}
	}

	buffer[--g] = 'x';
	buffer[--g] = '0';
	if (extra_char)
		buffer[--g] = extra_char;
	return (write(1, &buffer[g], BUFF_SIZE - g - 1));
}

