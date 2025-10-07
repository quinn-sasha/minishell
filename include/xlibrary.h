#ifndef XLIBRARY_H
#define XLIBRARY_H

void *xmalloc(size_t size);
void *xcalloc(size_t nmemb, size_t size);
char *xstrdup(const char *s);
int xdup(int oldfd);
int xdup2(int oldfd, int newfd);
int	xpipe(int pipefd[2]);
int	xclose(int fd);


#endif
