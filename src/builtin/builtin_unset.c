/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 15:24:13 by yurishik          #+#    #+#             */
/*   Updated: 2025/10/20 08:26:02 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief 環境変数を名前で指定してunsetする
 *
 * @author yurishik
 * @param envmap
 * @param name unsetしたい環境変数名
 * @return 環境変数名としてOKならFLG_TRUE, NGならFLG_FALSE
 */
int	builtin_unset(char **argv, t_map *envmap)
{
	char	*name;
	int		i;
	int		status;

	if (envmap == NULL)
		return (FAILED);
	status = SUCCESS;
	i = 1;
	while (argv[i] != NULL)
	{
		name = argv[i];
		if (!is_identifier(name))
		{
			perror_wrapper("unset", name, "not a valid identifier");
			status = 1;
			i++;
			continue ;
		}
		map_delete(envmap, name);
		i++;
	}
	return (status);
}
