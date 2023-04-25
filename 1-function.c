#include "main.h"

/**
 * print_char - Prints a char
 * @types: List of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculate active flags
 * @width: min width of printed char
 * @precision: Precision specification printed char
 * @size: Size specifier of printed char
 * Return: Num of chars printed
 */
int print_char(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char k = va_arg(types, int);

	return (handle_write_char(k, buffer, flags, width, precision, size));
}

/**
 * print_string - Prints string
 * @types: List of args
 * @buffer: Buffer array to handle print
 * @flags:  Calculate active flags
 * @width: get width of printed string.
 * @precision: Precision specification
 * @size: Size specifier of printed string
 * Return: Numb of chars printed
 */
int print_string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = 0, j;
	char *str = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
			str = "      ";
	}

	while (str[length] != '\0')
		length++;

	if (precision >= 0 && precision < length)
		length = precision;

	if (width > length)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], length);
			for (j = width - length; j > 0; j--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (j = width - length; j > 0; j--)
				write(1, " ", 1);
			write(1, &str[0], length);
			return (width);
		}
	}

	return (write(1, str, length));
}

/**
 * print_percent - Prints a percent sign
 * @types: List of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: gets width of printed a percent sign.
 * @precision: Precision specification
 * @size: Size specifier of percent sign.
 * Return: Num of chars printed
 */
int print_percent(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}
/**
 * print_int - Print int
 * @types: List of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width of printed int.
 * @precision: Precision specification
 * @size: Size specifier of printed in
 * Return: Num of chars printed
 */
int print_int(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int j = BUFF_SIZE - 2;
	int is_negative = 0;
	long int k = va_arg(types, long int);
	unsigned long int num;

	k = convert_size_number(k, size);

	if (k == 0)
		buffer[j--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)k;

	if (k < 0)
	{
		num = (unsigned long int)((-1) * k);
		is_negative = 1;
	}

	while (num > 0)
	{
		buffer[j--] = (num % 10) + '0';
		num /= 10;
	}

	j++;

	return (write_number(is_negative, j, buffer, flags, width, precision, size));
}

/**
 * print_binary - Prints an unsigned number
 * @types: List of args
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Nums of char printed.
 */
int print_binary(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	unsigned int a, b, c, sum;
	unsigned int j[32];
	int count;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	a = va_arg(types, unsigned int);
	b = 2147483648; /* (2 ^ 31) */
	j[0] = a / b;
	for (c = 1; c < 32; c++)
	{
		b /= 2;
		j[c] = (a / b) % 2;
	}
	for (c = 0, sum = 0, count = 0; c < 32; c++)
	{
		sum += j[c];
		if (sum || c == 31)
		{
			char m = '0' + j[c];

			write(1, &m, 1);
			count++;
		}
	}
	return (count);
}
