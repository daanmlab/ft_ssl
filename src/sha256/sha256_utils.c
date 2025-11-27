/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabalm <dabalm@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 22:36:29 by dabalm            #+#    #+#             */
/*   Updated: 2025/11/27 22:36:30 by dabalm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

uint32_t	rotr(uint32_t a, int i)
{
	return ((a >> i) | (a << (32 - i)));
}

uint32_t	compute_big_s1(uint32_t e)
{
	return (rotr(e, 6) ^ rotr(e, 11) ^ rotr(e, 25));
}

uint32_t	compute_big_s0(uint32_t a)
{
	return (rotr(a, 2) ^ rotr(a, 13) ^ rotr(a, 22));
}

uint32_t	compute_s0(uint32_t word)
{
	return (rotr(word, 7) ^ rotr(word, 18) ^ (word >> 3));
}

uint32_t	compute_s1(uint32_t word)
{
	return (rotr(word, 17) ^ rotr(word, 19) ^ (word >> 10));
}
