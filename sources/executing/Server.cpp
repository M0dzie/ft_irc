/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <thmeyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 10:37:42 by thmeyer           #+#    #+#             */
/*   Updated: 2024/01/10 16:23:10 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Server.hpp"

/* Thus, if you try to read/recv or write/send in any file descriptor
without using poll() (or equivalent), your grade will be 0. */

void	parseLine(std::string line) {
	std::cout << "LINE: " << line << std::endl;
}

Server::Server(int port) {
    int serverFd = 0;
    struct sockaddr_in address;
    int opt = 1;

    // AF_INET = domain IPv4; SOCK_STREAM = socket oriente connexion (type TCP); 0 = protocole adapte au type
    // Create socket file descriptor
    if ((serverFd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        throw(Server::ServerError(ERROR "Creation of socket failed."));
        // return(displayErrorMessage("Creation of socket failed."), -1);
    
    // Forcefully attaching socket to the current port passing in paramater (port)
    if (setsockopt(serverFd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
        throw(Server::ServerError(ERROR "Something went wrong."));

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    // htons function converts the unsigned short integer hostshort from host byte order to network byte order. 
    address.sin_port = htons(port);

    if (bind(serverFd, (struct sockaddr *)&address, sizeof(address)) < 0)
        throw(Server::ServerError(ERROR "bind() failed."));
        
    if (listen(serverFd, 1) < 0)
        throw(Server::ServerError(ERROR "listen() failed."));

    // int clientSocket = 0;
        
    // accept() block the program here
    // if ((clientSocket = accept(serverFd, (struct sockaddr *)&address, &addrLen)) < 0)
    //     throw(Server::ServerError(ERROR "accept() failed."));

    socklen_t addrLen = sizeof(address);
    std::string tmpSentence;
    int nbClient = 0;
	int bufferSize = 1024;
	char buffer[bufferSize];
    for (int i = 0; i < bufferSize; i++)
		buffer[i] = '\0';

    struct pollfd fds[MAXCLIENT + 1]; // + 1 for clientSocket : Server fd
    fds[0].fd = serverFd;
    fds[0].events = POLLIN;

    while (1) {
        poll(fds, nbClient + 1, -1);
        
        if (fds[0].fd == serverFd) {
            nbClient += 1;
            if ((fds[nbClient].fd = accept(serverFd, (struct sockaddr *)&address, &addrLen)) < 0 ) {
                displayErrorMessage("accept() failed.");
                break;
            }
        }
        std::cout << nbClient << std::endl;
        for (int i = 0; i < nbClient + 1; i++) {
            if (fds[i].revents & POLLIN) { // there is data ready to recv()
                if (recv(fds[i].fd, &buffer, bufferSize, 0) < 0) {
                    displayErrorMessage("recv() failed.");
                    break;
                }
                tmpSentence.append(buffer);
                std::size_t indexEnd = tmpSentence.find("\r\n");
                while(indexEnd != std::string::npos)
                {
                    std::string command = tmpSentence.substr(0, indexEnd);
                    tmpSentence = tmpSentence.substr(indexEnd + 2, tmpSentence.size());;
                    parseLine(command);
                    indexEnd = tmpSentence.find("\r\n");
                }
                for (int i = 0; i <= bufferSize; i++)
                buffer[i] = '\0';
            }
        }
	}
        
    // while (1) {
    //     char buffer[1024];
    //     if (recv(clientSocket, &buffer, 1024, 0) < 0)
    //     throw(Server::ServerError(ERROR "recv() failed."));
    //         // boucle pour stocker l'entierete du buffer avant de print
    //     std::cout << std::string(buffer);
    //     send(clientSocket, "Message received\n", 18, 0);
    //     for (size_t i = 0; i < sizeof(buffer); i++)
    //         buffer[i] = '\0';
    // }
    /* Vous devrez également effectuer d'autres opérations telles que la liaison (bind()), l'écoute (listen(), 
    pour un serveur), la connexion (connect(), pour un client), etc., en fonction de vos besoins.*/
    
    // close(clientSocket);
    // close(serverFd);
}