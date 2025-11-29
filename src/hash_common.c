#include "ft_ssl.h"

static void print_invalid_option(const char *cmd_name, char *opt)
{
  ft_putstr_err("ft_ssl: ");
  ft_putstr_err(cmd_name);
  ft_putstr_err(": invalid option -- ");
  ft_putstr_err(opt + 1);
  ft_putstr_err("\n");
}

static int handle_hash_flag(char **argv, int *i, t_hash_flags *flags)
{
  if (ft_strcmp(argv[*i], "-q") == 0)
    flags->quiet = 1;
  else if (ft_strcmp(argv[*i], "-r") == 0)
    flags->reverse = 1;
  else if (ft_strcmp(argv[*i], "-p") == 0)
    return (2);
  else if (ft_strcmp(argv[*i], "-s") == 0)
    return (3);
  else
  {
    print_invalid_option(flags->algo->name, argv[*i]);
    return (-1);
  }
  return (0);
}

static int handle_s_flag(int argc, char **argv, int *i, t_hash_flags *flags)
{
  (*i)++;
  if (*i >= argc)
  {
    ft_putstr_err("ft_ssl: ");
    ft_putstr_err(flags->algo->name);
    ft_putstr_err(": option requires an argument -- s\n");
    return (1);
  }
  process_hash_string(argv[*i], flags);
  flags->has_string = 1;
  return (0);
}

static int process_flag(int argc, char **argv, int *i, t_hash_flags *flags)
{
  int flag;

  flag = handle_hash_flag(argv, i, flags);
  if (flag == -1)
    return (1);
  if (flag == 2)
  {
    process_hash_stdin(flags);
    flags->has_string = 1;
  }
  else if (flag == 3)
    return (handle_s_flag(argc, argv, i, flags));
  return (0);
}

int handle_hash_command(int argc, char *argv[], t_hash_algorithm *algo)
{
  t_hash_flags flags;
  int i;

  flags.algo = algo;
  flags.quiet = 0;
  flags.reverse = 0;
  flags.has_string = 0;
  flags.has_files = 0;
  i = 2;
  while (i < argc)
  {
    if (argv[i][0] == '-')
    {
      if (process_flag(argc, argv, &i, &flags))
        return (1);
    }
    else
    {
      process_hash_file(argv[i], &flags);
      flags.has_files = 1;
    }
    i++;
  }
  if (!flags.has_string && !flags.has_files)
    process_hash_stdin(&flags);
  return (0);
}
