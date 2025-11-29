#include "ft_ssl.h"

static void md5_init_wrapper(void *ctx)
{
  md5_init((s_md5_ctx *)ctx);
}

static void md5_update_wrapper(void *ctx, const uint8_t *data, size_t size)
{
  md5_update((s_md5_ctx *)ctx, data, size);
}

static void md5_finalize_wrapper(void *ctx)
{
  md5_finalize((s_md5_ctx *)ctx);
}

static void md5_print_hash_wrapper(void *ctx)
{
  print_md5_hash(((s_md5_ctx *)ctx)->state);
}

static void sha256_init_wrapper(void *ctx)
{
  sha256_init((s_sha256_ctx *)ctx);
}

static void sha256_update_wrapper(void *ctx, const uint8_t *data, size_t size)
{
  sha256_update((s_sha256_ctx *)ctx, data, size);
}

static void sha256_finalize_wrapper(void *ctx)
{
  sha256_finalize((s_sha256_ctx *)ctx);
}

static void sha256_print_hash_wrapper(void *ctx)
{
  print_sha256_hash(((s_sha256_ctx *)ctx)->state);
}

static t_hash_algorithm g_algorithms[] = {
  {
    "md5",
    md5_init_wrapper,
    md5_update_wrapper,
    md5_finalize_wrapper,
    md5_print_hash_wrapper
  },
  {
    "sha256",
    sha256_init_wrapper,
    sha256_update_wrapper,
    sha256_finalize_wrapper,
    sha256_print_hash_wrapper
  },
  {NULL, NULL, NULL, NULL, NULL}
};

static t_hash_algorithm *find_algorithm(const char *name)
{
  int i;

  i = 0;
  while (g_algorithms[i].name != NULL)
  {
    if (ft_strcmp(g_algorithms[i].name, name) == 0)
      return (&g_algorithms[i]);
    i++;
  }
  return (NULL);
}

int main(int argc, char *argv[])
{
  t_hash_algorithm *algo;

  if (argc < 2)
  {
    ft_putstr_err("usage: ft_ssl command [flags] [file/string]\n");
    return (1);
  }
  
  algo = find_algorithm(argv[1]);
  if (algo != NULL)
    return (handle_hash_command(argc, argv, algo));
  
  ft_putstr_err("ft_ssl: Error: '");
  ft_putstr_err(argv[1]);
  ft_putstr_err("' is an invalid command.\n\n");
  ft_putstr_err("Standard commands:\n\nMessage Digest commands:\nmd5\nsha256\n");
  return (1);
}
