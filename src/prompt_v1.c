#include "../include/minishell.h"


/*
find last /, add $> 
*/

char	*ft_prompt(char *str)
{
	while (*str)
		str++;
	while (*str != '/')
		str--;
	str++;
	return (ft_strjoin(str, "$> "));
}