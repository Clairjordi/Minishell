/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 12:33:49 by clorcery          #+#    #+#             */
/*   Updated: 2022/09/21 19:16:48 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/all_h.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>

# include <termios.h>
# include <curses.h>
# include <term.h>

typedef struct s_lst_cmd
{
	char				*cmd;
	char				*opt;
	int					infile;
	int					outfile;
	char				heredoc;
	char				dollar;
	int					pipe;
	struct s_lst_cmd	*prev;
	struct s_lst_cmd	*next;
}	t_cmds;

typedef struct s_minishell
{
	char	**copy_envp;
	char	**copy_export;	
}	t_shell;

//A SUPPR ////////////////////////////////////////////////////////////////////////
void	ft_print_test(t_shell *shell, t_cmds **cmds);
//

//INIT
void	ft_init_shell(t_shell *shell, t_cmds *cmds);
void	ft_init_prompt(t_shell *shell, t_cmds *cmds);

//PARSING
void	ft_parsing(char *s, t_shell *shell, t_cmds *cmds);

//BUILTINS
void	ft_sort_export(t_shell *shell);
void	ft_create_copy_export(t_shell *shell);
void	ft_export(char **envp, t_shell *shell);
void	ft_recup_env(char **envp, t_shell *shell);
void	ft_add_envp(char **envp, t_shell *shell);

//SIGNALS
void	handler(int sig);

//UTILS
char	**ft_realloc_tab_char(t_shell *shell, char **old_tab, char *new_var);
int		ft_len_va(char *var, int start, char c);
t_cmds	*ft_lstnew_cmd(char *s);
void	ft_lstaddback_cmd(t_cmds **list, t_cmds *new_elem);
char	**ft_split_shell(char const *s, char c);

//FREE
void	ft_free_shell(t_shell *shell);
void	ft_free_cmds(t_cmds *shell);
void	ft_free_malloc(t_shell *shell);
void	ft_free_cmds(t_cmds *cmds);
void	ft_free_error(t_shell *shell, t_cmds *cmds, char *s);

#endif
