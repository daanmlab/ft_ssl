/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabalm <dabalm@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 22:36:45 by dabalm            #+#    #+#             */
/*   Updated: 2025/11/27 22:36:46 by dabalm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	hash_fd_to_buffer(int fd, t_hash_algorithm *algo, void *ctx)
{
	char	buffer[4096];
	int		bytes_read;

	algo->init(ctx);
	bytes_read = read(fd, buffer, sizeof(buffer));
	while (bytes_read > 0)
	{
		algo->update(ctx, (const uint8_t *)buffer, (size_t)bytes_read);
		bytes_read = read(fd, buffer, sizeof(buffer));
	}
}

static void	print_string_normal(char *str, t_hash_algorithm *algo, uint8_t *ctx)
{
	ft_putstr_out(algo->name);
	ft_putstr_out("(\"");
	ft_putstr_out(str);
	ft_putstr_out("\")= ");
	algo->print_hash(ctx);
	ft_putchar_out('\n');
}

void	process_hash_string(char *str, t_hash_flags *flags)
{
	uint8_t		ctx[256];
	size_t		len;

	len = 0;
	while (str[len])
		len++;
	flags->algo->init(ctx);
	flags->algo->update(ctx, (const uint8_t *)str, len);
	flags->algo->finalize(ctx);
	if (flags->quiet)
	{
		flags->algo->print_hash(ctx);
		ft_putchar_out('\n');
	}
	else if (flags->reverse)
	{
		flags->algo->print_hash(ctx);
		ft_putstr_out(" \"");
		ft_putstr_out(str);
		ft_putstr_out("\"\n");
	}
	else
		print_string_normal(str, flags->algo, ctx);
}

static void	print_file_error(char *filename, t_hash_algorithm *algo)
{
	ft_putstr_err("ft_ssl: ");
	ft_putstr_err(algo->name);
	ft_putstr_err(": ");
	ft_putstr_err(filename);
	ft_putstr_err(": No such file or directory\n");
}

static void	print_file_normal(char *filename, t_hash_algorithm *algo,
						uint8_t *ctx)
{
	ft_putstr_out(algo->name);
	ft_putstr_out("(");
	ft_putstr_out(filename);
	ft_putstr_out(")= ");
	algo->print_hash(ctx);
	ft_putchar_out('\n');
}

void	process_hash_file(char *filename, t_hash_flags *flags)
{
	int			fd;
	uint8_t		ctx[256];

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		print_file_error(filename, flags->algo);
		return ;
	}
	hash_fd_to_buffer(fd, flags->algo, ctx);
	close(fd);
	flags->algo->finalize(ctx);
	if (flags->quiet)
	{
		flags->algo->print_hash(ctx);
		ft_putchar_out('\n');
	}
	else if (flags->reverse)
	{
		flags->algo->print_hash(ctx);
		ft_putchar_out(' ');
		ft_putstr_out(filename);
		ft_putchar_out('\n');
	}
	else
		print_file_normal(filename, flags->algo, ctx);
}
