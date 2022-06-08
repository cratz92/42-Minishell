#include "../include/minishell.h"

void	free_str(char *str)
{
	printf("free_str:%s\n", str);
	if (!str)
		return ;
	free(str);
	str = NULL;
}

void	free_variables(t_var **var)
{
	t_var	*v;

	v = *var;
	if (!v)
		return ;
	while (v)
	{
		if (v->name)
			free_str(v->name);
		if (v->content)
			free_str(v->content);
		v = v->next;
	}
	free(*var);
	(*var) = NULL;
}

void	free_array(char **arr)
{
	char	**cpy;

	//TO WORK ON
	cpy = arr;
	while (*arr)
	{
		if (*arr)
			free_str(*arr);
		arr++;
	}
	//ARG FREE & ARG NULL ?¿
	free(cpy);
	cpy = NULL;
}


void	free_tokens(t_token **tokens)
{
	t_token	*t;
	int		i;

	t = *tokens;
	if (!t)
		return ;
	while (t)
	{
		if (t->cmd)
			free_str(t->cmd);
		if (t->args)
		{
			i = 0;
			while (t->args[i])
				free_str(t->args[i++]);
		}
		t = t->next;
	}
	free(*tokens);
	(*tokens) = NULL;
}


int	free_minishell(t_minishell **shell)
{
	t_minishell *s;
	int			exitcode;

	s = *shell;

	exitcode = s->ec;
	if (s->head)
		free_tokens(s->head);
	if (s->var)
		free_variables(s->var);
	//MALLOC SEGFAULT BUG
	free(*shell);
	(*shell) = NULL;
	return (exitcode);
}