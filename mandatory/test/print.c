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

void	ft_print_envcpy(t_shell *shell)
{
	t_envcpy	*tmp;

	tmp = shell->env->first;
	while (tmp != NULL)
	{
		ft_printf("~~~~~~name = %s~~~~~~~\n", tmp->name);
		ft_printf("value = %s\n", tmp->value);
		ft_printf("--------\n");
		tmp = tmp->next;
	}
	/* ft_printf("~~~~~~name = %s~~~~~~~\n", shell->env->first->name); */
	/* ft_printf("~~~~~~value = %s~~~~~~~\n", shell->env->first->value); */
	/* ft_printf("~~~~~~name = %s~~~~~~~\n", shell->env->last->name); */
	/* ft_printf("~~~~~~value = %s~~~~~~~\n", shell->env->last->value); */
}
