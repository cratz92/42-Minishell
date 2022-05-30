
#include "minishell.h"

// fd 0 = STDIN_FILENO
// fd 1 = STDOUT_FILENO
// fd 2 = STDERR_FILENO
// fd 3 = aqui.txt
// fd 4 = copy_s

int redirection(char **cmd, char **envp)
{
    char *path;
    //char *arg[50] = {path, NULL};
    char **temp;
    int fd;
    int copy_stdout;
    int pid;
    
    fd = open(cmd[1], O_CREAT | O_RDWR | O_APPEND, 0777);
    if (fd < 0)
        return(1);
    copy_stdout = dup(STDOUT_FILENO);
    dup2(fd, STDOUT_FILENO);
    pid = fork();
    if (pid == 0)
    {
        temp = ft_split(cmd[0], ' ');
        path = check_path(temp[0], envp);
        char *arg[50] = {path, temp[1], NULL};
        execve(path, arg, envp);
        close(fd);
        exit(1);
    }
    dup2(copy_stdout, STDOUT_FILENO);
    waitpid(pid, NULL, 0);
    close(fd);
    close(copy_stdout);
    //while(1);
    return 0;
}   

// lsof -c a.out  =  meter um while(1) no fim
