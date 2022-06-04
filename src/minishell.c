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
	char	*cmd_buff;
	char	*cmd;
	(void)	argv;
	char	prompt[241];
	t_args	*arg; //to replace the *cmd
	t_minishell	*shell;

	cmd = NULL;
	shell = malloc(sizeof(t_minishell));
	while (1)
	{
		// read stdin
		getcwd(prompt, 242);
		cmd_buff = readline(ft_prompt(prompt));

		if (!cmd_buff)
			break;
		
		//cmd_buf to t_args
		arg = ft_cmd_to_args(cmd_buff);
		shell->head = ft_evaluate_args_to_token(arg); 
		check_token_to_variables(&shell); //if (helloworld=world) make it var not a token;
		// if (shell->var)
		// 	print_var(shell->var);
		// print_tkn(shell->head); //TOKENS ARE READY to parse

		if (!ft_strncmp(cmd_buff, "exit", 5))
			break;

		add_history(cmd_buff);

		// parse args
		parse_args(cmd_buff, envp);

		// command_execution(cmd_buff, envp);
		// if (argc == 3)
		// 	ft_pipe(cmd_buff, envp);
		// if (argc == 4)
		// 	redirection(cmd_buff, envp);

		// execute parsed args

		// stuff to do before exit
		free(cmd_buff);
	}
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
