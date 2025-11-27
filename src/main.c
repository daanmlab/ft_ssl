/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabalm <dabalm@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 22:36:51 by dabalm            #+#    #+#             */
/*   Updated: 2025/11/27 22:36:51 by dabalm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static t_hash_algorithm	*find_algorithm(const char *name)
{
	if (ft_strcmp(name, "md5") == 0)
		return (get_md5_algorithm());
	if (ft_strcmp(name, "sha256") == 0)
		return (get_sha256_algorithm());
	return (NULL);
}

static void	print_error(char *cmd)
{
	ft_putstr_err("ft_ssl: Error: '");
	ft_putstr_err(cmd);
	ft_putstr_err("' is an invalid command.\\n\\n");
	ft_putstr_err("Standard commands:\\n\\nMessage Digest commands:\\n");
	ft_putstr_err("md5\\nsha256\\n");
}

int	main(int argc, char *argv[])
{
	t_hash_algorithm	*algo;

	if (argc < 2)
	{
		ft_putstr_err("usage: ft_ssl command [flags] [file/string]\\n");
		return (1);
	}
	algo = find_algorithm(argv[1]);
	if (algo != NULL)
		return (handle_hash_command(argc, argv, algo));
	print_error(argv[1]);
	return (1);
}
