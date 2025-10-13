/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xcalloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squinn <squinn@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 15:47:50 by squinn            #+#    #+#             */
/*   Updated: 2025/09/16 19:14:27 by squinn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void *xcalloc(size_t nmemb, size_t size) {
  void *result = ft_calloc(nmemb, size);
  if (result == NULL) {
    fatal_error("xcalloc()");
  }
  return result;
}
