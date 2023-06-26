#include "main.h"

/**
 * put_char - a function that prints a character to std output
 * @h: character to be printed out
 * Return: 1 is success
*/

int put_char(char h)
{

	return (write(1, &h, 1));
}
