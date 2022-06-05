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

#include <stdbool.h>
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

typedef enum	s_type
{
	IS_PIPE,
	IS_RDR, //riderection
	IS_CMD, //command
	IS_VAR, //variable
}				t_type;


typedef struct	s_var
{
	char			*name;
	char			*content;
	struct s_var	*next;
}				t_var;
/* local variables when myname=name 
are stored as a variable, outputed as $myname
*/

typedef struct	s_args
{
	int		nbr_pipes; //bool	pipes;
	int		nbr_endline; //bool	endline;
	char	**args;
}				t_args;
/* so first we read the args(input from readline)
then split into args, fill out pipes endline ect.
and then create tokens or local variable
*/

typedef struct	s_token
{
	char	*cmd;
	char	**args;
	t_type	en;
	struct s_token	*next;
	struct s_token	*prev;
}				t_token;
/*tokens have cmd, and args (optional)
next is pointing to next for link list
*/


typedef struct 	s_minishell
{
	t_token		*head; //pointing to the first token
	t_var		*var;
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
int redirection_out(char **cmd, char **envp);
int ft_append(char **cmd, char **envp);

//prompt.c
char *ft_prompt(char *str);

//detective
t_args *ft_cmd_to_args(char *str);


//newutils.c
char	*ft_strldup(char *str, int l);
char	*ft_strfdup(char **str, int f);
bool 	ft_strlook(char *str, char *look);
bool	ft_strexact(char *s1, char *s2);
bool	ft_strexact_abs(char *s1, char *s2);

void 	print_targs(t_args *a);
void 	print_tkn(t_token *t);
void  	print_var(t_var *v);


// temporary files
// redirect_input_v1.c
int redirection_in(char **cmd, char **envp);
int ft_heredoc(char **cmd, char **envp);

//enum
t_token *ft_evaluate_args_to_token(t_args *a);


//variables
void	check_token_to_variables(t_minishell **shell);

#endif
