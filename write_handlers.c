#include "main.h"

/************************* WRITE HANDLE *************************/
/**
 * handle_write_char - Prints a character to stdout
 * @c: The character to be printed
 * @buffer: Buffer array to handle printing
 * @flags: Flag values to calculate active flags
 * @width: Width specifier
 * @precision: Precision specifier
 * @size: Size specifier
 *
 * Return: Number of characters printed
 */
int handle_write_char(char c, char buffer[],
	int flags, int width, int precision, int size)
{
	int t = 0;
	char padding = ' ';

	UNUSED(precision);
	UNUSED(size);

	if (flags & F_ZERO)
		padding = '0';

	buffer[t++] = c;
	buffer[t] = '\0';

	if (width > 1)
	{
		buffer[BUFF_SIZE - 1] = '\0';
		for (t = 0; t < width - 1; t++)
			buffer[BUFF_SIZE - t - 2] = padding;

		if (flags & F_MINUS)
			return (write(1, &buffer[0], 1) +
					write(1, &buffer[BUFF_SIZE - t - 1], width - 1));
		else
			return (write(1, &buffer[BUFF_SIZE - t - 1], width - 1) +
					write(1, &buffer[0], 1));
	}

	return (write(1, &buffer[0], 1));
}

/************************* WRITE NUMBER *************************/
/**
 * write_number - Prints a number
 * @is_negative: Indicates if the number is negative
 * @ind: Index at which the number starts in the buffer
 * @buffer: Buffer array to handle printing
 * @flags: Flag values to calculate active flags
 * @width: Width specifier
 * @precision: Precision specifier
 * @size: Size specifier
 *
 * Return: Number of characters printed
 */
int write_number(int is_negative, int ind, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = BUFF_SIZE - ind - 1;
	char padding = ' ', extra_char = 0;

	UNUSED(size);

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padding = '0';
	if (is_negative)
		extra_char = '-';
	else if (flags & F_PLUS)
		extra_char = '+';
	else if (flags & F_SPACE)
		extra_char = ' ';

	return (write_num(ind, buffer, flags, width, precision,
		length, padding, extra_char));
}

/**
 * write_num - Write a number using a buffer
 * @ind: Index at which the number starts in the buffer
 * @buffer: Buffer array
 * @flags: Flag values
 * @width: Width specifier
 * @prec: Precision specifier
 * @length: Number length
 * @padding: Padding character
 * @extra_char: Extra character
 *
 * Return: Number of characters printed
 */
int write_num(int ind, char buffer[],
	int flags, int width, int prec,
	int length, char padding, char extra_char)
{
	int t, padding_start = 1;

	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0' && width == 0)
		return (0);
	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		buffer[ind] = padding = ' ';
	if (prec > 0 && prec < length)
		padding = ' ';
	while (prec > length)
		buffer[--ind] = '0', length++;
	if (extra_char != 0)
		length++;
	if (width > length)
	{
		for (t = 1; t < width - length + 1; t++)
			buffer[t] = padding;
		buffer[t] = '\0';
		if (flags & F_MINUS && padding == ' ')
		{
			if (extra_char)
				buffer[--ind] = extra_char;
			return (write(1, &buffer[ind], length) + write(1, &buffer[1], t - 1));
		}
		else if (!(flags & F_MINUS) && padding == ' ')
		{
			if (extra_char)
				buffer[--ind] = extra_char;
			return (write(1, &buffer[1], t - 1) + write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && padding == '0')
		{
			if (extra_char)
				buffer[--padding_start] = extra_char;
			return (write(1, &buffer[padding_start], t - padding_start) +
				write(1, &buffer[ind], length - (1 - padding_start)));
		}
	}
	if (extra_char)
		buffer[--ind] = extra_char;
	return (write(1, &buffer[ind], length));
}

/**
 * write_unsgnd - Writes an unsigned number
 * @is_negative: Indicates if the number is negative
 * @ind: Index at which the number starts in the buffer
 * @buffer: Buffer array
 * @flags: Flag values
 * @width: Width specifier
 * @precision: Precision specifier
 * @size: Size specifier
 *
 * Return: Number of characters printed
 */
int write_unsgnd(int is_negative, int ind,
	char buffer[],
	int flags, int width, int precision, int size)
{
	int length = BUFF_SIZE - ind - 1, t = 0;
	char padding = ' ';

	UNUSED(is_negative);
	UNUSED(size);

	if (precision == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		return (0);

	if (precision > 0 && precision < length)
		padding = ' ';

	while (precision > length)
	{
		buffer[--ind] = '0';
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padding = '0';

	if (width > length)
	{
		for (t = 0; t < width - length; t++)
			buffer[t] = padding;

		buffer[t] = '\0';

		if (flags & F_MINUS)
		{
			return (write(1, &buffer[ind], length) + write(1, &buffer[0], t));
		}
		else
		{
			return (write(1, &buffer[0], t) + write(1, &buffer[ind], length));
		}
	}

	return (write(1, &buffer[ind], length));
}

/**
 * write_pointer - Writes a memory address
 * @buffer: Buffer array
 * @ind: Index at which the number starts in the buffer
 * @length: Number length
 * @width: Width specifier
 * @flags: Flag values
 * @padding: Padding character
 * @extra_char: Extra character
 * @padding_start: Index at which padding should start
 *
 * Return: Number of characters printed
 */
int write_pointer(char buffer[], int ind, int length,
	int width, int flags, char padding, char extra_char, int padding_start)
{
	int t;

	if (width > length)
	{
		for (t = 3; t < width - length + 3; t++)
			buffer[t] = padding;
		buffer[t] = '\0';
		if (flags & F_MINUS && padding == ' ')
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_char)
				buffer[--ind] = extra_char;
			return (write(1, &buffer[ind], length) + write(1, &buffer[3], t - 3));
		}
		else if (!(flags & F_MINUS) && padding == ' ')
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_char)
				buffer[--ind] = extra_char;
			return (write(1, &buffer[3], t - 3) + write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && padding == '0')
		{
			if (extra_char)
				buffer[--padding_start] = extra_char;
			buffer[1] = '0';
			buffer[2] = 'x';
			return (write(1, &buffer[padding_start], t - padding_start) +
				write(1, &buffer[ind], length - (1 - padding_start) - 2));
		}
	}
	buffer[--ind] = 'x';
	buffer[--ind] = '0';
	if (extra_char)
		buffer[--ind] = extra_char;
	return (write(1, &buffer[ind], BUFF_SIZE - ind - 1));
}
