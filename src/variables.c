#include "../include/minishell.h"

void	ft_var_add_back(t_var **lst, t_var *new)
{
	t_var	*last_ptr;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last_ptr = *lst;
	while (last_ptr->next != NULL)
		last_ptr = last_ptr->next;
	last_ptr->next = new;
}

t_var	*ft_token_to_var(t_token *token)
{
	t_var	*var;
	int		i;
	int		j;

	var = malloc(sizeof(t_var));
	var->name = NULL;
	var->content = NULL;
	var->next = NULL;
	var->name = malloc(sizeof(char) * ft_strlen(token->cmd));
	var->content = malloc(sizeof(char) * ft_strlen(token->cmd));
	i = 0;
	j = 0;
	while (token->cmd[i] != '=')
		var->name[j++] = token->cmd[i++];
	var->name[j] = 0;
	i++;
	while (token->cmd[i])
		var->content[j++] = token->cmd[i++];
	var->content[j] = 0;
	return (var);
}


void	check_token_to_variables(t_minishell **shell)
{
	t_token *tkn;
	t_var	*var;

	tkn = (*shell)->head;
	var = (*shell)->var;
	while (tkn)
	{
		// printf("checking=%s \n", tkn->cmd);
		if (ft_strlook(tkn->cmd, "="))
		{
			var = ft_token_to_var(tkn);
			// printf("added!\n");
		}
		tkn=tkn->next;
	}
}