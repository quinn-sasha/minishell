#include "../include/minishell.h"

/*
command_nameに対応する実行可能ファイルへの、絶対パスを取得する。
もしファイルが存在しなければ、NULLを返す。
*/
char *find_path(char *command_name) {
  char **paths = ft_split(getenv("PATH"), ':');
  int i = 0;
  while (paths[i]) {
    char *dir_path = ft_strjoin(paths[i], "/");
    char *path = ft_strjoin(dir_path, command_name);
    free(dir_path);
    if (access(path, F_OK) == FAILED) {
      free(path);
      i++;
      continue;
    }
    free_words(paths);
    return path;
  }
  free_words(paths);
  return NULL;
}
