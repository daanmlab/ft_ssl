#include "ft_ssl.h"

static int handle_md5_flag(char **argv, int *i, int *quiet, int *reverse)
{
  if (ft_strcmp(argv[*i], "-q") == 0)
    *quiet = 1;
  else if (ft_strcmp(argv[*i], "-r") == 0)
    *reverse = 1;
  else if (ft_strcmp(argv[*i], "-p") == 0)
    return (2);
  else if (ft_strcmp(argv[*i], "-s") == 0)
    return (3);
  else
  {
    ft_putstr_err("ft_ssl: md5: invalid option -- ");
    ft_putstr_err(argv[*i] + 1);
    ft_putstr_err("\n");
    return (-1);
  }
  return (0);
}

int handle_md5_command(int argc, char *argv[])
{
  int quiet;
  int reverse;
  int has_string;
  int has_files;
  int i;
  int flag;

  quiet = 0;
  reverse = 0;
  has_string = 0;
  has_files = 0;
  i = 2;
  while (i < argc)
  {
    if (argv[i][0] == '-')
    {
      flag = handle_md5_flag(argv, &i, &quiet, &reverse);
      if (flag == -1)
        return (1);
      if (flag == 2)
      {
        process_md5_stdin(quiet, reverse);
        has_string = 1;
      }
      else if (flag == 3)
      {
        i++;
        if (i >= argc)
        {
          ft_putstr_err("ft_ssl: md5: option requires");
          ft_putstr_err(" an argument -- s\n");
          return (1);
        }
        process_md5_string(argv[i], quiet, reverse);
        has_string = 1;
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
