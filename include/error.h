#ifndef ERROR_H
#define ERROR_H

#define PREFIX_ERROR "micro-shell: "

void prefix_error(void);
void unclosed_quote_error(void);
void syntax_error(const char *unexpected_token);
void fatal_error(const char *message);
void perror_wrapper(const char *s1, const char *s2, const char *message);

#endif
