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

/*
parseされたcommandを実行する.
終了ステータスは、現段階では受け取らない。
*/
void execute_command(t_command command) {
  extern char **environ;
  pid_t pid = fork();
  if (pid != CHILD) {
    waitpid(pid, NULL, 0);
    return;
  }
  char **command_and_arguments = convert_word_list_to_string_array(command.words);
  if (ft_strchr(command_and_arguments[0], '/') > 0) {
    execve(command_and_arguments[0], command_and_arguments, environ);
  }
  // Skip implementing builtin
  char *path = find_path(command_and_arguments[0]);
  if (path == NULL) {
    free_words(command_and_arguments);
    clean_command(&command);
    ft_putendl_fd(COMMAND_NOT_FOUND_ERROR, STDERR_FILENO);
    exit(COMMAND_NOT_FOUND_STATUS);
  }
  if (access(path, X_OK) == FAILED) {
    free(path);
    free_words(command_and_arguments);
    clean_command(&command);
    ft_putendl_fd(PERMISSION_DENIED_ERROR, STDERR_FILENO);
    exit(PERMISSION_DENIED_STATUS);
  }
  execve(path, command_and_arguments, environ);
}
