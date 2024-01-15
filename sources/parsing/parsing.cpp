/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <thmeyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 11:08:58 by thmeyer           #+#    #+#             */
/*   Updated: 2024/01/15 12:28:20 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_irc.hpp"

bool isPortValid(char *argv) {
    for (int i = 0; argv[i]; i++)
        if (!std::isdigit(argv[i]))
            return (displayErrorMessage("Port must be a positive number."), false);
    if (std::atoi(argv) > 65535)
        return (displayErrorMessage("Port available : [0-65535]"), false);
    if (std::atoi(argv) < 1025) {
        std::cerr << YELLOW << "Warning: " << RESET << "This port might be reserved to a root access." << std::endl;
        return (true);
    }
    return true;
}