/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 12:43:25 by clorcery          #+#    #+#             */
/*   Updated: 2022/09/07 17:57:03 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	init_prompt(void)
{
	char	*str;

	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		str = readline ("$>");
		if (!str || !ft_strncmp("exit", str, 4))
		{
			ft_putstr_fd("exit\n", 1);
			exit (0);
		}
		if (str)
			add_history(str);
		free(str);
	}
}
int init_term()
{
    int ret;
    char *term_type = getenv("TERM");

    if (term_type == NULL)
    {
        fprintf(stderr, "TERM must be set (see 'env').\n");
        return -1;
    }

    ret = tgetent(NULL, term_type);

    if (ret == -1)
    {
        fprintf(stderr, "Could not access to the termcap database..\n");
        return -1;
    }
    else if (ret == 0)
    {
        fprintf(stderr, "Terminal type '%s' is not defined in termcap database (or have too few informations).\n", term_type);
        return -1;
    }

    return 0;
}
int	main(void)
{
	/* t_shell	shell; */
    /*  */
	/* init_prompt(&shell); */
	//init_prompt();
	int column_count; 
	int ret = init_term();
	if (ret == 0)
    {
		column_count = tgetnum("li");
    }
	printf("%d\n", column_count);
	return (ret);
}
