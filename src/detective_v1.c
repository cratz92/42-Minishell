#include "../include/minishell.h"

/* To detect a " when parsing
Goal is create t_args-> array of args */

void	ft_dquote(char **output, int i)
{
	char	*buff;
	int		c;

	c = 0;
	buff = readline("dquote> ");
	while (*buff)
	{
		if (*buff == '"')
		{
			buff++;
			c++;
		}
		(*output)[i++] = *buff;
		buff++;
	}
	if (c % 2 == 1) //MY MATH needs work
	{
		// ft_dquote(output, i);
	}
}


char	*ft_proceed(char **input)
{
	char	*output;
	int		i;

	output = malloc(sizeof(char) * ft_strlen(*input) + 1); //Later need to remalloc if want to make it perfect
	i = 0;
	while (**input)
	{
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
				ft_dquote(&output, i);
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




/* main
-count quotes if > 0
-if %2 != 0 -> ft_dquote
-if
*/

void	init_targs(t_args **arg)
{
	(*arg) = malloc(sizeof(t_args));
	(*arg)->nbr_pipes = 0;
	(*arg)->nbr_endline = 0;
	(*arg)->args = NULL; //?maybe this is meaninless - NULL
}

t_args	*ft_cmd_to_args(char *str)
{
	t_args	*targ;
	int		i;
	char	*cpy;

	
	printf("WE ARE Here\n");
	printf("%s |\n", str);
	init_targs(&targ);
	// printf("targ: %d, \n", targ->nbr_pipes);
	i = 0;
	while (*str)
	{
		while (*str == 32)
			str++;
		printf("%s -\n", ft_proceed(&str));
    	// printf("cpied|%s| -> |%s|\n", cpy, str);
	}

	// print_targs(targ);
	// printf("we found %d |\n", bk);
	// if (ft_scan_for_quotes(str) == 0)
		//duplicate arg
	// else
	return (targ);
}


/* EXAMPLES TO MIND
✗ echo terminal"love"
terminallove
✗ echo terminal"this is a love"
terminalthis is a love
*/