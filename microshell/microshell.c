#define CD_BAD_ARGS "error: cd: bad arguments\n"
#define CD_BAD_ARGS_L sizeof(CD_BAD_ARGS)
#define CD_CHDIR_FAIL "error: cd: cannot change directory to "

#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

#include <sys/types.h>
#include <sys/wait.h>

#include <stdio.h>

int	ft_strlen(const char *s)
{
	int	n;
	
	n = 0;
	while (s[n] != '\0')
		n++;
	return (n);
}

int	error(const char *s, const char *s2)
{
	write(2, s, ft_strlen(s));
	if (s2 != NULL)
		write(2, s2, ft_strlen(s2));
	write(2, "\n", 1);
	exit(1);
	return (1);
}

int	check_av(int ac, char **av)
{
	bool	pipe;

	pipe = false;
	for (int i = 1; i < ac; ++i)
	{
		if (pipe && (av[i] == NULL || strcmp(av[i], "|") == 0 || av[i][0] == ';'))
			return (0);
		else
			pipe = false;
		if (strcmp(av[i], "|") == 0)
		{
			if (i == 1)
				return (0);
			pipe = true;
		}
	}
	if (pipe)
		return (0);
	return (1);
}

int len_av(char **s)
{
	int	len;

	len = 0;
	while (s[len] && strcmp(s[len], "|") && strcmp(s[len],";"))
		++len;
	return (len);
}
int	main(int ac, char **av, char **env)
{
	//char	**args;
	int		pid;
	int		fds[2];
	int		last_pipe;
	int		i;
	if (ac < 2)
		return (1);
	//if (!check_av(ac, av))
	//	return (error("error: parsing: pipe", NULL));
	i = 0;
	last_pipe = 0;
	while (av[i] && av[i+1])
	{
		av = av + i + 1;
		i = len_av(av);
		if (strcmp(*av, "cd") == 0)
		{
			if (i != 2)
				return (error(CD_BAD_ARGS, NULL));
			if (chdir(av[1]) < 0)
				return (error(CD_CHDIR_FAIL, av[1]));
		}
		// Command solo / last
		else if (i != 0 && (!av[i] || !strcmp(av[i], ";")))
		{
			pid = fork();
			if (pid < 0)
				return (error("error: fatal", NULL));
			if (pid == 0)
			{
				if (last_pipe)
				{
					if (dup2(last_pipe, 0) == -1)
						return (error("error: fatal", NULL));
					close(last_pipe);
				}
				av[i] = NULL;
				if (execve(*av, av, env) == -1)
					return (error("error: cannot execute ", *av));
			}
			else if (pid > 0)
			{
				if (last_pipe)
					close(last_pipe);
				waitpid(pid, NULL, 0);
				last_pipe = 0;
			}
		}
		// Middle command or First
		else if (i != 0 && !strcmp(av[i], "|"))
		{
			if (pipe(fds))
				return (error("error: fatal", NULL));
			pid = fork();
			if (pid < 0)
				return (error("error: fatal", NULL));
			if (pid == 0)
			{
				if (last_pipe)
				{
					if (dup2(last_pipe, 0) == -1)
						return (error("error: fatal", NULL));
					close(last_pipe);
				}
				close(fds[0]);
				if (dup2(fds[1], 1) == -1)
					return (error("error: fatal", NULL));
				close(fds[1]);
				av[i] = NULL;
				if (execve(*av, av, env) == -1)
					return (error("error: cannot execute ", *av));
			}
			else if (pid > 0)
			{
				if (last_pipe)
					close(last_pipe);
				last_pipe = fds[0];
				close(fds[1]);
				waitpid(pid, NULL, 0);
			}
		}
	}
}
