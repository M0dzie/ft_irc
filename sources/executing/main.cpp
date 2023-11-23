/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <thmeyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 10:17:37 by thmeyer           #+#    #+#             */
/*   Updated: 2023/11/23 13:12:55 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_irc.hpp"

int main(int argc, char **argv)
{
    if (argc != 3)
        return(displayErrorMessage(BLACK "This program must run as follows : \n" RESET "./ircserv <port> <password>"), 1);
    if (!isArgValid(argv))
        return 1;
    return 0;
}   