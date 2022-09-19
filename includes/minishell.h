/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 12:33:49 by clorcery          #+#    #+#             */
/*   Updated: 2022/09/19 14:32:34 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "../libft/all_h.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <termios.h>
#include <curses.h>
#include <term.h>


typedef struct s_minishell
{
	char	**copy_envp;
	char	**copy_export;
	char	*test_add_env; // A SUPPR
}	t_shell;

//INIT
void	ft_init_shell(t_shell *shell);
void	init_prompt(void);

//UTILS
char	**ft_realloc_tab_char(t_shell *shell, char **old_tab, char *new_var);

//BUILTINS
void	ft_sort_export(t_shell *shell);
int		ft_len_va(char *var, int start, char c);
void	ft_create_copy_export(t_shell *shell);
void	ft_export(char **envp, t_shell *shell);
void	ft_recup_env(char **envp, t_shell *shell);
void	ft_add_envp(char **envp, t_shell *shell);
//SIGNALS
void	handler(int sig);

//FREE
void	ft_free_shell(t_shell *shell);
void	ft_free_malloc(t_shell *shell);

#endif
