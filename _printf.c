#include "main.h"
#include <stdarg.h>
#include <stdio.h>

void print_buffer(char buffer[], int *buff_ind);

/**
  *_printf - printf function
  *@format: format string
  *Return: number of printed chars
  */
int _printf(const char *format, ...)
{
int v, printed = 0, printed_chars = 0;
int flags, width, precision, size, buff_ind = 0;
va_list list;
char buffer[BUFF_SIZE];

if (format == NULL)
return (-1);

va_start(list, format);

for (v = 0; format && format[v] != '\0'; v++)
{
if (format[v] != '%')
{
buffer[buff_ind++] = format[v];
if (buff_ind == BUFF_SIZE)
print_buffer(buffer, &buff_ind);
/* write(1, &format[i], 1); */
printed_chars++;
}
else
{
print_buffer(buffer, &buff_ind);
flags = get_flags(format, &v);
width = get_width(format, &v, list);
precision = get_precision(format, &v, list);
size = get_size(format, &v);
++v;
printed = handle_print(format, &v, list, buffer,
flags, width, precision, size);
if (printed == -1)
return (-1);
printed_chars += printed;
}
}

print_buffer(buffer, &buff_ind);

va_end(list);

return (printed_chars);
}

/**
 *print_buffer - Prints the contents of the buffer if it exists
 *@buffer: Array of characters
 *@buff_ind: Pointer to the index at which to add the next character
 */
void print_buffer(char buffer[], int *buff_ind)
{
if (*buff_ind > 0)
write(1, &buffer[0], *buff_ind);

*buff_ind = 0;
}
