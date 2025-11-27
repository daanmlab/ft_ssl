#include "ft_ssl.h"

void print_md5_hash(s_state result)
{
  print_hex_byte((result.A & 0xFF));
  print_hex_byte(((result.A >> 8) & 0xFF));
  print_hex_byte(((result.A >> 16) & 0xFF));
  print_hex_byte(((result.A >> 24) & 0xFF));
  print_hex_byte((result.B & 0xFF));
  print_hex_byte(((result.B >> 8) & 0xFF));
  print_hex_byte(((result.B >> 16) & 0xFF));
  print_hex_byte(((result.B >> 24) & 0xFF));
  print_hex_byte((result.C & 0xFF));
  print_hex_byte(((result.C >> 8) & 0xFF));
  print_hex_byte(((result.C >> 16) & 0xFF));
  print_hex_byte(((result.C >> 24) & 0xFF));
  print_hex_byte((result.D & 0xFF));
  print_hex_byte(((result.D >> 8) & 0xFF));
  print_hex_byte(((result.D >> 16) & 0xFF));
  print_hex_byte(((result.D >> 24) & 0xFF));
}

s_state md5_from_buffer(const uint8_t *data, size_t len)
{
  s_ctx ctx;

  md5_init(&ctx);
  md5_update(&ctx, data, len);
  md5_finalize(&ctx);
  return (ctx.state);
}

void print_md5_digest(s_state result, int is_string, const char *label)
{
  if (is_string)
  {
    ft_putstr_out("MD5(\"");
    ft_putstr_out(label);
    ft_putstr_out("\")= ");
  }
  else if (label != NULL)
  {
    ft_putstr_out("MD5(");
    ft_putstr_out(label);
    ft_putstr_out(")= ");
  }
  else
    ft_putstr_out("(stdin)= ");
  print_md5_hash(result);
  ft_putchar_out('\n');
}

void process_md5_string(char *str, int quiet, int reverse)
{
  s_state result;
  size_t len;

  len = 0;
  while (str[len])
    len++;
  result = md5_from_buffer((const uint8_t *)str, len);
  if (quiet)
  {
    print_md5_hash(result);
    ft_putchar_out('\n');
  }
  else if (reverse)
  {
    print_md5_hash(result);
    ft_putstr_out(" \"");
    ft_putstr_out(str);
    ft_putstr_out("\"\n");
  }
  else
    print_md5_digest(result, 1, str);
}

static void hash_fd_to_ctx(int fd, s_ctx *ctx)
{
  char buffer[4096];
  int bytes_read;

  md5_init(ctx);
  bytes_read = read(fd, buffer, sizeof(buffer));
  while (bytes_read > 0)
  {
    md5_update(ctx, (const uint8_t *)buffer, (size_t)bytes_read);
    bytes_read = read(fd, buffer, sizeof(buffer));
  }
}

void process_md5_file(char *filename, int quiet, int reverse)
{
  int fd;
  s_ctx ctx;
  s_state result;

  fd = open(filename, O_RDONLY);
  if (fd < 0)
  {
    ft_putstr_err("ft_ssl: md5: ");
    ft_putstr_err(filename);
    ft_putstr_err(": No such file or directory\n");
    return;
  }
  hash_fd_to_ctx(fd, &ctx);
  close(fd);
  md5_finalize(&ctx);
  result = ctx.state;
  if (quiet)
  {
    print_md5_hash(result);
    ft_putchar_out('\n');
  }
  else if (reverse)
  {
    print_md5_hash(result);
    ft_putchar_out(' ');
    ft_putstr_out(filename);
    ft_putchar_out('\n');
  }
  else
    print_md5_digest(result, 0, filename);
}

void process_md5_stdin(int quiet, int reverse)
{
  s_ctx ctx;
  s_state result;

  hash_fd_to_ctx(STDIN_FILENO, &ctx);
  md5_finalize(&ctx);
  result = ctx.state;
  if (quiet)
  {
    print_md5_hash(result);
    ft_putchar_out('\n');
  }
  else if (reverse)
  {
    print_md5_hash(result);
    ft_putstr_out(" *stdin");
    ft_putchar_out('\n');
  }
  else
    print_md5_digest(result, 0, NULL);
}
