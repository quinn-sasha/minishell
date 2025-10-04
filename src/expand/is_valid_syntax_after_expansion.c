#include "minishell.h"

bool is_valid_filename(const char *filename) {
  if (*filename == '\0')
    return false;
  char *ifs_trimmed = ft_strtrim(filename, DEFAULT_IFS_CHARS);
  if (*ifs_trimmed == '\0') {
    free(ifs_trimmed);
    return false;
  }
  int num_words = count_words(ifs_trimmed, DEFAULT_IFS_CHARS);
  free(ifs_trimmed);
  if (num_words != 1)
    return false;
  return true;
}

int is_valid_syntax_after_expansion(t_redirect *redirect) {
  t_redirect *iter = redirect;
  while (iter) {
    if (iter->is_filename_expanded == false) {
      iter = iter->next;
      continue;
    }
    char *filename = iter->to.filename;
    if (!is_valid_filename(filename)) {
      ambiguous_redirect_error();
      return false;
    }
    iter = iter->next;
  }
  return true;
}
