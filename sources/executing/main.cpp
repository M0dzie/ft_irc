/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <thmeyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 10:17:37 by thmeyer           #+#    #+#             */
/*   Updated: 2023/12/18 17:17:31 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_irc.hpp"

/* ---------- DOCUMENTATION HEXCHAT ----------

-> Les discussions instantanées sont exclusivement textuelles mais on peut aussi envoyer des fichiers à travers le protocole DCC.

*/

/* ---------- HOW TO CONNECT WITH ANOTHER TERMINAL ----------

-> nc -C 127.0.0.1 8080

*/

int main(int argc, char **argv)
{
    if (argc != 3)
        return(displayErrorMessage("This program must run as follows : \n" BOLD "./ircserv <port> <password>" RESET), -1);
    if (!isPortValid(argv[1]))
        return -1;
    if (!argv[2][0])
        return (displayErrorMessage("Empty password are not authorized."), -1);

    int socketFd = 0;
    struct sockaddr_in address;
    int opt = 1;

    // AF_INET = domain IPv4; SOCK_STREAM = socket oriente connexion (type TCP); 0 = protocole adapte au type
    // Create socket file descriptor
    if ((socketFd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        return(displayErrorMessage("Creation of socket failed."), -1);
    
    // Forcefully attaching socket to the current port passing in paramater (argv[1])
    if (setsockopt(socketFd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
        return(displayErrorMessage("Something went wrong."), -1);

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    // htons function converts the unsigned short integer hostshort from host byte order to network byte order. 
    address.sin_port = htons(std::atoi(argv[1]));

    if (bind(socketFd, (struct sockaddr *)&address, sizeof(address)) < 0)
        return (displayErrorMessage("bind() failed."), -1);
    if (listen(socketFd, 1) < 0)
        return (displayErrorMessage("listen() failed."), -1);

    int clientSocket = 0;
    socklen_t addrLen = sizeof(address);
    
    // accept() block the program here
    if ((clientSocket = accept(socketFd, (struct sockaddr *)&address, &addrLen)) < 0)
        return (displayErrorMessage("accept() failed."), -1);

    char buffer[1024];
    if (recv(clientSocket, &buffer, 1024, 0) < 0)
        return (displayErrorMessage("recv() failed."), -1);
    std::cout << std::string(buffer) << std::endl;

    send(clientSocket, "Message received\n", 18, 0);
    /* Vous devrez également effectuer d'autres opérations telles que la liaison (bind()), l'écoute (listen(), 
    pour un serveur), la connexion (connect(), pour un client), etc., en fonction de vos besoins.*/
    
    // close(clientSocket);
    // close(socketFd);
    return 0;
}