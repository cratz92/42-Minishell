#include "../include/minishell.h"

void	ft_var_add_back(t_var **head, t_var *new)
{
	t_var	*last_ptr;

	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	last_ptr = *head;
	while (42)
	{
		if (ft_strexact(new->name, last_ptr->name))
		{
			last_ptr->content = new->content;
			return ;
		}
		if (last_ptr->next != NULL)
			last_ptr = last_ptr->next;
		else
			break;
	}
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
	j = 0;
	while (token->cmd[i])
		var->content[j++] = token->cmd[i++];
	var->content[j] = 0;
	return (var);
}

void	check_token_to_variables(t_minishell **shell)
{
	t_token *tkn;
	t_var	*tmp;
	t_var	*var;

	tkn = (*shell)->head;
	var = (*shell)->var; 
	while (tkn)
	{
		// printf("checking=%s \n", tkn->cmd);
		if (ft_strlook(tkn->cmd, "="))
		{
			tmp = ft_token_to_var(tkn);
			ft_var_add_back(&(*shell)->var, tmp);
		}
		tkn=tkn->next;
	}
}

/* NOTES on 
$> test1=one test2=two
--> there are two cmds here and need to be seperated in targs
$> test1=onevone
--> need to find if test1 exist, if it does, replace the content
*/