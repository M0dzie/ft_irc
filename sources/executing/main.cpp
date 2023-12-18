/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <thmeyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 10:17:37 by thmeyer           #+#    #+#             */
/*   Updated: 2023/12/18 13:35:56 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_irc.hpp"

/* ---------- DOCUMENTATION HEXCHAT ----------

- Les discussions instantanées sont exclusivement textuelles mais on peut aussi envoyer des fichiers à travers le protocole DCC.

*/

int main(int argc, char **argv)
{
    if (argc != 3)
        return(displayErrorMessage("This program must run as follows : \n" BOLD "./ircserv <port> <password>" RESET), -1);
    if (!isPortValid(argv[1]))
        return -1;

    int socketFd = 0;
    struct sockaddr_in address;
    int opt = 1;

    // AF_INET = domain IPv4; SOCK_STREAM = socket oriente connexion (type TCP); 0 = protocole adapte au type
    if ((socketFd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        return(displayErrorMessage("creation of socket failed."), -1);
    std::cout << socketFd << std::endl;
    
    if (setsockopt(socketFd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
        return(displayErrorMessage("Something went wrong."), -1);

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = std::atoi(argv[1]);

    std::cout << address.sin_port << std::endl;

    /* Vous devrez également effectuer d'autres opérations telles que la liaison (bind()), l'écoute (listen(), 
    pour un serveur), la connexion (connect(), pour un client), etc., en fonction de vos besoins.*/
    
    // close(socketFd);
    return 0;
}