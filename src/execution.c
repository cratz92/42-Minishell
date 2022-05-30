/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-l <cbrito-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 03:34:27 by cbrito-l          #+#    #+#             */
/*   Updated: 2022/03/21 03:34:27 by cbrito-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void *parse_args(char *str, char *envp[])
{
    char **temp;
    //int i;

    temp = NULL;
    temp = ft_split(str, '|');
    if (temp[1] != NULL)
        ft_pipe(temp, envp);
    temp = NULL;
    temp = ft_split(str, '>');
    if (temp[1] != NULL)
        redirection(temp, envp);
    else
    {
        temp = ft_split(str, ' ');
        command_execution(temp, envp);
    }
}


void command_execution(char **cmd,char *envp[])
{
    int resp;
    int pid;
    char *path;
    char *path2;
    char **buffer;
    int i;
    int j;

    j = -1;
    // This function is used to look for line initiate by PATH, at the env.
    while (!ft_strnstr(envp[++j], "PATH", 4))
        continue ;
    path = ft_strchr(envp[j], '=') + 1;
    buffer = ft_split(path, ':');
    i = -1;
    while(++i <= j)
    {
        path = ft_strjoin(buffer[i], "/");
        path2 = ft_strjoin(path, cmd[0]);
        resp = access(path2, F_OK);
        if (resp == 0)
            break;
    }
    path = ft_strjoin(buffer[i], "/");
    path2 = ft_strjoin(path, cmd[0]);
    char *arg[50] = {path2, cmd[1], NULL};
    pid = fork();
    if (pid == 0)
    {        
        execve(path2, arg, envp);
    }
    waitpid(pid, NULL, 0);
    //return 0;
}

char *check_path(char *cmd, char *envp[])
{
    int resp;
    int pid;
    char *path;
    char *path2;
    char **buffer;
    int i;
    int j;

    printf("the command is: %s", cmd);
    j = -1;
    // This function is used to look for line initiate by PATH, at the env.
    while (!ft_strnstr(envp[++j], "PATH", 4))
        continue ;
    path = ft_strchr(envp[j], '=') + 1;
    buffer = ft_split(path, ':');
    i = -1;
    while(++i <= j)
    {
        path = ft_strjoin(buffer[i], "/");
        path2 = ft_strjoin(path, cmd);
        resp = access(path2, F_OK);
        if (resp == 0)
            break;
    }
    path = ft_strjoin(buffer[i], "/");
    path2 = ft_strjoin(path, cmd);
    return path2;
}

