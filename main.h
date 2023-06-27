#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>

/**
 * struct format - This will match the specifiers to the function
 * @spec: type char pointer of the specifier i.e (l, h) for (d, i, u, o, x, X)
 * @spec_func: type pointer to function for the conversion specifier
 *
 */

typedef struct format
{
	char *spec;
	int (*spec_func)();
} conversion_spec;

int put_char(char h);
int _printf(const char *format, ...);
int printfstring(va_list value);
int printchar(va_list value);
int print_percent(void);


#endif
