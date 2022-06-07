

// //if $var change to var->content if not, ""
// void	change_dollar_for_money(char *str, t_var *var)
// {
// 	int		i;
// 	int		j;
// 	char	*new;

// 	i = 0;
// 	new = malloc(sizeof(char) * ft_strlen(str));
// 	while (str)
// 	{
// 		j = ft_strlen(new);
// 		while (*str != '$' && *str != 0)
// 			new[j++] = (*str)++;
// 		if (*str == '$')
// 		{
// 			str++;
// 			new = ft_strjoin(new, var_for_content(&str, var));
// 		}
// 		if (*str == NULL)
// 			break;
// 	}
// 	printf("OK NEW = %s\n", new);
// }




// void	check_var_exist(char **token, t_var *var)
// {
// 	char	*str;

// 	str = *token;
// 	str++;
// 	printf("check_var_exist@%s \n", str);
// 	while (var)
// 	{
// 		printf("variable now is:%s\n", var->name);
// 		if (ft_strexact(str, var->name))
// 		{
// 			printf("FOUND %s is %s\n", str, var->name);
// 			str = ft_strdup(var->content); //str_dup double allocation fo memory
// 			**token = &str;
// 			printf("NOW=%s\n", str);
// 			return ;
// 		}
// 		var = var->next;
// 	}
// 	str = ft_strdup(""); //again str_dup? for str = "";
// 	**token = &str;
// 	printf("NOT FOUND@%s \n", str);
// }
