/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <thmeyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 10:17:37 by thmeyer           #+#    #+#             */
/*   Updated: 2023/12/19 16:13:10 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_irc.hpp"

/* ---------- DOCUMENTATION HEXCHAT ----------

-> Les discussions instantanées sont exclusivement textuelles mais on peut aussi envoyer des fichiers à travers le protocole DCC.

*/

/* ---------- HOW TO CONNECT WITH ANOTHER TERMINAL ----------

-> nc -C 127.0.0.1 6667

*/

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