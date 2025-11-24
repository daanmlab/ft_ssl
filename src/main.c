#include "main.h"

int ft_strcmp(const char *s1, const char *s2)
{
  int i;

  i = 0;
  while (s1[i] && s2[i] && s1[i] == s2[i])
    i++;
  return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char *ft_strdup(const char *s)
{
  int len;
  char *dup;
  int i;

  len = 0;
  while (s[len])
    len++;
  dup = malloc(len + 1);
  if (!dup)
    return (NULL);
  i = 0;
  while (i < len)
  {
    dup[i] = s[i];
    i++;
  }
  dup[i] = '\0';
  return (dup);
}

void *ft_memcpy(void *dest, const void *src, int n)
{
  unsigned char *d;
  const unsigned char *s = (const unsigned char *)src;
  int i;

  d = (unsigned char *)dest;
  i = 0;
  while (i < n)
  {
    d[i] = s[i];
    i++;
  }
  return (dest);
}

void ft_putstr(const char *s)
{
  int len;

  len = 0;
  while (s[len])
    len++;
  write(2, s, len);
}

void ft_putstr_stdout(const char *s)
{
  int len;

  len = 0;
  while (s[len])
    len++;
  write(1, s, len);
}

void ft_putchar_stdout(char c)
{
  write(1, &c, 1);
}

void print_hex_byte(unsigned char byte)
{
  const char hex[] = "0123456789abcdef";

  ft_putchar_stdout(hex[byte >> 4]);
  ft_putchar_stdout(hex[byte & 0x0F]);
}

void print_md5_hash(struct s_ABCD result)
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

void print_md5_digest(uint8_t *input, int is_string, char *label)
{
  struct s_ABCD result;

  result = compute_md5(input);
  if (is_string)
  {
    ft_putstr_stdout("MD5 (\"");
    ft_putstr_stdout(label);
    ft_putstr_stdout("\") = ");
  }
  else if (label)
  {
    ft_putstr_stdout("MD5 (");
    ft_putstr_stdout(label);
    ft_putstr_stdout(") = ");
  }
  else
    ft_putstr_stdout("(stdin)= ");
  print_md5_hash(result);
  ft_putchar_stdout('\n');
}

void process_md5_string(char *str, int quiet, int reverse)
{
  struct s_ABCD result;

  result = compute_md5((uint8_t *)str);
  if (quiet)
  {
    print_md5_hash(result);
    ft_putchar_stdout('\n');
  }
  else if (reverse)
  {
    print_md5_hash(result);
    ft_putstr_stdout(" \"");
    ft_putstr_stdout(str);
    ft_putstr_stdout("\"\n");
  }
  else
    print_md5_digest((uint8_t *)str, 1, str);
}

void process_md5_file(char *filename, int quiet, int reverse)
{
  int fd;
  char buffer[4096];
  char *content;
  int total_size;
  int bytes_read;
  char *new_content;
  struct s_ABCD result;

  fd = open(filename, O_RDONLY);
  if (fd < 0)
  {
    ft_putstr("ft_ssl: md5: ");
    ft_putstr(filename);
    ft_putstr(": No such file or directory\n");
    return;
  }
  // Read file content
  content = NULL;
  total_size = 0;
  while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0)
  {
    new_content = malloc(total_size + bytes_read + 1);
    if (content)
    {
      ft_memcpy(new_content, content, total_size);
      free(content);
    }
    ft_memcpy(new_content + total_size, buffer, bytes_read);
    total_size += bytes_read;
    new_content[total_size] = '\0';
    content = new_content;
  }
  close(fd);
  if (!content)
    content = ft_strdup("");
  result = compute_md5((uint8_t *)content);
  if (quiet)
  {
    print_md5_hash(result);
    ft_putchar_stdout('\n');
  }
  else if (reverse)
  {
    print_md5_hash(result);
    ft_putchar_stdout(' ');
    ft_putstr_stdout(filename);
    ft_putchar_stdout('\n');
  }
  else
    print_md5_digest((uint8_t *)content, 0, filename);
  free(content);
}

void process_md5_stdin(int quiet, int reverse)
{
  char buffer[4096];
  char *content;
  int total_size;
  int bytes_read;
  char *new_content;
  struct s_ABCD result;

  content = NULL;
  total_size = 0;
  while ((bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer))) > 0)
  {
    new_content = malloc(total_size + bytes_read + 1);
    if (content)
    {
      ft_memcpy(new_content, content, total_size);
      free(content);
    }
    ft_memcpy(new_content + total_size, buffer, bytes_read);
    total_size += bytes_read;
    new_content[total_size] = '\0';
    content = new_content;
  }
  if (!content)
    content = ft_strdup("");
  result = compute_md5((uint8_t *)content);
  if (quiet)
  {
    print_md5_hash(result);
    ft_putchar_stdout('\n');
  }
  else if (reverse)
  {
    print_md5_hash(result);
    ft_putchar_stdout('\n');
  }
  else
    print_md5_digest((uint8_t *)content, 0, NULL);
  free(content);
}

int handle_md5_command(int argc, char *argv[])
{
  int quiet;
  int reverse;
  int has_string;
  int has_files;
  int i;

  quiet = 0;
  reverse = 0;
  has_string = 0;
  has_files = 0;
  i = 2;
  while (i < argc)
  {
    if (argv[i][0] == '-')
    {
      if (ft_strcmp(argv[i], "-s") == 0)
      {
        i++;
        if (i >= argc)
        {
          ft_putstr("ft_ssl: md5: option requires an argument -- s\n");
          return (1);
        }
        process_md5_string(argv[i], quiet, reverse);
        has_string = 1;
      }
      else if (ft_strcmp(argv[i], "-q") == 0)
        quiet = 1;
      else if (ft_strcmp(argv[i], "-r") == 0)
        reverse = 1;
      else if (ft_strcmp(argv[i], "-p") == 0)
      {
        process_md5_stdin(quiet, reverse);
        has_string = 1;
      }
      else
      {
        ft_putstr("ft_ssl: md5: invalid option -- ");
        ft_putstr(argv[i] + 1);
        ft_putstr("\n");
        return (1);
      }
    }
    else
    {
      process_md5_file(argv[i], quiet, reverse);
      has_files = 1;
    }
    i++;
  }
  if (!has_string && !has_files)
    process_md5_stdin(quiet, reverse);
  return (0);
}

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    ft_putstr("usage: ft_ssl command [flags] [file/string]\n");
    return (1);
  }

  if (ft_strcmp(argv[1], "md5") == 0)
    return (handle_md5_command(argc, argv));
  else
  {
    ft_putstr("ft_ssl: Error: '");
    ft_putstr(argv[1]);
    ft_putstr("' is an invalid command.\n\n");
    ft_putstr("Standard commands:\n\nMessage Digest commands:\nmd5\n");
    return (1);
  }

  return (0);
}