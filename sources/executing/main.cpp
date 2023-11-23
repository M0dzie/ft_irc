/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <thmeyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 10:17:37 by thmeyer           #+#    #+#             */
/*   Updated: 2023/11/23 13:43:34 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_irc.hpp"

int main(int argc, char **argv)
{
    if (argc != 3)
        return(displayErrorMessage("This program must run as follows : \n" BOLD "./ircserv <port> <password>" RESET), 1);
    if (!isPortValid(argv[1]))
        return 1;
    return 0;
}   