#ifndef XLIBRARY_H
#define XLIBRARY_H

void *xmalloc(size_t size);
void *xcalloc(size_t nmemb, size_t size);
char *xstrdup(const char *s);
int	xpipe(int pipefd[2]);

#endif
