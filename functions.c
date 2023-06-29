#include "main.h"

/************************* PRINT CHAR *************************/

/**
 * print_char - prints character
 * @types: list of arguments
 * @buf: buf array to handle print
 * @flags: calculates active flags
 * @wid: get Wid
 * @prec: prec specification
 * @size: size specifier
 *
 * Return: number of characters printed out
 */
int print_char(va_list types, char buf[],
	      int flags, int wid, int prec, int size)
{
	char c = va_arg(types, int);

	return (handle_write_character(c, buf, flags, width, prec, size));
}

/************************* PRINT STRING *************************/

/**
 * print_string - prints string
 * @types: list of arguments
 * @buf: buf array to handle print
 * @flags: calculates active flags
 * @wid: get wid
 * @prec: prec specification
 * @size: size specifier
 *
 * Return: number of characters printed out
 */
int print_string(va_list types, char buf[],
		int flags, int wid, int prec, int size)
{
	int length = 0, w;
	char *str = va_arg(types, char *);

	UNUSED(buf);
	UNUSED(flags);
	UNUSED(wid);
	UNUSED(prec);
	UNUSED(size);
	if (str == NULL)
	{
		str = "(null)";
		if (prec >= 6)
			str = "      ";
	}

	while (str[length] != '\0')
		length++;

	if (prec >= 0 && prec < length)
		length = prec;

	if (wid > length)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], length);
			for (w = wid - length; w > 0; w--)
				write(1, " ", 1);
			return (wid);
		}
		else
		{
			for (w = wid - length; w > 0; w--)
				write(1, " ", 1);
			write(1, &str[0], length);
			return (wid);
		}
	}

	return (write(1, str, length));
}

/************************* PRINT PERCENT SIGN *************************/

/**
 * print_percent - prints percent sign
 * @types: list of arguments
 * @buf: buf array to handle print
 * @flags: calculates active flags
 * @wid: Wid
 * @prec: prec specification
 * @size: size specifier
 *
 * Return: number of characters printed
 */
int print_percent(va_list types, char buf[],
		  int flags, int wid, int prec, int size)
{
	UNUSED(types);
	UNUSED(buf);
	UNUSED(flags);
	UNUSED(wid);
	UNUSED(prec);
	UNUSED(size);
	return (write(1, "%%", 1));
}

/************************* PRINT INT *************************/

/**
 * print_int - print int
 * @types: list of arguments
 * @buffer: buffer array to handle print
 * @flags: calculates active flags
 * @wid: get wid
 * @prec: prec specification
 * @size: size specifier
 *
 * Return: number of characters printed out
 */
int print_int(va_list types, char buf[],
	     int flags, int wid, int prec, int size)
{
	int w = BUFF_SIZE - 2;
	int is_negative = 0;
	long int n = va_arg(types, long int);
	unsigned long int num;

	n = convert_size_number(n, size);

	if (n == 0)
		buf[w--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)n;

	if (n < 0)
	{
		num = (unsigned long int)((-1) * n);
		is_negative = 1;
	}

	while (num > 0)
	{
		buffer[w--] = (num % 10) + '0';
		num /= 10;
	}

	w++;

	return (write_number(is_negative, w, buf, flags, wid, prec, size));
}

/************************* PRINT BINARY *************************/

/**
 * print_binary - prints an unsigned number
 * @types: list of arguments
 * @buf: buf array to handle print
 * @flags: calculates active flags
 * @width: get wid
 * @prec: prec specification
 * @size: size specifier
 *
 * Return: numbers of characters printed
 */
int print_binary(va_list types, char buf[],
		int flags, int wid, int prec, int size)
{
	unsigned int n, m, w, sum;
	unsigned int a[32];
	int count;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	n = va_arg(types, unsigned int);
	m = 2147483648; /* (2 ^ 31) */
	a[0] = n / m;
	for (w = 1; w < 32; w++)
	{
		m /= 2;
		a[w] = (n / m) % 2;
	}
	for (w = 0, sum = 0, count = 0; w < 32; w++)
	{
		sum += a[w];
		if (sum || w == 31)
		{
			char z = '0' + a[w];

			write(1, &z, 1);
			count++;
		}
	}
	return (count);
}

