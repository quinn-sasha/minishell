#include "minishell.h"

int	xpipe(int pipefd[2])
{
	int	ret;

	ret = pipe(pipefd);
	if (ret < 0)
		fatal_error("xpipe");
	return (ret);
}
