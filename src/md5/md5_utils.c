/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabalm <dabalm@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 22:31:53 by chief             #+#    #+#             */
/*   Updated: 2025/11/27 22:35:43 by dabalm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static const uint32_t	g_md5_k[64] = {0xd76aa478, 0xe8c7b756, 0x242070db,
	0xc1bdceee, 0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
	0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be, 0x6b901122,
	0xfd987193, 0xa679438e, 0x49b40821, 0xf61e2562, 0xc040b340,
	0x265e5a51, 0xe9b6c7aa, 0xd62f105d, 0x02441453, 0xd8a1e681,
	0xe7d3fbc8, 0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
	0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a, 0xfffa3942,
	0x8771f681, 0x6d9d6122, 0xfde5380c, 0xa4beea44, 0x4bdecfa9,
	0xf6bb4b60, 0xbebfbc70, 0x289b7ec6, 0xeaa127fa, 0xd4ef3085,
	0x04881d05, 0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039, 0x655b59c3,
	0x8f0ccc92, 0xffeff47d, 0x85845dd1, 0x6fa87e4f, 0xfe2ce6e0,
	0xa3014314, 0x4e0811a1, 0xf7537e82, 0xbd3af235, 0x2ad7d2bb,
	0xeb86d391};

static const uint32_t	g_md5_s[64] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12,
	17, 22, 7, 12, 17, 22, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14,
	20, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 6, 10, 15,
	21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};

uint32_t	f(uint32_t b, uint32_t c, uint32_t d, int i)
{
	if (i >= 0 && i <= 15)
		return ((b & c) | ((~b) & d));
	else if (i >= 16 && i <= 31)
		return ((d & b) | ((~d) & c));
	else if (i >= 32 && i <= 47)
		return (b ^ c ^ d);
	else
		return (c ^ (b | (~d)));
}

uint32_t	red_box(uint32_t input, int i)
{
	uint32_t	return_val;

	return_val = input;
	return_val += g_md5_k[i];
	return_val = (return_val << g_md5_s[i] | return_val >> (32 - g_md5_s[i]));
	return (return_val);
}

void	to_words(uint8_t *input, uint32_t words[])
{
	int	i;
	int	base;

	i = 0;
	while (i < 16)
	{
		base = i * 4;
		words[i] = ((uint32_t)input[base]
				+ ((uint32_t)input[base + 1] << 8)
				+ ((uint32_t)input[base + 2] << 16)
				+ ((uint32_t)input[base + 3] << 24));
		i++;
	}
}

int	get_word_index(int i)
{
	if (i >= 0 && i <= 15)
		return (i);
	if (i >= 16 && i <= 31)
		return (((i * 5) + 1) % 16);
	if (i >= 32 && i <= 47)
		return (((i * 3) + 5) % 16);
	if (i >= 48 && i <= 63)
		return ((i * 7) % 16);
	return (i);
}
