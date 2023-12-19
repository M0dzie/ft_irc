/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <thmeyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 11:08:58 by thmeyer           #+#    #+#             */
/*   Updated: 2023/12/19 13:11:22 by thmeyer          ###   ########.fr       */
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

bool isPasswordValid(char *argv)
{
    if (!argv[0])
        return (displayErrorMessage("Empty password are not authorized."), false);
    for (int i = 0; argv[i]; i++)
        if (std::isspace(argv[i]))
            return (displayErrorMessage("Space in password are not authorized."), false);
    return true;
}