/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 08:21:22 by yurishik          #+#    #+#             */
/*   Updated: 2025/09/08 09:36:56 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief envの要素数を返す
 *
 * @author yurishik
 * @param env // 構造体を渡したほうがいい？
 * @return envの要素数
 */
int	get_env_size(char **env)
{
	int	count;

	count = 0;
	while (env[count])
		count++;
	return (count);
}

/**
 * @brief environをコピーして配列に持つ
 *
 * @author yurishik
 * @param dest 配列のポインタ // 構造体を渡したほうがいい？
 * @param environ externしたenviron
 * @return 正常終了ならSUCCESS、エラーならFAILURE
 */
int	copy_env(char ***dest, char **environ)
{
	int		i;
	char	**result;

	result = (char **)malloc(sizeof(char *) * (get_env_size(environ) + 1));
	if (!result)
		return (FAILURE);
	i = 0;
	while (i < get_env_size(environ))
	{
		if (ft_strndup(environ[i], ft_strlen(environ[i]), &result[i]) == FAILURE)
		{
			free_str_array(result);
			return (FAILURE);
		}
		i++;
	}
	result[i] = NULL;
	*dest = result;
	return (SUCCESS);
}

/**
 * @brief environの値をもとに構造体を初期化する
 *
 * @author yurishik
 * @param env
 * @param environ externしたenviron
 * @return 正常終了ならSUCCESS、エラーならFAILURE
 */
int	initialize_environ(t_environ *env, char **environ)
{
	if (copy_env(&env->env, environ) == FAILURE)
		return (FAILURE);
	env->last_status = 0;
	return (SUCCESS);
}

/**
 * @brief 環境変数を保持している構造体の中からkeyで該当の項目を探す
 *
 * @author yurishik
 * @param env 構造体のポインタ
 * @param key 探したいkey
 * @return 何番目か(env->env[i]で該当項目を取得できる)
 */
int	find_env_key(t_environ *env, const char *key)
{
	size_t	len;
	int		i;

	i = 0;
	len = ft_strlen(key);
	while (env->env[i] != NULL)
	{
		if (ft_strncmp(env->env[i], key, len) == 0 && env->env[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

/**
 * @brief 環境変数名のvalid.
 *
 * @author yurishik
 * @param name 自分で指定した環境変数名
 * @return 環境変数名として問題ないならFLG_TRUE, 問題があればFLG_FALSE
 */
int	is_env_key_name(const char *name)
{
	int	len;

	len = ft_strlen(name);
	if (len <= 0)
		return (FLG_FALSE);
	return (FLG_TRUE);
}

/**
 * @brief 構造体に入れたenvから指定のnameのものをunsetする
 *
 * @author yurishik
 * @param env 格納されている構造体
 * @param name 指定した環境変数名
 * @return 正常終了ならSUCCESS、エラーならFAILURE
 */
int	unset_env(t_environ *env, const char *name)
{
	int		i;
	int		j;
	int		index;
	char	**new_env;

	if (is_env_key_name(name) == FLG_FALSE)
		return (FAILURE); // SUCCESSでいいのかも
	index = find_env_key(env, name);
	if (index == -1)
		return (SUCCESS);
	new_env = (char **)malloc(sizeof(char *) * get_env_size(env->env));
	if (!new_env)
		return (FAILURE);
	i = 0;
	j = 0;
	while (i < get_env_size(env->env))
	{
		if (i == index)
		{
			free(env->env[i++]);
			continue ;
		}
		new_env[j] = env->env[i];
		j++;
		i++;
	}
	new_env[j] = NULL;
	free(env->env);
	env->env = new_env;
	return (SUCCESS);
}
