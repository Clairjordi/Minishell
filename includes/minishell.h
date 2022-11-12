/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 12:33:49 by clorcery          #+#    #+#             */
/*   Updated: 2022/11/12 10:21:21 by mcloarec         ###   ########.fr       */
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
# include <sys/stat.h>

# define TRUE 1
# define FALSE 0
# define ERROR -1

typedef struct s_global
{
	int		status;
	char	*limiter;
	char	*line;
	int		is_in_loop;
	int		fd_hdoc;
}	t_global;

typedef struct s_lst_cmd
{
	char				*value;
	char				**value_split;
	int					idx_hdoc;
	int					hdoc;
	int					count_hdoc;
	int					pipe_fd[2];
	int					cmd_found;
	struct s_lst_cmd	*prev;
	struct s_lst_cmd	*next;
}	t_cmds;

typedef struct s_exec
{
	char	**cmd;
	int		infile;
	int		outfile;
	char	*cmd_path;
	char	**builtins;
	int		is_dir;
	pid_t	pid;
}	t_exec;

typedef struct s_builtins
{
	char	**env;
}	t_built;

typedef struct s_envcpy
{
	char			*name;
	char			*value;
	char			*var;
	struct s_envcpy	*prev;
	struct s_envcpy	*next;
}	t_envcpy;

typedef struct s_env
{
	struct s_envcpy	*first;
	struct s_envcpy	*last;
}	t_env;

typedef struct s_minishell
{
	t_built	*built;
	t_exec	*exec;
	t_cmds	*arg;
	t_env	*env;
	pid_t	pid_hdoc;
	int		quote;
	int		dollar;
	int		pipe;
	char	**tab_pid;
	char	*tmp;
	char	**path;
	char	**tab_cmd;
}	t_shell;

extern t_global	g_g;

//A SUPPR ////////////////////////////////////////////////////////////////////////
void		ft_print_test(t_shell *shell);

//////INIT
void		ft_init_shell(t_shell *shell);
void		ft_init_exec(t_shell *shell);
void		ft_init_prompt(t_shell *shell);
void		ft_init_cmds(t_cmds *cmd);
/*init_bis*/
void		ft_init_built(t_shell *shell);
void		ft_init_envcpy(t_shell *shell);

//////PARSING
int			ft_verif_if_str(char *str);
void		ft_parsing(char *s, t_shell *shell);
int			ft_verif_parsing(char *s);
/*list*/	
void		ft_create_lst(t_shell *shell);
/*pipes*/
int			ft_verif_pipe(char *s);
int			ft_check_pipe(char *s);
int			ft_check_space_pipe(t_shell *shell);
/*quotes*/
char		*ft_delete_quotes_redirect(t_shell *shell, char *s);
int			ft_count_quote(char *str);
void		ft_check_c(char **str, int *d, int *s, int *i);
int			ft_skip_quote(int *i, char **s);
/*redirect*/
int			ft_is_not_redirection(char *s);
int			ft_check_redirect(char *s);
int			ft_verif_redirect(char *s);
/*replace*/
char		*ft_rep(t_shell *shell, int i, int *j, t_cmds *lst);
void		ft_replace_value_split(t_shell *shell, int i, t_cmds *lst);
void		ft_replace_value(t_shell *shell);
/*replace_utils*/
int			ft_check_redir(char *s);
int			ft_open_quote(t_shell *shell, char c);
char		*ft_rep_quotes_space(t_shell *shell, int i, int *j, t_cmds *lst);
/*dollar*/
char		*ft_rep_if_dollar(t_shell *shell, int i, int *j, t_cmds *lst);
/*dollar_utils*/
int			ft_check_dollar(char *s, int i);
char    	*ft_getenv(t_shell *shell, char *name);

//////EXECUTE
/*minishell*/
int			ft_execute_cmd(t_shell *shell, int wstatus);
void		ft_execute_pipe(t_shell *shell, t_exec *exec, t_cmds *lst);
void		ft_exec_builtins(t_shell *shell);
void		ft_check_execute(t_shell *shell);
void		ft_minishell(t_shell *shell);
/*check_sort*/
int			ft_valid_redirect(char *s);
int			ft_check_error_redirect(t_shell *shell);
int			ft_check_infile(t_exec *exec, char **tab, int i);
int			ft_check_outfile(t_shell *shell, char **tab, int i);
int			ft_check_first(t_shell *shell, char *s);
/*child*/
void		ft_child_cmd(t_shell *shell, t_exec *exec);
void		ft_first_child(t_exec *exec, t_cmds *lst);
void		ft_last_child(t_exec *exec, t_cmds *lst);
void		ft_else_child(t_exec *exec, t_cmds *lst);
void		ft_check_child_execute(t_shell *shell, t_cmds *lst);
/*cmd*/
void		ft_add_opt_arg(t_shell *shell, char **tab, int i);
int			ft_add_cmd(t_shell *shell, char *s);
int			ft_check_point(t_shell *shell, char **tab, int i);
int			ft_check_cmd(t_shell *shell, char **tab, int i);
/*builtins*/
void		ft_add_opt_arg_builtins(t_shell *shell, char **tab, int i);
void		ft_add_builtins(t_shell *shell, char *cmd_built);
void		ft_create_builtins_tab(t_shell *shell, char **tab, int *i);
/*builtins_utils.c*/
int			ft_check_is_builtins(t_shell *shell, char **tab, int *i);
int			ft_check_builtins_without_fork(t_shell *shell);
/*sort*/	
void		ft_sort_cmd(t_shell *shell, t_cmds *lst);
void		ft_sort_cmd_pipe(t_shell *shell, t_cmds *lst);
/*sort_utils*/
int			ft_check_shell_pipe(t_shell *shell, t_cmds *lst);
void		ft_waitpid_pipe(t_shell *shell);
void		ft_add_pid(t_shell *shell);
/*sort_utils_bis*/
int			ft_is_a_path(char *str);
int			ft_is_directory(char *str);
/*heredoc*/
void		ft_heredoc(t_shell *shell);
int			ft_fork_heredoc(t_shell *shell, int wstatus, t_cmds *lst);
int			ft_init_heredoc(t_shell *shell);
/*heredoc_utils*/
void		ft_get_idx_heredoc(t_cmds *lst);
void		ft_count_heredoc(t_shell *shell);
/*path*/	
void		ft_get_path_bis(t_shell *shell, char *path_test);
char		*ft_check_path(t_shell *shell, char *path_tmp, char *cmd, int i);
char		*ft_get_path(t_shell *shell, char *path_cmd);
/*path_utils*/
int			ft_check_access(t_shell *shell, char *path_cmd);
int			ft_check_path_cmd(char *path_cmd);
void		ft_find_path(t_shell *shell);

//////BUILTINS
/*getenv*/
char		*ft_get_name(char *name_env);
char		*ft_get_value(char *value_env);
t_envcpy	*ft_new_elem_env(char *str);
void		ft_create_lst_env(t_shell *shell, char **envp);
/*pwd*/
void		ft_pwd(void);
/*export*/
void		ft_export(t_shell *shell);
/*exit*/
int			ft_exit(t_shell *shell, char *str);
void		ft_exit_fork(char **built);
/*env*/
void		ft_recup_env(t_shell *shell);
void		ft_print_env(t_shell *shell);
/*echo*/
void		ft_echo(char **tab);
int			ft_size_tab(char **tab);
/*cd*/
void		ft_cd(char **tab);
/*unset*/
int			ft_check_valid_name(char *s);
void		ft_unset(t_shell *shell);
t_envcpy	*ft_check_name_envcpy(t_shell *shell, char *s);

//////SIGNALS
void		handler(int sig);
void		ft_status_child(int wstatus);

//////UTILS 
int			ft_size_lst(t_cmds *lst);
int			ft_len_va(char *var, int start, char c);
int			ft_sep(char c);
int			ft_check_q(char c);
void		ft_close_std(void);
/*realloc*/
char		**ft_realloc_tab_char(char **old_tab, char *new_var);
char		*ft_cdup(char c);
char		*ft_charjoin(char *s1, char c);
/*create_lst_cmds*/
t_cmds		*ft_lstnew_cmd(char *s, t_shell *shell);
void		ft_lstaddback_cmd(t_cmds **list, t_cmds *new_elem);
/*split_minishell*/
char		**ft_split_pipes(char *s, char c);
/*split_value*/
char		**ft_split_value(char *s, char c);

//////FREE
/*free*/
void		ft_free(t_shell *shell, char *s);
void		ft_free_exec(t_shell *shell);
void		ft_free_cmds(t_shell *shell);
void		ft_free_shell(t_shell *shell);
/*free_bis*/
void		*ft_free_ptr(void *ptr);
void		ft_free_malloc(t_shell *shell);
void		ft_free_close_pipe(t_shell *shell, t_cmds *lst);
void		ft_free_close(t_shell *shell);
/*free_exit*/
void		ft_free_built(t_shell *shell);
void		ft_free_envcpy(t_shell *shell);
void		ft_free_child(t_shell *shell);
#endif
