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



void	safe_exit(t_minishell **shell, char *buff)
{
	if (buff)
		free_str(buff);
	if ((*shell))
		free_minishell(shell);
}

void handle_ctrlc(int sig)
{
	(void)sig;

	write(1, "\n", 2);
	// rl_replace_line("", 0); this is commented because if not it gives error
	rl_on_new_line();
	rl_redisplay();
}

int init(int argc, char *argv[], char *envp[])
{
	char		*cmd_buff;
	(void)		argv;
	char		prompt[241];
	char		*preprompt;
	t_minishell	*shell;
	int			ec; //exitcode- need to return

	shell = malloc(sizeof(t_minishell));
	shell->var = NULL;
	shell->env = init_parse_env(envp);
	print_var(shell->env);

	shell->ec = 0;
	ec = shell->ec; //Working on now
	preprompt = get_preprompt();
	while (1)
	{
		// read stdin
		getcwd(prompt, 242);
		printf("%s", preprompt);
		cmd_buff = readline(ft_prompt(prompt));

		if (!cmd_buff)
		{
			printf("NOCMD\n"); //segfault- because doesnt no read !cmd_buff
			break ;
		}

		add_history(cmd_buff); //this should probably be the first thing after readline ¿no? //IF cmd_buff NULL NOT READING
		shell->head = ft_evaluate_args_to_token(ft_cmd_to_args(cmd_buff)); 
		check_token_to_variables(&shell);

		ft_validations(&shell); //to discuss
		check_and_replace_if_variables(&shell);

		// printf("CMDHEAD=%s\n", shell->head->cmd);
		/*printing to see whats happening- TOKENS ARE READY to be parsed */
		// printf("PRINTING\n\n");
		// if (shell->var != NULL)
		// 	print_var(shell->var);
		// print_tkn(shell->head);

		if (!ft_strncmp(shell->head->cmd, "ppvv", 5)) //: print variable list for debuggin
		{
			if (shell->var)
				print_var(shell->var);
			else
				printf("variable list empty\n");	
		}
		if (!ft_strncmp(shell->head->cmd, "exit", 5)) //: cmd_buff => shell->head->cmd
		{
			printf("BREAKEXIT\n"); //printf because sometimes does not break the while loop
			free_str(cmd_buff);
			break ; //go to ft_exit_cmd
		}
		else
			printf("%s ≠ exit", shell->head->cmd);

		// parse args
		// parse_args(cmd_buff, envp);

		// command_execution(cmd_buff, envp);
		// if (argc == 3)
		// 	ft_pipe(cmd_buff, envp);
		// if (argc == 4)
		// 	redirection(cmd_buff, envp);

		// execute parsed args

		free_str(cmd_buff);
		if (shell->head)
			free_tokens(&shell->head);
	}
	if (shell->var)
		free_variables(&shell->var);
	free_str(preprompt);
	free_minishell(&shell);
	return (ec); //maybe return shell instead and free from main?
}

int main(int argc, char *argv[], char *envp[])
{
	struct termios	term;
	int				ec;
	
	ec = 0; //initialize- working on exitcode now
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
	ec = init(argc, argv, envp);

	// shutdown / cleanup

	return (ec);
}


/*
IMPORTANT


*/
