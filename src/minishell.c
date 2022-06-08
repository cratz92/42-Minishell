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
	//rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void init(int argc, char *argv[], char *envp[])
{
	char		*cmd_buff;
	(void)		argv;
	char		prompt[241];
	char		*preprompt;
	t_minishell	*shell;

	shell = malloc(sizeof(t_minishell));
	shell->var = NULL;
	shell->ec = 0;
	preprompt = get_preprompt();
	while (1)
	{
		// read stdin
		getcwd(prompt, 242);
		printf("%s", preprompt);
		cmd_buff = readline(ft_prompt(prompt));
		if (!cmd_buff)
		{
			printf("NOCMD\n");
			break;
		}
		add_history(cmd_buff); //this should probably be the first thing after readline ¿no? //IF cmd_buff NULL NOT READING
		shell->head = ft_evaluate_args_to_token(ft_cmd_to_args(cmd_buff)); 

		check_token_to_variables(&shell);

		ft_validations(&shell); //to discuss
		check_and_replace_if_variables(&shell->head, shell->var);

		// printf("CMDHEAD=%s\n", shell->head->cmd);
		/*printing to see whats happening- TOKENS ARE READY to be parsed */
		// printf("PRINTING\n\n");
		// if (shell->var != NULL)
			// print_var(shell->var);
		// print_tkn(shell->head); 

		if (!ft_strncmp(shell->head->cmd, "ppvv", 5)) //: print variable list for debuggin
			print_var(shell->var);	
		if (!ft_strncmp(shell->head->cmd, "exit", 5)) //: cmd_buff => shell->head->cmd
		{
			printf("BREAKEXIT\n"); //printf because sometimes does not break the while loop
			break;
		}
		else
			printf("%s ≠ exit", shell->head->cmd);

		// parse args
		parse_args(cmd_buff, envp);

		// command_execution(cmd_buff, envp);
		// if (argc == 3)
		// 	ft_pipe(cmd_buff, envp);
		// if (argc == 4)
		// 	redirection(cmd_buff, envp);

		// // execute parsed args

		// // stuff to do before exit
		free(cmd_buff);
		//free shell->head and all that...! TODO NEXT
	}
	//free preprompt
}

int main(int argc, char *argv[], char *envp[])
{
	struct termios term;

	if (argc != 1)
	{
		write(1, "plz initialize with ./minishell with no args\n", 45);
		return (ERROR_127);
	}

	// init signals to handle ctrl-c/-backstab/-d
	signal(SIGINT, handle_ctrlc);

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

	// main loop
	init(argc, argv, envp);

	// shutdown / cleanup

	return (SUCESS);
}


/*
IMPORTANT


*/
