/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdparse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikeda <kikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 22:43:53 by kikeda            #+#    #+#             */
/*   Updated: 2021/02/04 22:49:16 by kikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

#define MAXARGS 20
#define ARGLEN 100

int		execute(char *arglist[])
{
	int pid;
	int exitstatus;

	pid = fork();
	if (pid == -1)
	{
		perror("fork failed");
		exit(1);
	}
	else if (pid == 0)
	{
		execvp(arglist[0], arglist);
		perror("execvp failed");
		exit(1);
	}
	else
	{
		while (wait(&exitstatus) != pid)
			;
		printf("child exited with status %d,%d\n",
					exitstatus >> 8, exitstatus & 0377);
	}
}

char	*makestring(char *buf)
{
	char *cp;

	buf[strlen(buf) - 1] = '\0';
	cp = malloc(strlen(buf) + 1);
	if (cp == NULL)
	{
		fprintf(stderr, "no memory\n");
		exit(1);
	}
	strcpy(cp, buf);
	return (cp);
}

int		main(void)
{
	char	*arglist[MAXARGS + 1];
	int		numargs;
	char	argbuf[ARGLEN];

	numargs = 0;
	while (numargs < MAXARGS)
	{
		printf("Arg[%d]? ", numargs);
		if (fgets(argbuf, ARGLEN, stdin) && *argbuf != '\n')
			arglist[numargs++] = makestring(argbuf);
		else
		{
			if (numargs > 0)
			{
				arglist[numargs] = NULL;
				execute(arglist);
				numargs = 0;
			}
		}
	}
	return (0);
}
