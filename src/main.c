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

char **convert_word_list_to_string_array() {

}

/*
parseされたcommandを実行する.
返り値は、EXECUTION_SUCCESSかEXECUTION_FAILURE.
*/
int execute_command(t_command command) {
  char **command_and_arugments = convert_word_list_to_string_array();
  // clean_command(command)
  // fork
  // 
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
