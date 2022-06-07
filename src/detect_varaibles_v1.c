#include "../include/minishell.h"

/*
validate $var check var
if found var = var
if not var = "";
*/


void	check_var_exist(char **token, t_var *var)
{
	char	*str;

	str = *token;
	str++;
	printf("check_var_exist@%s \n", str);
	while (var)
	{
		printf("variable now is:%s\n", var->name);
		if (ft_strexact(str, var->name))
		{
			printf("FOUND %s is %s\n", str, var->name);
			str = ft_strdup(var->content); //str_dup double allocation fo memory
			**token = &str;
			printf("NOW=%s\n", str);
			return ;
		}
		var = var->next;
	}
	str = ft_strdup(""); //again str_dup? for str = "";
	**token = &str;
	printf("NOT FOUND@%s \n", str);
}


void	check_and_replace_if_variables(t_token **tkn, t_var *var)
{
	printf("ft_check_and_replace_if_variables\n");
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
			check_var_exist(&ptr->cmd, var);
			//check for variable
		}
		// i = -1;
		// while (ptr->args[++i] != 0)
		// {
		// 	j = -1;
		// 	while(ptr->args[i][++j])
		// 	{
		// 		if (ptr->args[i][j] == '$')
		// 			//check for variables
		// 	}
		// }
		printf("eval %s:\n", ptr->cmd);
		ptr = ptr->next;
	}
}