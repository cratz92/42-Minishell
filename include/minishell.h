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

#endif
