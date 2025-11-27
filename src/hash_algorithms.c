/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_algorithms.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabalm <dabalm@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 22:36:40 by dabalm            #+#    #+#             */
/*   Updated: 2025/11/27 22:36:40 by dabalm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void	md5_init_wrapper(void *ctx)
{
	md5_init((t_md5_ctx *)ctx);
}

static void	md5_update_wrapper(void *ctx, const uint8_t *data, size_t size)
{
	md5_update((t_md5_ctx *)ctx, data, size);
}

static void	md5_finalize_wrapper(void *ctx)
{
	md5_finalize((t_md5_ctx *)ctx);
}

static void	md5_print_hash_wrapper(void *ctx)
{
	print_md5_hash(((t_md5_ctx *)ctx)->state);
}

t_hash_algorithm	*get_md5_algorithm(void)
{
	static t_hash_algorithm	algo = {
		"md5",
		md5_init_wrapper,
		md5_update_wrapper,
		md5_finalize_wrapper,
		md5_print_hash_wrapper
	};

	return (&algo);
}
