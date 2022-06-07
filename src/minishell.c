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

void	ft_validations(t_minishell **shell)
{
	/* sudo code
	1. check if CMD exist
	2. ARGS ...
	3. if not- return exit code
	4. What else?
	*/
}

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
			break;
		shell->head = ft_evaluate_args_to_token(ft_cmd_to_args(cmd_buff)); 
		check_token_to_variables(&shell);
		//TOKENS ARE READY to be parsed

		/*printing to see whats happening UNDO // */
		if (shell->var != NULL)
			print_var(shell->var);
		print_tkn(shell->head); 
		
		ft_validations(&shell);
		if (!ft_strncmp(cmd_buff, "exit", 5)) //: cmd_buff => shell->head->cmd
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
