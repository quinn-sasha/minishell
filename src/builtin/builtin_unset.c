/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 15:24:13 by yurishik          #+#    #+#             */
/*   Updated: 2025/10/19 12:30:37 by yurishik         ###   ########.fr       */
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
			i++;
			continue ;
		}
		map_delete(envmap, name);
		i++;
	}
	return (SUCCESS);
}
