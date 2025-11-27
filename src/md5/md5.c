/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabalm <dabalm@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 22:36:16 by dabalm            #+#    #+#             */
/*   Updated: 2025/11/27 22:36:17 by dabalm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void	process_block(struct s_md5_ctx *ctx)
{
	uint32_t	words[16];
	uint32_t	a;
	uint32_t	b;
	uint32_t	c;
	uint32_t	d;
	uint32_t	temp;
	int			i;
	uint32_t	fval;
	uint32_t	g;

	a = ctx->state.a;
	b = ctx->state.b;
	c = ctx->state.c;
	d = ctx->state.d;
	to_words(ctx->block, words);
	i = 0;
	while (i < 64)
	{
		fval = f(b, c, d, i);
		g = get_word_index(i);
		temp = d;
		d = c;
		c = b;
		b = b + red_box(a + fval + words[g], i);
		a = temp;
		i++;
	}
	ctx->state.a += a;
	ctx->state.b += b;
	ctx->state.c += c;
	ctx->state.d += d;
}

void	md5_init(t_md5_ctx *ctx)
{
	ctx->state.a = 0x67452301;
	ctx->state.b = 0xefcdab89;
	ctx->state.c = 0x98badcfe;
	ctx->state.d = 0x10325476;
	ctx->block_len = 0;
	ctx->bitlen = 0x00;
}

void	md5_update(t_md5_ctx *ctx, const uint8_t *data, size_t size)
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

void	md5_finalize(t_md5_ctx *ctx)
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
	while (ctx->block_len < 64)
	{
		ctx->block[ctx->block_len++] = (uint8_t)(ctx->bitlen & 0xFF);
		ctx->bitlen >>= 8;
	}
	process_block(ctx);
	ctx->block_len = 0;
}
