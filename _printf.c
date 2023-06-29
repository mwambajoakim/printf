#include "main.h"
#include <stdarg.h>
#include <stdio.h>

void print_buffer(char buffer[], int *buff_ind);

/**
 * _printf - printf function
 * @format: format
 * Return: printed characters
 */
int _printf(const char *format, ...)
{
    int w, printed = 0, printed_chars = 0;
    int flags, wid, prec, size, buff_ind = 0;
    va_list arguments_list;
    char buffer[BUFF_SIZE];

    if (format == NULL)
        return (-1);

    va_start(arguments_list, format);

    for (w = 0; format && format[w] != '\0'; w++)
    {
        if (format[w] != '%')
        {
            buffer[buff_ind++] = format[w];
            if (buff_ind == BUFF_SIZE)
                print_buffer(buffer, &buff_ind);
            /* write(1, &format[w], 1);*/
            printed_chars++;
        }
        else
        {
            print_buffer(buffer, &buff_ind);
            flags = get_flags(format, &w);
            wid = get_width(format, &w, arguments_list);
            prec = get_precision(format, &w, arguments_list);
            size = get_size(format, &w);
            ++w;
            printed = handle_print(format, &w, arguments_list, buffer,
                flags, wid, prec, size);
            if (printed == -1)
                return (-1);
            printed_chars += printed;
        }
    }

    print_buffer(buffer, &buff_ind);

    va_end(arguments_list);

    return (printed_chars);
}

/**
 * print_buffer - prints the contents of the buffer if it exist
 * @buffer: characters of array
 * @buff_ind: index at which to add next char, represents the length.
 */
void print_buffer(char buffer[], int *buff_ind)
{
    if (*buff_ind > 0)
        write(1, &buffer[0], *buff_ind);

    *buff_ind = 0;
}

