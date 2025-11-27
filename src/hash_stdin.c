/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_stdin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabalm <dabalm@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 22:36:48 by dabalm            #+#    #+#             */
/*   Updated: 2025/11/27 22:36:49 by dabalm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	process_hash_stdin(t_hash_flags *flags)
{
	uint8_t	ctx[256];

	hash_fd_to_buffer(STDIN_FILENO, flags->algo, ctx);
	flags->algo->finalize(ctx);
	if (flags->quiet)
	{
		flags->algo->print_hash(ctx);
		ft_putchar_out('\n');
	}
	else if (flags->reverse)
	{
		flags->algo->print_hash(ctx);
		ft_putstr_out(" *stdin");
		ft_putchar_out('\n');
	}
	else
	{
		ft_putstr_out("(stdin)= ");
		flags->algo->print_hash(ctx);
		ft_putchar_out('\n');
	}
}
