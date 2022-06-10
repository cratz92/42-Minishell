/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-l <cbrito-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 17:59:10 by cbrito-l          #+#    #+#             */
/*   Updated: 2022/03/20 17:59:10 by cbrito-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void handle_ctrlc(int sig)
{
	(void)sig;

	write(1, "\n", 2);
	// rl_replace_line("", 0); this is commented because if not it gives error
	rl_on_new_line();
	rl_redisplay();
}

void init(t_minishell **shell)
{
	char		*cmd_buff;
	char		prompt[241];
	char		*preprompt;

	preprompt = get_preprompt();
	cmd_buff = NULL;
	while (1)
	{
		// read stdin
		getcwd(prompt, 242);
		printf("%s", preprompt);
		cmd_buff = readline(ft_prompt(prompt));

		if (!cmd_buff)
		{
			printf("NOCMD\n"); //segfault- because doesnt read !cmd_buff
			break ;
		}
		add_history(cmd_buff);
		(*shell)->head = ft_evaluate_args_to_token(ft_cmd_to_args(cmd_buff)); 
		check_token_to_variables(shell);
		check_and_replace_if_variables(shell);

		ft_validations(shell); //to discuss

		/*printing to see whats happening- TOKENS ARE READY to be parsed */
		// printf("PRINTING\n\n");
		// if ((*shell)->var != NULL)
		// 	print_var((*shell)->var);
		// print_tkn((*shell)->head);

		if (!ft_strncmp((*shell)->head->cmd, "ppvv", 5)) //: print variable list for debuggin
		{
			if ((*shell)->var)
				print_var((*shell)->var);
			else
				printf("variable list empty\n");	
		}
		if (!ft_strncmp((*shell)->head->cmd, "exit", 5)) //: cmd_buff => shell->head->cmd
		{
			printf("BREAKEXIT\n");
			free_str(cmd_buff);
			//more to do here, different args with exit.
			break ;
		}
		else
			printf("%s ≠ exit", (*shell)->head->cmd);

		// parse args
		// parse_args(cmd_buff, envp);

		// command_execution(cmd_buff, envp);
		// if (argc == 3)
		// 	ft_pipe(cmd_buff, envp);
		// if (argc == 4)
		// 	redirection(cmd_buff, envp);

		// execute parsed args



		//free and restart loop
		free_str(cmd_buff);
		if ((*shell)->head)
			free_tokens(&(*shell)->head);
	}
	free_str(preprompt);
}

void	init_shell(t_minishell **shell, char **envp)
{
	(*shell) = malloc(sizeof(t_minishell));
	(*shell)->var = NULL;
	(*shell)->env = init_parse_env(envp);
	(*shell)->ec = 0;
}

int main(int argc, char *argv[], char *envp[])
{
	struct termios	term;
	t_minishell		*shell;

	if (argc != 1)
	{
		write(1, "plz initialize with ./minishell with no args\n", 45);
		return (ERROR_127);
	}
	signal(SIGINT, handle_ctrlc); // init signals to handle ctrl-c/-backstab/-d
	if (tcgetattr(STDIN_FILENO, &term) != 0)
	{
		perror("tcgetattr() error");
		exit(errno);
	}
	else
	{
		term.c_lflag &= ~(ECHOCTL);
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
	}
	init_shell(&shell, envp);
	init(&shell);
	return (free_minishell(&shell));
}


/*
IMPORTANT


*/
