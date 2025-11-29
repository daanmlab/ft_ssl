#ifndef FT_SSL_H
# define FT_SSL_H

#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

/**
 * Macros
 */

#define ROTL(a, i) (((a) << (i)) | ((a) >> (32 - (i))))
#define ROTR(a, i) (((a) >> (i)) | ((a) << (32 - (i))))


/**
 * MD5 types
 */
typedef struct t_md5_state
{
  uint32_t A;
  uint32_t B;
  uint32_t C;
  uint32_t D;
} s_md5_state;

typedef struct t_md5_ctx {
  s_md5_state state;
  uint8_t block[64];
  size_t block_len;
  uint64_t bitlen;
} s_md5_ctx;

void md5_init(s_md5_ctx *ctx);
void md5_update(s_md5_ctx *ctx, const uint8_t *data, size_t size);
void md5_finalize(s_md5_ctx *ctx);

int ft_strcmp(const char *s1, const char *s2);
char *ft_strdup(const char *s);
void *ft_memcpy(void *dest, const void *src, int n);

void ft_putstr_fd(const char *s, int fd);
void ft_putstr_err(const char *s);
void ft_putstr_out(const char *s);
void ft_putchar_out(char c);
void print_hex_byte(unsigned char byte);
void print_md5_hash(s_md5_state result);

/**
 * Generic hash algorithm interface
 */
typedef struct s_hash_algorithm {
	const char	*name;
	void		(*init)(void *ctx);
	void		(*update)(void *ctx, const uint8_t *data, size_t size);
	void		(*finalize)(void *ctx);
	void		(*print_hash)(void *ctx);
}	t_hash_algorithm;

typedef struct s_hash_flags {
	t_hash_algorithm	*algo;
	int					quiet;
	int					reverse;
	int					has_string;
	int					has_files;
}	t_hash_flags;

int		handle_hash_command(int argc, char *argv[], t_hash_algorithm *algo);
void	process_hash_string(char *str, t_hash_flags *flags);
void	process_hash_file(char *filename, t_hash_flags *flags);
void	process_hash_stdin(t_hash_flags *flags);


/**
 * SHA256
 */

typedef struct t_sha256_state
{
  uint32_t A;
  uint32_t B;
  uint32_t C;
  uint32_t D;
  uint32_t E;
  uint32_t F;
  uint32_t G;
  uint32_t H;
} s_sha256_state;

typedef struct t_sha256_ctx {
  s_sha256_state state;
  uint8_t block[64];
  size_t block_len;
  uint64_t bitlen;
} s_sha256_ctx;

void sha256_init(s_sha256_ctx *ctx);
void sha256_update(s_sha256_ctx *ctx, const uint8_t *data, size_t size);
void sha256_finalize(s_sha256_ctx *ctx);

void print_sha256_hash(s_sha256_state result);

#endif
