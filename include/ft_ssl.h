#ifndef FT_SSL_H
# define FT_SSL_H

#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

typedef struct t_state
{
  uint32_t A;
  uint32_t B;
  uint32_t C;
  uint32_t D;
} s_state;

typedef struct t_ctx {
  s_state state;
  uint8_t block[64];
  size_t block_len;
  uint64_t bitlen;
} s_ctx;

void md5_init(s_ctx *ctx);
void md5_update(s_ctx *ctx, const uint8_t *data, size_t size);
void md5_finalize(s_ctx *ctx);

int handle_md5_command(int argc, char *argv[]);
void process_md5_string(char *str, int quiet, int reverse);
void process_md5_file(char *filename, int quiet, int reverse);
void process_md5_stdin(int quiet, int reverse);
s_state md5_from_buffer(const uint8_t *data, size_t len);

int ft_strcmp(const char *s1, const char *s2);
char *ft_strdup(const char *s);
void *ft_memcpy(void *dest, const void *src, int n);

void ft_putstr_fd(const char *s, int fd);
void ft_putstr_err(const char *s);
void ft_putstr_out(const char *s);
void ft_putchar_out(char c);
void print_hex_byte(unsigned char byte);
void print_md5_hash(s_state result);
void print_md5_digest(s_state result, int is_string, const char *label);

#endif
