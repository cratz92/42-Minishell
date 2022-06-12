#include "../include/minishell.h"

char	*get_preprompt(void)
{
	char	*p;
	char	tmp[202];
	int		i;
	int		j;

	getcwd(tmp, sizeof(tmp));
	p = malloc(sizeof(char) * ft_strlen(tmp));
	i = 7;
	j = 0;
	while (tmp[i] != '/')
		p[j++] = tmp[i++];
	p = ft_strjoin(p, "\033[0;31m@\033[0;33m42\033[0;32mLisboa\033[0m/");
	return (p);
}

char	*ft_prompt(char *str)
{
	while (*str)
		str++;
	while (*str != '/')
		str--;
	str++;
	
	return (ft_strjoin(str, "$> "));
}