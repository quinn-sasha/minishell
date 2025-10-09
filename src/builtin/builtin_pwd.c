/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 16:46:19 by yurishik          #+#    #+#             */
/*   Updated: 2025/10/09 16:22:40 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief ビルトイン関数のpwd
 *
 * @author yurishik
 * @return 正常ならSUCCESS、エラーならFAILED(ディレクトリが存在しない場合などに発生)
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
		return (FAILED);
	}
}
