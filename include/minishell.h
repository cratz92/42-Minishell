/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-l <cbrito-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 17:59:01 by cbrito-l          #+#    #+#             */
/*   Updated: 2022/03/20 17:59:01 by cbrito-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft.h"
#include <termios.h>
#include <errno.h>

#define SUCESS 0

// error codes

#define ERROR_127 127
// structs => We need a Command Table
typedef struct t_token;
typedef struct	s_args
{
	//bool	pipes;
	int nbr_pipes;
	//bool	endline;
	int	nbr_endline;
	char **args;
}				t_args;
/* so first we read the args(input from readline)
then split into args, fill out pipes endline ect.
and then create tokens
*/

typedef struct	s_token
{
	char	*cmd;
	char	**args;
	struct t_token	*next;
}				t_token;
/*tokens have cmd, and args (optional)
next is pointing to next for link list
*/

typedef struct 	s_minishell
{
	t_token		*head; //pointing to the first token
}				t_minishell;

// ********** PROTOTYPES  ***********
// minishell.c
int main(int argc, char *argv[], char *envp[]);
void handle_ctrlc(int sig);
void init(int argc, char *argv[], char *envp[]);

// execution.c
void command_execution(char **cmd,char *envp[]);
char *check_path(char *cmd, char *envp[]);

// parsing.c
void *parse_args(char *str, char *envp[]);

// pipe.c
int ft_pipe(char **cmd, char **envp);

// redirection_output
int redirection(char **cmd, char **envp);

//prompt.c
char *ft_prompt(char *str);

//detective
t_args *ft_cmd_to_args(char *str);


//newutils.c
char  *ft_strldup(char *str, int l);
char  *ft_strfdup(char **str, int f);

void  print_targs(t_args *a);

#endif
