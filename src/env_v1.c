#include "../include/minishell.h"

void	malloc_tvar(t_var **ptr)
{
	(*ptr) = malloc(sizeof(t_var));
	(*ptr)->name = NULL;
	(*ptr)->content = NULL;
	(*ptr)->next = NULL;
}

void	ft_parse_env(t_var **var, char *str)
{
	t_var	*ptr;
	int		i;
	int		j;

	if (!str)
		return ;
	i = 0;
	while(str[i] != '=')
		i++;	// printf("%d, ", i);
	(*var)->name = ft_strldup(str, i);
	j = ++i;
	while (str[j] != 0)
		j++;
	(*var)->content = ft_strldupimp(str, i, j);
}

t_var	*init_parse_env(char **env)
{
	t_var	*vhead;
	t_var	*v;
	t_var	*v2;
	int		i;
	int		j;

	i = 0;
	malloc_tvar(&vhead);
	ft_parse_env(&vhead, env[i]);
	v2 = NULL;
	while (env[++i])
	{
		malloc_tvar(&v);
		ft_parse_env(&v, env[i]);
		if (vhead->next == NULL)
			vhead->next = v;
		else if (v2)
			v2->next = v;
		v2 = v;
	}
	return (vhead);
}
