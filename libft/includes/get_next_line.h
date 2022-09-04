/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorcery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 14:12:35 by clorcery          #+#    #+#             */
/*   Updated: 2022/04/19 11:56:25 by clorcery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*ft_strjoin_gnl(char const *s1, char const *s2);
char	*get_next_line(int fd);
int		find_bsn(char *buf);
char	*read_fd(char *buf, int file_d);
char	*recup_line(char *buf);
char	*new_buffer(char *old_buf);

#endif
