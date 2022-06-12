#include "../include/minishell.h"

/* To detect a " when parsing
Goal is create t_args-> array of args */

void	ft_dquote(char **output, char c)
{
	char	*buff;
	bool	even_quotation;
	int		i;

	i = ft_strlen(*output);
	even_quotation = false; //flag: we have already 1 ", we need an even number of "
	buff = readline("dquote> ");
	add_history(buff);
	while (*buff)
	{
		if (*buff == c)
		{
			buff++;
			even_quotation = !even_quotation;
		}
		(*output)[i++] = *buff;
		buff++;
	}
	if (even_quotation == false)
		ft_dquote(output, c);
}

static void	ft_proceed_check_two(char **input, char *output, int *i)
{
	char	c;

	c = **input;
	(*input)++;
	while (**input != c && **input)
	{
		output[(*i)++] = **input;
		(*input)++;
	}
	if (**input == c)
		(*input)++;
	else 
	{
		ft_dquote(&output, c);
		*i = ft_strlen(output);
	}
}

static int	ft_proceed_check_one(char **input, char *output, int *i)
{
	if (**input == '>' || **input == '<' || **input == '|')
	{
		if (output[*i - 1] == 0) 
		{
			output[(*i)++] = **input;
			(*input)++;
			if (output[*i - 1] == **input)
			{
				output[(*i)++] = **input;
				(*input)++;
			}
		}
		return (1);
	}
	if (**input == ';')
	{
		if (output[*i - 1] == 0) 
		{
			output[(*i)++] = **input;
			(*input)++;
		}
		return (1);
	}
	return (0);
}

char	*ft_proceed(char **input)
{
	char	*output;
	int		i;

	output = malloc(sizeof(char) * ft_strlen(*input) + 1);
	i = 0;
	while (**input)
	{
		if (ft_proceed_check_one(input, output, &i))
			break;
		if (**input != '"' && **input != '\'')
			output[i++] = **input;
		else if (**input == '"' || **input == '\'')
		{
			ft_proceed_check_two(input, output, &i);
			if (**input == 32)
				break;
			else
				(*input)--;
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
	// print_targs(targ);
	// printf("--\n");
	return (targ);
}
