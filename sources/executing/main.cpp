/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <thmeyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 10:17:37 by thmeyer           #+#    #+#             */
/*   Updated: 2024/01/16 12:59:06 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_irc.hpp"

/* ---------- HOW TO CONNECT WITH ANOTHER TERMINAL ----------

-> nc -C 127.0.0.1 6667

*/

void displayErrorMessage(std::string const &msg) {
    std::cerr << ERROR << msg << std::endl;
}

static bool isPortValid(char *argv) {
    for (int i = 0; argv[i]; i++)
        if (!std::isdigit(argv[i]))
            return (displayErrorMessage("Port must be a positive number."), false);
    if (std::atoi(argv) > 65535)
        return (displayErrorMessage("Port available : [0-65535]"), false);
    if (std::atoi(argv) < 1025) {
        std::cerr << YELLOW << BOLD << "Warning: " << RESET << "This port might be reserved to a root access." << std::endl;
        return (true);
    }
    return true;
}

int main(int argc, char **argv) {
    if (argc != 3)
        return(displayErrorMessage("This program must run as follows : \n" BOLD "./ircserv <port> <password>" RESET), -1);
    if (!isPortValid(argv[1]))
        return -1;

    try {
        Server server(std::atoi(argv[1]));
    } catch (std::exception const &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}