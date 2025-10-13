/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xmalloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squinn <squinn@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 15:25:03 by squinn            #+#    #+#             */
/*   Updated: 2025/09/16 19:14:38 by squinn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void *xmalloc(size_t size) {
  void *result = malloc(size);
  if (result == NULL) {
    fatal_error("xmalloc()");
  }
  return result;
}
