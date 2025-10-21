/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurishik <yurishik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 08:04:38 by yurishik          #+#    #+#             */
/*   Updated: 2025/10/20 08:09:46 by yurishik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRON_H
# define ENVIRON_H

typedef struct s_item	t_item;
typedef struct s_map	t_map;

struct	s_item
{
	char	*name;
	char	*value; // value can be NULL
	int		is_exported; // TRUE or FALSE
	t_item	*next; // Next element or NULL
};

struct	s_map
{
	t_item	head;
	int		last_status;
};

// is_identifier.c
bool	is_alpha_underscore(int c);
bool	is_alpha_underscore_num(int c);
bool	is_identifier(const char *s);
// map_set.c
void	set_name_and_value(const char *string, char **name, char **value);
void	map_insert(t_map *map, const char *name, const char *value,
			int is_exported);
void	map_update_item(t_item *item, const char *value);
void	map_set_internal(t_map *map, char *name, char *value, int is_exported);
void	map_set(t_map *map, const char *string, int is_exported);
// map.c
t_item	*map_get(t_map *map, const char *name);
int		map_delete(t_map *map, const char *name);
char	*xgetenv(t_map *envmap, const char *name);
char	**get_envmap(t_map *envmap);
size_t	count_map_item(t_map *envmap);
// item.c
t_item	*new_item(char *name, char *value);
// environ.c
t_map	*init_environment(void);

#endif
