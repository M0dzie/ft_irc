/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <thmeyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 11:08:58 by thmeyer           #+#    #+#             */
/*   Updated: 2023/12/19 13:26:39 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_irc.hpp"

bool isPortValid(char *argv)
{
    for (int i = 0; argv[i]; i++)
        if (!std::isdigit(argv[i]))
            return (displayErrorMessage("Port must be a number."), false);
    return true;
}