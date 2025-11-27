/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabalm <dabalm@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 22:36:12 by dabalm            #+#    #+#             */
/*   Updated: 2025/11/27 22:36:13 by dabalm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	print_md5_hash(t_md5_state result)
{
	print_hex_byte((result.a & 0xFF));
	print_hex_byte(((result.a >> 8) & 0xFF));
	print_hex_byte(((result.a >> 16) & 0xFF));
	print_hex_byte(((result.a >> 24) & 0xFF));
	print_hex_byte((result.b & 0xFF));
	print_hex_byte(((result.b >> 8) & 0xFF));
	print_hex_byte(((result.b >> 16) & 0xFF));
	print_hex_byte(((result.b >> 24) & 0xFF));
	print_hex_byte((result.c & 0xFF));
	print_hex_byte(((result.c >> 8) & 0xFF));
	print_hex_byte(((result.c >> 16) & 0xFF));
	print_hex_byte(((result.c >> 24) & 0xFF));
	print_hex_byte((result.d & 0xFF));
	print_hex_byte(((result.d >> 8) & 0xFF));
	print_hex_byte(((result.d >> 16) & 0xFF));
	print_hex_byte(((result.d >> 24) & 0xFF));
}
