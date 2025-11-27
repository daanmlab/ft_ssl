/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_algorithms.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabalm <dabalm@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 22:36:53 by dabalm            #+#    #+#             */
/*   Updated: 2025/11/27 22:36:53 by dabalm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void	sha256_init_wrapper(void *ctx)
{
	sha256_init((t_sha256_ctx *)ctx);
}

static void	sha256_update_wrapper(void *ctx, const uint8_t *data, size_t size)
{
	sha256_update((t_sha256_ctx *)ctx, data, size);
}

static void	sha256_finalize_wrapper(void *ctx)
{
	sha256_finalize((t_sha256_ctx *)ctx);
}

static void	sha256_print_hash_wrapper(void *ctx)
{
	print_sha256_hash(((t_sha256_ctx *)ctx)->state);
}

t_hash_algorithm	*get_sha256_algorithm(void)
{
	static t_hash_algorithm	algo = {
		"sha256",
		sha256_init_wrapper,
		sha256_update_wrapper,
		sha256_finalize_wrapper,
		sha256_print_hash_wrapper
	};

	return (&algo);
}
