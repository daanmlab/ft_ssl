/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabalm <dabalm@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 22:36:23 by dabalm            #+#    #+#             */
/*   Updated: 2025/11/27 22:36:24 by dabalm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void	print_hash_word(uint32_t word)
{
	print_hex_byte(((word >> 24) & 0xFF));
	print_hex_byte(((word >> 16) & 0xFF));
	print_hex_byte(((word >> 8) & 0xFF));
	print_hex_byte((word & 0xFF));
}

void	print_sha256_hash(t_sha256_state result)
{
	print_hash_word(result.a);
	print_hash_word(result.b);
	print_hash_word(result.c);
	print_hash_word(result.d);
	print_hash_word(result.e);
	print_hash_word(result.f);
	print_hash_word(result.g);
	print_hash_word(result.h);
}
