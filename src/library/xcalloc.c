/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xcalloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squinn <squinn@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 15:47:50 by squinn            #+#    #+#             */
/*   Updated: 2025/09/14 15:49:00 by squinn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/xlibrary.h"

void *xcalloc(size_t nmemb, size_t size) {
  void *result = ft_calloc(nmemb, size);
  if (result == NULL) {
    fatal_error("xcalloc()");
  }
  return result;
}
