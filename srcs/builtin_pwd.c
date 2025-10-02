/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 15:23:50 by yurishik          #+#    #+#             */
/*   Updated: 2025/10/02 15:24:08 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief ビルトイン関数のpwd
 *
 * @author yurishik
 * @return 正常なら0、エラーなら1(ディレクトリが存在しない場合などに発生)
 */
int	builtin_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		printf("%s\n", cwd);
		free(cwd);
		return (SUCCESS);
	}
	else
	{
		perror("pwd");
		return (FAILURE);
	}
}
