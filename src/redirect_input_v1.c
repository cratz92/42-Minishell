#include "../include/minishell.h"

// fd 0 = STDIN_FILENO
// fd 1 = STDOUT_FILENO
// fd 2 = STDERR_FILENO

// cmd < file ------  read content of file as input to the cmd
int redirection_in(char **cmd, char **envp)
{
    return 0;
}


// cmd << delimiter ---------- read input until it finds delimiter. thn fed into the stdin of the cmd
int ft_heredoc(char **cmd, char **envp)
{
    // line of thought: 
    // create a blanck file.txt
    // print on the prompt the text as we write
    // as we hit delimiter, close the file
    // use redirection_in into cmd with file we created
    // delete file



    return 0;
}