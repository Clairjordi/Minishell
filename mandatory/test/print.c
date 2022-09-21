#include "../../includes/minishell.h"

void	ft_print_test(t_shell *shell, t_cmds **cmds)
{
	t_cmds	*tmp;
	(void) 	*shell;

	tmp = *cmds;
	while (tmp != NULL)
	{
		ft_printf("valeur = %s\n", tmp->cmd);
		tmp = tmp->next;
	}
}


/* char *test_add_env; */
/* test_add_env = argv[1]; */
/* if (shell.test_add_env != NULL) */
/* 	ft_add_envp(envp, &shell); */
/* ft_print_envp(envp, &shell); */
/* ft_printf("-----------------------------------\n"); */
/* ft_print_export(envp, &shell); */
