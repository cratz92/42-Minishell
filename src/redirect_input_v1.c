#include "../include/minishell.h"

// realloc for minishell 
static void	*ft_realloc_ms(void *ptr, size_t size)
{
	char	*temp;
    size_t  ptrLen;
    int i;

    ptrLen = ft_strlen(ptr)
	temp = malloc(sizeof(char) * (ptrLen + size + 1));
	if (temp == NULL)
		return (NULL);
	i = 0;
    ft_memset(temp, 0, ptrLen + size + 1);
    while (ptr[i] != '\0')
    {
        temp[i] = ptr[i];
        i++;
    }
    temp[ptrLen + size + 1] = '\0';
	return (temp);
}

static int	ft_strstr_ms(const char *s1, const char *s2)
{
	size_t	i;
    size_t  j;

	i = 0;
    j = 0;
	if (!s1)
		return (0);
    while ((s2[j] == '\t') || (s2[j] == '\n') || (s2[j] == '\v')
			|| (s2[j] == '\f') || (s2[j] == '\r') || (s2[j] == ' '))
			j++;
	while (s1[i] != '\0')
    {
        if (s1[i] != s2[j + i])
            return (0)
        i++;
    }
	return (i);
}


// cmd < file ------  read content of file as input to the cmd
int redirection_in(char **cmd, char **envp)
{
    char *path;
    char **temp;
    int fd;
    char buff;
    int read_count = 0;
    char *file_content = NULL;

    fd = open(cmd[1], O_RDONLY, 0777);
    if (fd < 0)
        return(1);
    dup2(fd, STDIN_FILENO);
    close(fd);
    while (read(fd, &buff, 1) != 0)
    {
        file_content = (char *)realloc(file_content, ft_strlen(file_content) + 2);
        file_content = strlcat(file_content, &buff, ft_strlen(file_content) + 2);
    }
    temp = ft_split(cmd[0], ' ');
    path = check_path(temp[0], envp);
    char *arg[50] = {path, file_content, NULL};
    execve(path, arg, envp);
    


    return 0;
}


// cmd << delimiter ---------- read input until it finds delimiter. thn fed into the stdin of the cmd
int ft_heredoc(char **cmd, char **envp)
{
    int fd;
    char *temp_file;
    char *tmp;
    
    // line of thought: 
    // create a blanck file.txt
    temp_file = "temp_heredoc";
    fd = open(temp_file, O_RDWR | O_CREAT | O_TRUNC, 0777);
    
    // print on the prompt the text as we write
    while (true)
    {
        tmp = readline("heredoc> ");
        if (!tmp)
            exit(1);
        // as we hit delimiter, close the file
        if (ft_strstr_ms(tmp, cmd[1]))
            break ;
        write(fd, tmp, ft_strlen(tmp));
        write(fd, "\n", 1);
    }
    close(fd);
    // use redirection in to output the final file to std output
    char *temp_cmd[50] = {cmd[0], temp_file, NULL};
    redirection_in(temp_cmd, envp);
    // redirection_in({cmd[0], temp_file, NULL}, envp);

    // delete file
    unlink(temp_file);

    return 0;
}