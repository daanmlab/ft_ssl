/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabalm <dabalm@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 22:36:29 by dabalm            #+#    #+#             */
/*   Updated: 2025/11/27 22:36:30 by dabalm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static const uint32_t	g_sha256_k[] = {0x428a2f98, 0x71374491, 0xb5c0fbcf,
	0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5, 0xd807aa98,
	0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7,
	0xc19bf174, 0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f,
	0x4a7484aa, 0x5cb0a9dc, 0x76f988da, 0x983e5152, 0xa831c66d, 0xb00327c8,
	0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967, 0x27b70a85,
	0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e,
	0x92722c85, 0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819,
	0xd6990624, 0xf40e3585, 0x106aa070, 0x19a4c116, 0x1e376c08, 0x2748774c,
	0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3, 0x748f82ee,
	0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7,
	0xc67178f2};

static void	update_vars(t_sha256_vars *v, uint32_t *words, int i)
{
	uint32_t	ch;
	uint32_t	maj;

	v->big_s1 = compute_big_s1(v->e);
	ch = (v->e & v->f) ^ ((~v->e) & v->g);
	v->temp1 = v->h + v->big_s1 + ch + g_sha256_k[i] + words[i];
	v->big_s0 = compute_big_s0(v->a);
	maj = (v->a & v->b) ^ (v->a & v->c) ^ (v->b & v->c);
	v->temp2 = v->big_s0 + maj;
}

static void	rotate_vars(t_sha256_vars *v)
{
	v->h = v->g;
	v->g = v->f;
	v->f = v->e;
	v->e = v->d + v->temp1;
	v->d = v->c;
	v->c = v->b;
	v->b = v->a;
	v->a = v->temp1 + v->temp2;
}

static void	update_state(t_sha256_ctx *ctx, uint32_t *words)
{
	t_sha256_vars	v;
	int				i;

	v.a = ctx->state.a;
	v.b = ctx->state.b;
	v.c = ctx->state.c;
	v.d = ctx->state.d;
	v.e = ctx->state.e;
	v.f = ctx->state.f;
	v.g = ctx->state.g;
	v.h = ctx->state.h;
	i = 0;
	while (i < 64)
	{
		update_vars(&v, words, i);
		rotate_vars(&v);
		i++;
	}
	ctx->state.a += v.a;
	ctx->state.b += v.b;
	ctx->state.c += v.c;
	ctx->state.d += v.d;
	ctx->state.e += v.e;
	ctx->state.f += v.f;
	ctx->state.g += v.g;
	ctx->state.h += v.h;
}

static uint32_t	get_word(uint8_t *block, int i)
{
	return (((uint32_t)block[(i * 4)] << 24)
		| ((uint32_t)block[(i * 4) + 1] << 16)
		| ((uint32_t)block[(i * 4) + 2] << 8)
		| ((uint32_t)block[(i * 4) + 3]));
}

static void	expand_words(uint32_t *words)
{
	int	i;

	i = 16;
	while (i < 64)
	{
		words[i] = words[i - 16] + compute_s0(words[i - 15])
			+ words[i - 7] + compute_s1(words[i - 2]);
		i++;
	}
}

static void	process_block(t_sha256_ctx *ctx)
{
	uint32_t	words[64];
	int			i;

	i = 0;
	while (i < 16)
	{
		words[i] = get_word(ctx->block, i);
		i++;
	}
	expand_words(words);
	update_state(ctx, words);
}

void	sha256_init(t_sha256_ctx *ctx)
{
	ctx->state.a = 0x6a09e667;
	ctx->state.b = 0xbb67ae85;
	ctx->state.c = 0x3c6ef372;
	ctx->state.d = 0xa54ff53a;
	ctx->state.e = 0x510e527f;
	ctx->state.f = 0x9b05688c;
	ctx->state.g = 0x1f83d9ab;
	ctx->state.h = 0x5be0cd19;
	ctx->block_len = 0;
	ctx->bitlen = 0x00;
}

void	sha256_update(t_sha256_ctx *ctx, const uint8_t *data, size_t size)
{
	ctx->bitlen += (uint64_t)size * 8;
	while (size-- > 0)
	{
		ctx->block[ctx->block_len++] = *(data++);
		if (ctx->block_len == 64)
		{
			process_block(ctx);
			ctx->block_len = 0;
		}
	}
}

static void	write_bits(t_sha256_ctx *ctx)
{
	int			i;
	uint32_t	bits;

	i = 7;
	bits = ctx->bitlen;
	while (i >= 0)
	{
		ctx->block[ctx->block_len + i] = (uint8_t)(bits & 0xFF);
		bits >>= 8;
		i--;
	}
	ctx->block_len += 8;
}

void	sha256_finalize(t_sha256_ctx *ctx)
{
	ctx->block[ctx->block_len++] = 0x80;
	if (ctx->block_len > 56)
	{
		while (ctx->block_len < 64)
			ctx->block[ctx->block_len++] = 0x00;
		process_block(ctx);
		ctx->block_len = 0;
	}
	while (ctx->block_len < 56)
		ctx->block[ctx->block_len++] = 0x00;
	write_bits(ctx);
	process_block(ctx);
	ctx->block_len = 0;
}
