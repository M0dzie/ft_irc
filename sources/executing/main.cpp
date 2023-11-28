/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <thmeyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 10:17:37 by thmeyer           #+#    #+#             */
/*   Updated: 2023/11/28 10:31:24 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_irc.hpp"

/* ---------- DOCUMENTATION HEXCHAT ----------

- Les discussions instantanées sont exclusivement textuelles mais on peut aussi envoyer des fichiers à travers le protocole DCC.

*/

int main(int argc, char **argv)
{
    if (argc != 3)
        return(displayErrorMessage("This program must run as follows : \n" BOLD "./ircserv <port> <password>" RESET), 1);
    if (!isPortValid(argv[1]))
        return 1;

    // AF_INET = domain IPv4; SOCK_STREAM = socket oriente connexion (type TCP); 0 = protocole adapte au type
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    
    if (serverSocket == -1)
        return(displayErrorMessage("creation of socket failed"), 1);
    std::cout << serverSocket << std::endl;

    /* Vous devrez également effectuer d'autres opérations telles que la liaison (bind()), l'écoute (listen(), 
    pour un serveur), la connexion (connect(), pour un client), etc., en fonction de vos besoins.*/
    
    // close(serverSocket);
    return 0;
}   