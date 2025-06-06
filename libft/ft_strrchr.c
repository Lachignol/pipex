/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascordil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 18:23:01 by ascordil          #+#    #+#             */
/*   Updated: 2025/01/14 12:47:24 by ascordil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *string, int searchedChar)
{
	int	i;

	i = 0;
	if ((char)searchedChar == '\0')
		return ((char *)&string[ft_strlen(string)]);
	i = ft_strlen(string) - 1;
	while (i >= 0)
	{	
		if (string[i] == (char)searchedChar)
			return ((char *)&string[i]);
		i--;
	}
	return (NULL);
}
