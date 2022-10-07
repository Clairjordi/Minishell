/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 12:33:49 by clorcery          #+#    #+#             */
/*   Updated: 2022/10/07 17:35:23 by mcloarec         ###   ########.fr       */
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

typedef struct s_lst_cmd
{
	char				**cmd;
	char				*value;
	char 				**value_split;
	int					infile;
	int					outfile;
	char				heredoc;
	char				dollar;
	int					pipe_fd[2];
	char				*cmd_path;
	struct s_lst_cmd	*prev;
	struct s_lst_cmd	*next;
}	t_cmds;

typedef struct s_minishell
{
	t_cmds	*arg;
	int		argc;
	int		quote;
	char	*tmp;
	char	**tab_cmd;
	char	**copy_envp;
	char	**copy_export;	
}	t_shell;

//A SUPPR ////////////////////////////////////////////////////////////////////////
void	ft_print_test(t_shell *shell);
//

//////INIT
void	ft_init_shell(t_shell *shell);
void	ft_init_prompt(t_shell *shell, char **envp);
void	ft_init_struct(t_shell *shell);
void	ft_init_cmds(t_cmds *cmd);

//////PARSING
void	ft_parsing(char *s, t_shell *shell, char **envp);
int		ft_verif_parsing(char *s, t_shell *shell);
/*list*/
void	ft_create_lst(t_shell *shell);
/*pipes*/
int		ft_verif_pipe(t_shell *shell, char *s);
int		ft_check_pipe(char *s);
/*quotes*/
int		ft_len_without_quote(char *str);
char	*ft_delete_quotes(char *str, t_shell *shell);
int		ft_count_quote(char *str);
void	ft_check_c(char **str, int *d, int *s, int *i);
int		ft_skip_quote(int *i, char **s);
/*redirect*/
int		ft_check_redirect(char *s);
int		ft_verif_redirect(char *s);
/*replace*/
int		ft_replace_value(t_shell *shell, char **envp);

//////BUILTINS
/*export*/
void	ft_sort_export(t_shell *shell);
void	ft_create_copy_export(t_shell *shell);
void	ft_export(char **envp, t_shell *shell);
void	ft_print_export(char **envp, t_shell *shell);
/*env*/
void	ft_recup_env(char **envp, t_shell *shell);
void	ft_add_envp(char **envp, t_shell *shell);
void	ft_print_envp(char **envp, t_shell *shell);

//////SIGNALS
void	handler(int sig);

//////UTILS
int		ft_len_va(char *var, int start, char c);
int		ft_sep(char c);
int		ft_check_q(char c);
/*realloc*/
char	**ft_realloc_tab_char(char **old_tab, char *new_var);
char	*ft_cdup(char c);
char	*ft_charjoin(char *s1, char c);
/*create_lst_cmds*/
t_cmds	*ft_lstnew_cmd(char *s, t_shell *shell);
void	ft_lstaddback_cmd(t_cmds **list, t_cmds *new_elem);
/*split_minishell*/
char	**ft_split_pipes(char *s, char c);
/*split_value*/
char	**ft_split_value(char *s, char c);

//////FREE
void	ft_free_shell(t_shell *shell);
void	ft_free_malloc(t_shell *shell);
void	ft_free_cmds(t_shell *shell);
void	ft_free(t_shell *shell, char *s);

#endif
