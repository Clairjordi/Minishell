#include "../../includes/minishell.h"

void	ft_print_test(t_shell *shell)
{
	t_cmds	*tmp;
	int		i;

	tmp = shell->arg;
	while (tmp != NULL)
	{
		i = 0;
		ft_printf("~~~~~~value = %s~~~~~~~\n", tmp->value);
		while (tmp->value_split[i] != NULL)
		{
			ft_printf("value_split = %s\n", tmp->value_split[i]);
			i++;
		}
		ft_printf("--------\n");
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
