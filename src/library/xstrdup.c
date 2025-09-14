/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xstrdup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squinn <squinn@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 18:26:33 by squinn            #+#    #+#             */
/*   Updated: 2025/09/14 18:29:10 by squinn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/xlibrary.h"

char *xstrdup(const char *s) {
  char *result = ft_strdup(s);
  if (result == NULL) {
    fatal_error("xstrdup()");
  }
  return result;
}
