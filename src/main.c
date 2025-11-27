#include "ft_ssl.h"

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    ft_putstr_err("usage: ft_ssl command [flags] [file/string]\n");
    return (1);
  }
  if (ft_strcmp(argv[1], "md5") == 0)
    return (handle_md5_command(argc, argv));
  ft_putstr_err("ft_ssl: Error: '");
  ft_putstr_err(argv[1]);
  ft_putstr_err("' is an invalid command.\n\n");
  ft_putstr_err("Standard commands:\n\nMessage Digest commands:\nmd5\n");
  return (1);
}
