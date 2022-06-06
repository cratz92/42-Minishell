#include "../include/minishell.h"

/* To detect a " when parsing
Goal is create t_args-> array of args */

void	ft_dquote(char **output)
{
	char	*buff;
	bool	even_quotation;
	int		i;

	i = ft_strlen(*output);
	even_quotation = false; //flag: we have already 1 ", we need an even number of "
	buff = readline("dquote> ");
	while (*buff)
	{
		if (*buff == '"')
		{
			buff++;
			even_quotation = !even_quotation;
		}
		(*output)[i++] = *buff;
		buff++;
	}
	if (even_quotation == false)
		ft_dquote(output);
}

char	*ft_proceed(char **input)
{
	char	*output;
	int		i;
	bool	f;

	output = malloc(sizeof(char) * ft_strlen(*input) + 1); //Later need to remalloc if want to make it perfect
	i = 0;
	while (**input)
	{
		//if (> < |) ... << >>
		if (**input == '>' || **input == '<' || **input == '|') // ... >> <<
		{
			if (output[i - 1] == 0) 
			{
				output[i++] = **input;
				(*input)++;
				if (output[i - 1] == **input)
				{
					output[i++] = **input;
					(*input)++;
				}
				break;
			}
			else
				break;
		}
		if (**input != '"')
			output[i++] = **input;
		else if (**input == '"') //&& **input - 1 != '´' BREAK CASE
		{
			(*input)++;
			while (**input != '"' && **input) //+ BREAK CASE
			{
				output[i++] = **input;
				(*input)++;
			}
			if (**input == '"')
				(*input)++;
			else 
			{
				ft_dquote(&output);
				i = ft_strlen(output);
			}
			if (**input == 32)
				break;
		}
		(*input)++;
		if (**input == 32)
			break;
	}
	output[i] = 0;
	return (output);
}

void	init_targs(t_args **arg)
{
	(*arg) = malloc(sizeof(t_args));
	(*arg)->nbr_pipes = 0;
	(*arg)->nbr_endline = 0;
	(*arg)->args = NULL;
}

t_args	*ft_cmd_to_args(char *str)
{
	t_args	*targ;
	int		i;
	char	**cpy;

	init_targs(&targ);
	targ->args = malloc(sizeof(char) * 1000); //this can improve
	i = 0;
	while (*str)
	{
		while (*str == 32)
			str++;
		targ->args[i] = malloc(sizeof(char) * ft_strlen(str));
		targ->args[i++] = ft_proceed(&str);
	}
	return (targ);
}
