/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <thmeyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 10:37:42 by thmeyer           #+#    #+#             */
/*   Updated: 2024/01/16 12:39:19 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Server.hpp"

/* Thus, if you try to read/recv or write/send in any file descriptor
without using poll() (or equivalent), your grade will be 0. */

void Server::sendMessage(int clientFd, std::string msg) {
    msg += "\r\n";
    if (send(clientFd, msg.c_str(), msg.length(), 0) < 0)
        displayErrorMessage("send() failed.");
}

void	parseLine(std::string line) {
	std::cout << "LINE: " << line << std::endl;
}

Server::Server(int port) {
    std::string tmpSentence;
	int bufferSize = 1024;
	char buffer[bufferSize];
    for (int i = 0; i < bufferSize; i++)
		buffer[i] = '\0';

    this->initDataAndServer(port);

    while (this->_interrupt == false) {
        poll(this->_fds, this->_nbClient + 1, -1);
        
        // handling new clients
        if (this->_fds[0].revents & POLLIN) {
            if (this->_nbClient + 1 < MAXCLIENT) {
                this->_nbClient += 1;
                if ((this->_fds[this->_nbClient].fd = accept(this->_fds[0].fd, (struct sockaddr *)&this->_address, &this->_addrLen)) < 0 ) {
                    displayErrorMessage("accept() failed.");
                    this->_interrupt = true;
                }
                this->_fds[this->_nbClient].events = POLLIN;
                this->_fds[this->_nbClient].revents = 0;
                this->_clientList.insert(std::pair<int, Client *>(this->_fds[this->_nbClient].fd, new Client(this->_fds[this->_nbClient].fd, "undefined")));
                std::cout << this->_clientList[this->_nbClient]->getFD() << std::endl;
            } else { // There is no places left
                displayErrorMessage("The number of client available is full.");
                this->_interrupt = true;
            }
        }
        
        //handling msg from known clients
        for (int i = 1; i <= this->_nbClient + 1; i++) {
            if (this->_fds[i].revents & POLLIN) { // there is data ready to recv()
                if (recv(this->_fds[i].fd, &buffer, bufferSize, 0) == 0) {
                    displayErrorMessage("recv() failed.");
                    this->_interrupt = true;
                }
                tmpSentence.append(buffer);
                std::size_t indexEnd = tmpSentence.find("\r\n");
                while(indexEnd != std::string::npos)
                {
                    std::string command = tmpSentence.substr(0, indexEnd);
                    tmpSentence = tmpSentence.substr(indexEnd + 2, tmpSentence.size());;
                    parseLine(command);
                    // Send to everyone
                    // for (int j = 1; j <= this->_nbClient + 1; j++) {
                    //     int destFd = this->_fds[j].fd;
                    //     if (destFd != this->_fds[0].fd && destFd != this->_fds[i].fd)
                    //         this->sendMessage(this->_fds[j].fd, command);
                    // }
                    this->sendMessage(this->_fds[i].fd, command);
                    indexEnd = tmpSentence.find("\r\n");
                }
                for (int i = 0; i <= bufferSize; i++)
                buffer[i] = '\0';
            }
        }
	}
}

void Server::initDataAndServer(int port) {
    this->_opt = 1;
    this->_nbClient = 0;
    this->_interrupt = false;
    this->_addrLen = sizeof(this->_address);
    this->_address.sin_family = AF_INET;
    this->_address.sin_addr.s_addr = INADDR_ANY;
    this->_address.sin_port = htons(port); // htons function converts the unsigned short integer hostshort from host byte order to network byte order.
    this->_addrLen = sizeof(this->_address);
    this->_fds[0].events = POLLIN;
    
    // AF_INET = domain IPv4; SOCK_STREAM = socket oriente connexion (type TCP); 0 = protocole adapte au type
    // Create socket file descriptor
    if ((this->_fds[0].fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        throw(Server::ServerError(ERROR "Creation of socket failed."));
        // return(displayErrorMessage("Creation of socket failed."), -1);
    
    // Forcefully attaching socket to the current port passing in paramater (port)
    if (setsockopt(this->_fds[0].fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &this->_opt, sizeof(this->_opt)))
        throw(Server::ServerError(ERROR "Something went wrong."));

    if (bind(this->_fds[0].fd, (struct sockaddr *)&this->_address, sizeof(this->_address)) < 0)
        throw(Server::ServerError(ERROR "bind() failed."));
        
    if (listen(this->_fds[0].fd, 1) < 0)
        throw(Server::ServerError(ERROR "listen() failed."));

}