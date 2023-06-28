#include "main.h"

/************************* WRITE HANDLE *************************/

/**
 * handle_write_char - Prints a character to stdout
 * @c: Character to print
 * @buffer: Buffer array to handle printing
 * @flags: Calculates active flags
 * @width: Width specifier
 * @precision: Precision specifier
 * @size: Size specifier
 *
 * Return: Number of characters printed
 */
int handle_write_char(char c, char buffer[], int flags, int width, int precision, int size)
{
	int p = 0;
	char padd = ' ';

	UNUSED(precision);
	UNUSED(size);

	if (flags & F_ZERO)
		padd = '0';

	buffer[p++] = c;
	buffer[p] = '\0';

	if (width > 1)
	{
		buffer[BUFF_SIZE - 1] = '\0';
		for (p = 0; p < width - 1; p++)
			buffer[BUFF_SIZE - p - 2] = padd;

		if (flags & F_MINUS)
			return (write(1, &buffer[0], 1) + write(1, &buffer[BUFF_SIZE - p - 1], width - 1));
		else
			return (write(1, &buffer[BUFF_SIZE - p - 1], width - 1) + write(1, &buffer[0], 1));
	}

	return (write(1, &buffer[0], 1));
}

/************************* WRITE NUMBER *************************/

/**
 * write_number - Prints a number
 * @is_negative: Flag indicating if the number is negative
 * @ind: Index of the number in the buffer
 * @buffer: Buffer array to handle printing
 * @flags: Calculates active flags
 * @width: Width specifier
 * @precision: Precision specifier
 * @size: Size specifier
 *
 * Return: Number of characters printed
 */
int write_number(int is_negative, int ind, char buffer[], int flags, int width, int precision, int size)
{
	int length = BUFF_SIZE - ind - 1;
	char padd = ' ', extra_ch = 0;

	UNUSED(size);

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (is_negative)
		extra_ch = '-';
	else if (flags & F_PLUS)
		extra_ch = '+';
	else if (flags & F_SPACE)
		extra_ch = ' ';

	return (write_num(ind, buffer, flags, width, precision, length, padd, extra_ch));
}

/**
 * write_num - Write a number using a buffer
 * @ind: Index at which the number starts in the buffer
 * @buffer: Buffer array
 * @flags: Flags specifier
 * @width: Width specifier
 * @prec: Precision specifier
 * @length: Number length
 * @padd: Padding char
 * @extra_c: Extra char
 *
 * Return: Number of printed characters
 */
int write_num(int ind, char buffer[], int flags, int width, int prec, int length, char padd, char extra_c)
{
	int p, padd_start = 1;

	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0' && width == 0)
		return (0); /* printf(".0d", 0)  no char is printed */
	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		buffer[ind] = padd = ' '; /* width is displayed with padding ' ' */
	if (prec > 0 && prec < length)
		padd = ' ';
	while (prec > length)
		buffer[--ind] = '0', length++;
	if (extra_c != 0)
		length++;
	if (width > length)
	{
		for (p = 1; p < width - length + 1; p++)
			buffer[p] = padd;
		buffer[p] = '\0';
		if (flags & F_MINUS && padd == ' ')/* Assign extra char to the left of buffer */
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[1], p - 1));
		}
		else if (!(flags & F_MINUS) && padd == ' ')/* Assign extra char to the left of buffer */
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[1], p - 1) + write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')/* Assign extra char to the left of padding */
		{
			if (extra_c)
				buffer[--padd_start] = extra_c;
			return (write(1, &buffer[padd_start], p - padd_start) +
				write(1, &buffer[ind], length - (1 - padd_start)));
		}
	}
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], length));
}

/**
 * write_unsgnd - Writes an unsigned number
 * @is_negative: Flag indicating if the number is negative
 * @ind: Index at which the number starts in the buffer
 * @buffer: Buffer array of characters
 * @flags: Flags specifier
 * @width: Width specifier
 * @precision: Precision specifier
 * @size: Size specifier
 *
 * Return: Number of written characters
 */
int write_unsgnd(int is_negative, int ind, char buffer[], int flags, int width, int precision, int size)
{
	int length = BUFF_SIZE - ind - 1, p = 0;
	char padd = ' ';

	UNUSED(is_negative);
	UNUSED(size);

	if (precision == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		return (0); /* printf(".0d", 0)  no char is printed */

	if (precision > 0 && precision < length)
		padd = ' ';

	while (precision > length)
	{
		buffer[--ind] = '0';
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';

	if (width > length)
	{
		for (p = 0; p < width - length; p++)
			buffer[p] = padd;

		buffer[p] = '\0';

		if (flags & F_MINUS) /* Assign extra char to the left of buffer [buffer > padd] */
		{
			return (write(1, &buffer[ind], length) + write(1, &buffer[0], p));
		}
		else /* Assign extra char to the left of buffer [padd > buffer] */
		{
			return (write(1, &buffer[0], p) + write(1, &buffer[ind], length));
		}
	}

	return (write(1, &buffer[ind], length));
}

/**
 * write_pointer - Write a memory address
 * @buffer: Array of characters
 * @ind: Index at which the number starts in the buffer
 * @length: Length of the number
 * @width: Width specifier
 * @flags: Flags specifier
 * @padd: Character representing the padding
 * @extra_c: Character representing the extra character
 * @padd_start: Index at which the padding should start
 *
 * Return: Number of written characters
 */
int write_pointer(char buffer[], int ind, int length, int width, int flags, char padd, char extra_c, int padd_start)
{
	int p;

	if (width > length)
	{
		for (p = 3; p < width - length + 3; p++)
			buffer[p] = padd;
		buffer[p] = '\0';
		if (flags & F_MINUS && padd == ' ')/* Assign extra char to the left of buffer */
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[3], p - 3));
		}
		else if (!(flags & F_MINUS) && padd == ' ')/* Assign extra char to the left of buffer */
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[3], p - 3) + write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')/* Assign extra char to the left of padding */
		{
			if (extra_c)
				buffer[--padd_start] = extra_c;
			buffer[1] = '0';
			buffer[2] = 'x';
			return (write(1, &buffer[padd_start], p - padd_start) +
				write(1, &buffer[ind], length - (1 - padd_start) - 2));
		}
	}
	buffer[--ind] = 'x';
	buffer[--ind] = '0';
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], BUFF_SIZE - ind - 1));
}
