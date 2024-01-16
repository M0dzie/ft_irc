/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <thmeyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 10:17:37 by thmeyer           #+#    #+#             */
/*   Updated: 2024/01/16 13:28:38 by thmeyer          ###   ########.fr       */
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
    if (std::atoi(argv) < 1024) {
        std::cerr << YELLOW << BOLD << "Warning: " << RESET << "Those ports : [0-1023] are used by system processes and might not work." << std::endl;
        return true;
    }
    return true;
}

static bool isPasswordValid(char *argv) {
    if (!argv[0])
        return (displayErrorMessage("Password can't be empty."), false);
    return true;
}

int main(int argc, char **argv) {
    if (argc != 3)
        return(displayErrorMessage("This program must run as follows : \n" BOLD "./ircserv <port> <password>" RESET), -1);
    if (!isPortValid(argv[1]) || !isPasswordValid(argv[2]))
        return -1;

    try {
        Server server(std::atoi(argv[1]));
    } catch (std::exception const &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}