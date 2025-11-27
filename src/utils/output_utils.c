#include "ft_ssl.h"

void ft_putstr_fd(const char *s, int fd)
{
  int len;

  len = 0;
  while (s[len])
    len++;
  if (len > 0)
    write(fd, s, len);
}

void ft_putstr_err(const char *s)
{
  ft_putstr_fd(s, 2);
}

void ft_putstr_out(const char *s)
{
  ft_putstr_fd(s, 1);
}

void ft_putchar_out(char c)
{
  write(1, &c, 1);
}

void print_hex_byte(unsigned char byte)
{
  const char *hex;

  hex = "0123456789abcdef";
  ft_putchar_out(hex[byte >> 4]);
  ft_putchar_out(hex[byte & 0x0F]);
}
