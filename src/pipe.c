#include "minishell.h"

// fd 0 = STDIN_FILENO
// fd 1 = STDOUT_FILENO
// fd 2 = STDERR_FILENO


int ft_pipe(char **cmd, char **envp)
{
    char *path;
    char *path2;
    //char *arg[50] = {path, NULL};
    char **temp;
    char **temp2;
    int fd[2];
    int pid;
    int pid2;

    
    if (pipe(fd) == -1)
        return 1;
    if ((pid = fork()) == -1)
        return 2;
    if (pid == 0)
    {
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
        temp = ft_split(cmd[0], ' ');
        path = check_path(temp[0], envp);
        char *arg[50] = {path, temp[1], NULL};
        execve(path, arg, envp);
    }
    if ((pid2 = fork()) == -1)
        return 2;
    if (pid2 == 0)
    {
        
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        temp2 = ft_split(cmd[1], ' ');
        path2 = check_path(temp2[0], envp);
        char *arg2[50] = {path2, temp2[1], NULL};
        execve(path2, arg2, envp);
    }
    close(fd[0]);
    close(fd[1]);
    waitpid(pid, NULL, 0);
    waitpid(pid2, NULL, 0);
    //printf("Done!!");
    //while(1);
    return 0;
}   

// lsof -c a.out  =  meter um while(1) no fim
