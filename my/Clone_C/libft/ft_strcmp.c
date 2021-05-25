/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ji-park <ji-park@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 18:11:50 by ji-park           #+#    #+#             */
/*   Updated: 2021/02/21 18:48:08 by ji-park          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int ft_strcmp(char *str1, char *str2)
{
    int i;

    i = 0;
    while (str1[i] != 0 || str2[i] != 0)
    {
        if (str1[i] > str2[i])
            return (0);
        else if (str1[i] < str2[i])
            return (0);
        i++;
    }
    return (1);
}