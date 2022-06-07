#include "../include/minishell.h"

/*
validate $var check t_var
if found var = t_var->content
if not var = "";
*/

char	*var_for_content(char **str, t_var *var)
{
	char	*content;
	char	*tmp;
	char	*ptr;
	int		i;
	bool	found;

	i = 0;
	found = false;
	tmp = malloc(100);
	ptr = *str;
	while (*ptr != 0 && *ptr != 32)
	{
		tmp[i++] = *ptr;
		ptr++;
	}
	tmp[i] = 0;
	while (var)
	{
		if (ft_strexact(tmp, var->name))
		{
			found = true;
			content = ft_strdup(var->content);
			break;
		}
		var = var->next;
	}
	if (!found)
		content = ft_strdup("");
	*str = ptr;
	free(tmp);
	tmp = NULL;
	return (content);
}



char	*change_dollar_for_money(char *str, t_var *var)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	new = malloc(sizeof(char) * ft_strlen(str));
	while (*str)
	{
		j = ft_strlen(new);
		while (*str != '$' && *str != 0)
			new[j++] = (*str)++;
		if (*str == '$')
		{
			str++;
			new = ft_strjoin(new, var_for_content(&str, var));
		}
	}
	// printf("OK NEW = %s\n", new);
	return (new);
}

void	check_and_replace_if_variables(t_token **tkn, t_var *var)
{
	// printf("ft_check_and_replace_if_variables\n");
	t_token	*ptr;
	char	*str;
	int		i;
	int		j;
	t_var	*vptr;

	ptr = *tkn;
	vptr = var;
	while (ptr)
	{
		if (ptr->cmd[0] == '$')
		{
			ptr->cmd = change_dollar_for_money(ptr->cmd, var);
		}
		i = -1;
		while (ptr->args[++i])
		{
			//SCAN CHAR BY CHAR FOR $
		}
		// printf("eval %s:\n", ptr->cmd);
		ptr = ptr->next;
	}
}