// return last_status
int	wait_pipe(pid_t last_pid)
{
	int	last_status;
	int	wait_status;
	pid_t wait_pid;
	
	while (1)
	{
		wait_pid = wait(&wait_status);
		if (wait_pid == last_pid)
		{
			if (WIFSIGNALED(wait_status))
				last_status = 128 + WTERMSIG(wait_status);
			else
				last_status = WEXITSTATUS(wait_status);
		}
		else if (wait_pid < 0) // error
		{
			if (errno == ECHILD)
				break;
			if (errno == EINTR)
				continue;
			else
				perror("wait"); // TODO
		}
	}
	return (last_status);
}