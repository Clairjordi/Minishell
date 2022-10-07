char	*ft_rep_quotes_space(char *c, t_shell *shell)/*, int i, int j, t_cmds *lst) */
{
	char	*space;

	space = NULL;
	if (ft_sep(*c) == 2
			&& ft_sep(c[1]) == 2
			&& c[2] == '\0')
		space = ft_charjoin(shell->tmp, ' ');
	else if (ft_sep(*c) == 4
			&& ft_sep(c[1]) == 4
			&& c[2] == '\0')
		space = ft_charjoin(shell->tmp, ' ');
	return (space);
}

char	*ft_rep(char *c, t_shell *shell, int *j)/* t_shell *shell, int i, int *j, t_cmds *lst) */
{
	char	*new;

	if (ft_check_q(*c) == 1)
	{
		new = ft_rep_quotes_space(c, shell);
		if (new)
		{
			(*j)++;
			//shell->quote = 0;
			return (new);
		}
	}
	new = shell->tmp;
	shell->quote = ft_open_quote(shell, *c);
	if (!(*c == '\'' && shell->quote != 2)
			&& !(*c == '\"' && shell->quote != 1))
	{
		new = ft_charjoin(shell->tmp, *c);
		if (!new)
		{
			free(new);
			ft_free_malloc(shell);
		}
	}
	else
		return (shell->tmp);
	return (new);
}

int	ft_replace_value_split(t_shell *shell, int i, t_cmds *lst)
{
	if (shell->tmp != NULL)
	{
		lst->value_split[i] = ft_free_ptr(lst->value_split[i]);
		lst->value_split[i] = shell->tmp;
	}
	else
		return (-1);
	return (0);
}

int		ft_check_dollar(char c)
{
	if (c == '$')
		return (1);
	return (0);
}
/*  */
/* char	*ft_rep_if_dollar(t_shell *shell, char **envp, int i, int j, t_cmds *lst) */
/* {} */

int	ft_replace_value(t_shell *shell, char **envp)
{
	//int		dollar;
	int		i;
	int		j;
	(void)envp;
	t_cmds	*lst;

	lst = shell->arg;
	while (lst != NULL)
	{
		i = 0;
		while (lst->value_split[i] != NULL)
		{
			shell->tmp = NULL;
			j = 0;
			while (lst->value_split[i][j])
			{
				/* dollar = ft_check_dollar(lst->value[i]); */
				/* if (dollar == 1) */
				/* 	shell->tmp = ft_rep_if_dollar(shell, envp, i, j, lst); */
				/* else */
					shell->tmp = ft_rep(&lst->value_split[i][j], shell, &j/*, i, &j, lst*/);
				j++;
			}
			if (ft_replace_value_split(shell, i, lst) == -1)
				return (-1);
			i++;
		}
		lst = lst->next;
	}
	return (0);
}
