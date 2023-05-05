#include <stdarg.h>
#include <stdio.h>

/**
 * _printf - prints formatted output to stdout
 * @format: the format string
 *
 * Return: the number of characters printed (excluding the null byte used to end output to strings)
 */
int _printf(const char *format, ...)
{
    va_list args;
    int count = 0;

    va_start(args, format);

    while (*format != '\0')
    {
        if (*format == '%')
        {
            format++;
            if (*format == 'c')
            {
                char c = va_arg(args, int);
                putchar(c);
                count++;
            }
            else if (*format == 's')
            {
                char *s = va_arg(args, char *);
                while (*s != '\0')
                {
                    putchar(*s);
                    s++;
                    count++;
                }
            }
            else if (*format == '%')
            {
                putchar('%');
                count++;
            }
            else if (*format == 'b')
            {
                unsigned int n = va_arg(args, unsigned int);
                unsigned int mask = 1 << (sizeof(unsigned int) * 8 - 1);
                int started = 0;
                while (mask != 0)
                {
                    if (n & mask)
                    {
                        putchar('1');
                        started = 1;
                    }
                    else if (started || mask == 1)
                    {
                        putchar('0');
                        started = 1;
                    }
                    mask >>= 1;
                    count++;
                }
            }
        }
        else
        {
            putchar(*format);
            count++;
        }
        format++;
    }

    va_end(args);
    return count;
}
