#include "main.h"

/************************* WRITE HANDLE *************************/
/**
 * handle_write_char - prints string
 * to stdout
 * @c: char types
 * @buffer: print buffer array
 * @flags: calculates active flags
 * @wid: get width
 * @prec: precision specifier
 * @size: size specifier
 *
 * Return: number of characters printed
 */
int handle_write_char(char c, char buffer[],
	int flags, int wid, int prec, int size)
{ /* char is stored at left and padding at buffer's right */
	int w = 0;
	char padd = ' ';

	UNUSED(prec);
	UNUSED(size);

	if (flags & F_ZERO)
		padd = '0';

	buffer[w++] = c;
	buffer[w] = '\0';

	if (wid > 1)
	{
		buffer[BUFF_SIZE - 1] = '\0';
		for (w = 0; w < wid - 1; w++)
			buffer[BUFF_SIZE - w - 2] = padd;

		if (flags & F_MINUS)
			return (write(1, &buffer[0], 1) +
					write(1, &buffer[BUFF_SIZE - w - 1], wid - 1));
		else
			return (write(1, &buffer[BUFF_SIZE - w - 1], wid - 1) +
					write(1, &buffer[0], 1));
	}

	return (write(1, &buffer[0], 1));
}

/************************* WRITE NUMBER *************************/
/**
 * write_number - prints string
 * @is_negative: arguments list
 * @ind: char types
 * @buffer: print buffer array
 * @flags: calculates active flags
 * @wid: get width.
 * @prec: precision specifier
 * @size: Size specifier
 *
 * Return: number of characters printed out
 */
int write_number(int is_negative, int ind, char buffer[],
	int flags, int wid, int prec, int size)
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

	return (write_num(ind, buffer, flags, wid, prec,
		length, padd, extra_ch));
}

/**
 * write_num - write a number using a buffer
 * @ind: index at which the number starts on the buffer
 * @buffer: buffer
 * @flags: flags
 * @wid: width
 * @prec: precision specifier
 * @length: number length
 * @padd: padding char
 * @extra_c: extra char
 *
 * Return: number of characters printed out
 */
int write_num(int ind, char buffer[],
	int flags, int wid, int prec,
	int length, char padd, char extra_c)
{
	int w, padd_start = 1;

	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0' && wid == 0)
		return (0); /* printf(".0d", 0)  no char is printed */
	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		buffer[ind] = padd = ' '; /* width is displayed with padding ' ' */
	if (prec > 0 && prec < length)
		padd = ' ';
	while (prec > length)
		buffer[--ind] = '0', length++;
	if (extra_c != 0)
		length++;
	if (wid > length)
	{
		for (w = 1; w < wid - length + 1; w++)
			buffer[w] = padd;
		buffer[w] = '\0';
		if (flags & F_MINUS && padd == ' ')/* Assign extra char to left of buffer */
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[1], w - 1));
		}
		else if (!(flags & F_MINUS) && padd == ' ')/* extra char to left of buff */
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[1], w - 1) + write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')/* extra char to left of padd */
		{
			if (extra_c)
				buffer[--padd_start] = extra_c;
			return (write(1, &buffer[padd_start], w - padd_start) +
				write(1, &buffer[ind], length - (1 - padd_start)));
		}
	}
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], length));
}

/**
 * write_unsgnd - writes an unsigned number
 * @is_negative: number indicating if the num is negative
 * @ind: index at which the number starts in the buffer
 * @buffer: character array
 * @flags: flags specifiers
 * @wid: width specifier
 * @prec: precision specifier
 * @size: size specifier
 *
 * Return: number of written characters
 */
int write_unsgnd(int is_negative, int ind,
	char buffer[],
	int flags, int wid, int prec, int size)
{
	/* The number is stored at the buffer's right and starts at position i */
	int length = BUFF_SIZE - ind - 1, w = 0;
	char padd = ' ';

	UNUSED(is_negative);
	UNUSED(size);

	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		return (0); /* printf(".0d", 0)  no char is printed */

	if (prec > 0 && prec < length)
		padd = ' ';

	while (prec > length)
	{
		buffer[--ind] = '0';
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';

	if (wid > length)
	{
		for (w = 0; w < wid - length; w++)
			buffer[w] = padd;

		buffer[w] = '\0';

		if (flags & F_MINUS) /* Assign extra char to left of buffer [buffer>padd]*/
		{
			return (write(1, &buffer[ind], length) + write(1, &buffer[0], w));
		}
		else /* Assign extra char to left of padding [padd>buffer]*/
		{
			return (write(1, &buffer[0], w) + write(1, &buffer[ind], length));
		}
	}

	return (write(1, &buffer[ind], length));
}

/**
 * write_pointer - write a memory address
 * @buffer: character array
 * @ind: index at which the number starts in the buffer
 * @length: length of number
 * @wid: width specifier
 * @flags: flags specifier
 * @padd: character representing the padding
 * @extra_c: Character representing extra char
 * @padd_start: index at which padding should start
 *
 * Return: number of written characters
 */
int write_pointer(char buffer[], int ind, int length,
	int wid, int flags, char padd, char extra_c, int padd_start)
{
	int w;

	if (wid > length)
	{
		for (w = 3; w < wid - length + 3; w++)
			buffer[w] = padd;
		buffer[w] = '\0';
		if (flags & F_MINUS && padd == ' ')/* Assign extra char to left of buffer */
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[3], w - 3));
		}
		else if (!(flags & F_MINUS) && padd == ' ')/* extra char to left of buffer */
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[3], w - 3) + write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')/* extra char to left of padd */
		{
			if (extra_c)
				buffer[--padd_start] = extra_c;
			buffer[1] = '0';
			buffer[2] = 'x';
			return (write(1, &buffer[padd_start], w - padd_start) +
				write(1, &buffer[ind], length - (1 - padd_start) - 2));
		}
	}
	buffer[--ind] = 'x';
	buffer[--ind] = '0';
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], BUFF_SIZE - ind - 1));
}
