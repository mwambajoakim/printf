#include "main.h"
#include <stdarg.h>
/**
 * _printf - is a function that selects the correct function to print.
 * @format: identifier to look for.
 * Return: the length of the string.
 */
int _printf(const char * const format, ...)
{
        va_list arguments;
        int k = 0, len = 0;

        va_start(arguments, format);
        for (k = 0; format[k] != '\0'; k++)
        {
                if (format[k] != '%')
                {
                        put_char(format[k]);
                        len += 1;
                }

                else if (format[k] == 'c')
                {
                        put_char(format[k + 1]);
                        len += 1;
                }
        }
        va_end(arguments);
        return (len);
}
