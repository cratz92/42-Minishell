#include "../include/minishell.h"

void	ft_var_add_back(t_var **head, t_var *new)
{
	t_var	*ptr;

	if (ft_strlen(new->name) == 0)
		return ;
	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	ptr = *head;
	while (45)
	{
		if (ft_strexact(new->name, ptr->name) == true)
		{
			ptr->content = new->content;
			return ;
		}
		if (ptr->next != NULL)
			ptr = ptr->next;
		else
		{
			ptr->next = new;
			break;
		}
	}
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
	j = 0;
	while (token->cmd[i])
		var->content[j++] = token->cmd[i++];
	var->content[j] = 0;
	return (var);
}

void	check_token_to_variables(t_minishell **shell)
{
	t_token *tkn;

	tkn = (*shell)->head;
	while (tkn)
	{
		if (ft_strlook(tkn->cmd, "="))
			ft_var_add_back(&(*shell)->var, ft_token_to_var(tkn));
		tkn = tkn->next;
	}
}
