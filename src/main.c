#include "../include/minishell.h"

/*
blank is space or tab from the definition
https://www.gnu.org/software/bash/manual/bash.html#Definitions-1
*/
int is_blank(int c) {
  if (c == ' ' || c == '\t')
    return TRUE;
  return FALSE;
}

t_word_list *new_word_list(char *word) {
  t_word_list *result = malloc(sizeof(t_word_list));
  result->word = word;
  result->next = NULL;
}

/*
inputを解析して、解析した結果を返す。
コマンド名とオプションをword_list構造体にいれる。
*/
int parse(char *input, t_command *command) {
  t_word_list *dummy_head;
  t_word_list *words = dummy_head;
  int i = 0;
  while (input[i]) {
    if (is_blank(input[i])) {
      i++;
      continue;
    }
    int word_start = i;
    while (!is_balnk(input[i])) {
      i++;
    }
    char *word = ft_substr(input, word_start, i - 1);
    words->next = new_word_list(word);
    words = words->next;
  }
  command->words = dummy_head->next;
  return SUCCESS;
}

/*
リンクトリストから文字列の配列に変換する。
wordsには最低でも一つの文字列が入っていると仮定する。
*/
char **convert_word_list_to_string_array(t_word_list *words) {
  int num_words = 0;
  t_word_list *iter = words;
  while (iter) {
    num_words++;
    iter = iter->next;
  }
  char **result = ft_calloc(num_words + 1, sizeof(char *));
  int i = 0;
  iter = words;
  while (i < num_words) {
    result[i] = iter->word;
    i++;
    iter = iter->next;
  }
  return result;
}

/*
現在はコマンドが一つしかないが、任意の数のコマンドを動的に割り当てる
必要が出てきたら、command自体も解放する。
*/
void clean_command(t_command *command) {
  t_word_list *iter = command->words;
  while (iter) {
    t_word_list *next = iter->next;
    free(iter->word);
    iter = next;
  }
  command == NULL;
}

/*
parseされたcommandを実行する.
*/
void execute_command(t_command command) {
  extern char **envrion;
  pid_t pid = fork();
  if (pid == CHILD) {
    char **command_and_arguments = convert_word_list_to_str_array(command.words);
    if (ft_strchr(command_and_arguments[0], '/') > 0) {
      execve(command_and_arguments[0], command_and_arguments, envrion);
    }
    // Skip implementing builtin
    char *path = find_path(command_and_arguments[0]);
    if (path == NULL) {
      free_words(command_and_arguments);
      // clean command
      // print error message
      // exit(COMMAND_NOT_FOUND)
    }
    if (access(path, X_OK) == FAILED) {
      // free command and arguments
      // clean command
      // print error message
      // exit(No permission)
    }
    execve(path, command_and_arguments, envrion);
  }
  // clean_command(command)
  // waitpid()
}

int main(void) {
  while (TRUE) {
    char *input = readline("> ");
    if (input == NULL) {
      free(input);
      exit(EXIT_SUCCESS);
    }
    t_command command;
    parse(input, &command);
    // execute_command(command);
    // free everything
  }
}
