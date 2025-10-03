#include "minishell.h"

bool is_valid_filename(const char *filename) {

}

int is_valid_syntax_after_expansion(t_redirect *redirect) {
  t_redirect *iter = redirect;
  while (iter) {
    if (iter->redirect_kind == r_reading_until) {
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
