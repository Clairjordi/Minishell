/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 12:33:49 by clorcery          #+#    #+#             */
/*   Updated: 2022/10/21 19:05:03 by clorcery         ###   ########.fr       */
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
# include <fcntl.h>

# define TRUE 1
# define FALSE 0

typedef struct s_global
{
	int		status;
	char	*limiter;
	char	*line;
	int		is_in_heredoc;
	int		fd_hdoc;
	pid_t	pid;
}	t_global;

typedef struct s_lst_cmd
{
	char				*value;
	char				**value_split;
	int					idx_hdoc;
	int					hdoc;
	int					count_hdoc;
	struct s_lst_cmd	*prev;
	struct s_lst_cmd	*next;
}	t_cmds;

typedef struct s_exec
{
	char	**cmd;
	int		in;
	int		out;
	char	*cmd_path;
	int		pipe_fd[2];
	//pid_t	pid;
} t_exec;

typedef struct s_minishell
{
	t_exec	*exec;
	t_cmds	*arg;
	int		quote;
	int		dollar;
	int		pipe;
	char	*tmp;
	char	**path;
	char	**tab_cmd;
	char	**copy_envp;
	char	**copy_export;	
}	t_shell;

t_global g_g;
//A SUPPR ////////////////////////////////////////////////////////////////////////
void	ft_print_test(t_shell *shell);
//

//////INIT
void	ft_init_shell(t_shell *shell);
void	ft_init_exec(t_shell *shell);
void	ft_init_prompt(t_shell *shell, char **envp);
void	ft_init_struct(t_shell *shell);
void	ft_init_cmds(t_cmds *cmd);

//////PARSING
int		ft_verif_if_str(char *str);
void	ft_parsing(char *s, t_shell *shell, char **envp);
int		ft_verif_parsing(char *s);
/*list*/
void	ft_create_lst(t_shell *shell);
/*pipes*/
int		ft_verif_pipe(char *s);
int		ft_check_pipe(char *s);
/*quotes*/
int		ft_len_without_quote(char *str);
char	*ft_delete_quotes(char *str);
int		ft_count_quote(char *str);
void	ft_check_c(char **str, int *d, int *s, int *i);
int		ft_skip_quote(int *i, char **s);
/*redirect*/
int		ft_check_redirect(char *s);
int		ft_verif_redirect(char *s);
/*replace*/
char	*ft_rep(t_shell *shell, int i, int *j, t_cmds *lst);
void	ft_replace_value_split(t_shell *shell, int i, t_cmds *lst);
void	ft_replace_value(t_shell *shell);
/*replace_utils*/
int		ft_check_redir(char *s);
int		ft_open_quote(t_shell *shell, char c);
char	*ft_rep_quotes_space(t_shell *shell, int i, int *j, t_cmds *lst);
/*dollar*/
char	*ft_rep_if_dollar(t_shell *shell, int i, int *j, t_cmds *lst);
/*dollar_utils*/
int		ft_check_dollar(char *s, int i);

//////EXECUTE
/*minishell*/
void	ft_minishell(t_shell *shell, char **envp);
int 	ft_valid_redirect(char *s); //a deplacer dans un utils
int		ft_check_error_redirect(t_shell *shell); //a deplacer dans un utils
/*heredoc*/
void	ft_status_child(int wstatus);
void	ft_heredoc(t_shell *shell);
int		ft_fork_heredoc(t_shell *shell, int wstatus, t_cmds *lst);
void	ft_init_heredoc(t_shell *shell);
/*heredoc_utils*/
void	ft_get_idx_heredoc(t_cmds *lst);
void	ft_count_heredoc(t_shell *shell);
/*path*/
int		ft_check_path_cmd(char *path_cmd);
int		ft_get_path(t_shell *shell, char *path_cmd, char **envp);
void	ft_find_path(t_shell *shell, char **envp);

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
int		ft_size_lst(t_cmds *lst);
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
/*free*/
void	ft_free_shell(t_shell *shell);
void	ft_free_exec(t_shell *shell);
void	ft_free_cmds(t_shell *shell);
void	ft_free(t_shell *shell, char *s);
/*free_bis*/
void	*ft_free_ptr(void *ptr);
void	ft_free_malloc(t_shell *shell);

#endif
