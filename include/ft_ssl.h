/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabalm <dabalm@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 22:36:59 by dabalm            #+#    #+#             */
/*   Updated: 2025/11/27 22:37:04 by dabalm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdint.h>
# include <unistd.h>

typedef struct s_md5_state
{
	uint32_t	a;
	uint32_t	b;
	uint32_t	c;
	uint32_t	d;
}	t_md5_state;

typedef struct s_md5_ctx
{
	t_md5_state	state;
	uint8_t		block[64];
	size_t		block_len;
	uint64_t	bitlen;
}	t_md5_ctx;

void		md5_init(t_md5_ctx *ctx);
void		md5_update(t_md5_ctx *ctx, const uint8_t *data, size_t size);
void		md5_finalize(t_md5_ctx *ctx);
uint32_t	f(uint32_t b, uint32_t c, uint32_t d, int i);
uint32_t	red_box(uint32_t input, int i);
void		to_words(uint8_t *input, uint32_t words[]);
int			get_word_index(int i);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_strdup(const char *s);
void		*ft_memcpy(void *dest, const void *src, int n);
void		ft_putstr_fd(const char *s, int fd);
void		ft_putstr_err(const char *s);
void		ft_putstr_out(const char *s);
void		ft_putchar_out(char c);
void		print_hex_byte(unsigned char byte);
void		print_md5_hash(t_md5_state result);

typedef struct s_hash_algorithm
{
	const char	*name;
	void		(*init)(void *ctx);
	void		(*update)(void *ctx, const uint8_t *data, size_t size);
	void		(*finalize)(void *ctx);
	void		(*print_hash)(void *ctx);
}	t_hash_algorithm;

typedef struct s_hash_flags
{
	t_hash_algorithm	*algo;
	int					quiet;
	int					reverse;
	int					has_string;
	int					has_files;
}	t_hash_flags;

int					handle_hash_command(int argc, char *argv[],
						t_hash_algorithm *algo);
void				process_hash_string(char *str, t_hash_flags *flags);
void				process_hash_file(char *filename, t_hash_flags *flags);
void				process_hash_stdin(t_hash_flags *flags);
void				hash_fd_to_buffer(int fd, t_hash_algorithm *algo,
						void *ctx);
t_hash_algorithm	*get_md5_algorithm(void);
t_hash_algorithm	*get_sha256_algorithm(void);

typedef struct s_sha256_state
{
	uint32_t	a;
	uint32_t	b;
	uint32_t	c;
	uint32_t	d;
	uint32_t	e;
	uint32_t	f;
	uint32_t	g;
	uint32_t	h;
}	t_sha256_state;

typedef struct s_sha256_ctx
{
	t_sha256_state	state;
	uint8_t			block[64];
	size_t			block_len;
	uint64_t		bitlen;
}	t_sha256_ctx;

typedef struct s_sha256_vars
{
	uint32_t	a;
	uint32_t	b;
	uint32_t	c;
	uint32_t	d;
	uint32_t	e;
	uint32_t	f;
	uint32_t	g;
	uint32_t	h;
	uint32_t	big_s1;
	uint32_t	big_s0;
	uint32_t	temp1;
	uint32_t	temp2;
}	t_sha256_vars;

void		sha256_init(t_sha256_ctx *ctx);
void		sha256_update(t_sha256_ctx *ctx, const uint8_t *data,
				size_t size);
void		sha256_finalize(t_sha256_ctx *ctx);
void		print_sha256_hash(t_sha256_state result);
uint32_t	rotr(uint32_t a, int i);
uint32_t	compute_big_s1(uint32_t e);
uint32_t	compute_big_s0(uint32_t a);
uint32_t	compute_s0(uint32_t word);
uint32_t	compute_s1(uint32_t word);

#endif
