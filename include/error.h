#ifndef ERROR_H
#define ERROR_H

#define PREFIX_ERROR "micro-shell: "

void prefix_error(void);
void syntax_error(const char *unexpected_token);
void fatal_error(const char *message);

#endif
