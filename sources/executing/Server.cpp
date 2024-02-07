/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <thmeyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 10:37:42 by thmeyer           #+#    #+#             */
/*   Updated: 2024/02/07 09:34:02 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Server.hpp"
#include "../../includes/Commands.hpp"

// non-member attribute to handle signal with sigaction
bool Server::interrupt = false;

void Server::sendMessage(int clientFd, std::string msg) {
	msg += "\r\n";
	
	if (send(clientFd, msg.c_str(), msg.length(), 0) < 0)
		displayErrorMessage("send() failed.");
}

Server::Server(int port, char *password) {
	std::string tmpSentence;
	int bufferSize = 1024;
	char buffer[bufferSize];
	
	for (int i = 0; i < bufferSize; i++)
		buffer[i] = '\0';

	this->initDataAndServer(port, password);
	this->handlingSignal();

	while (Server::interrupt == false) {
		poll(this->_fds, this->_nbClient + 1, -1);
		
		// handling new clients
		if (this->_fds[0].revents & POLLIN) {
			int newFD = accept(this->_fds[0].fd, (struct sockaddr *)&this->_address, &this->_addrLen);
			if (newFD < 0) {
				displayErrorMessage("accept() failed.");
				this->exit();
			}
			
			if (this->_nbClient + 1 < MAXCLIENT) {
				this->_nbClient += 1;
				this->_fds[this->_nbClient].fd = newFD;
				this->_fds[this->_nbClient].events = POLLIN;
				this->_fds[this->_nbClient].revents = 0;
				this->_clientList.insert(std::pair<int, Client *>(this->_fds[this->_nbClient].fd, new Client(this->_fds[this->_nbClient].fd, "undefined")));

				std::cout << GREEN << "ADD" << RESET << " client fd: " << this->_fds[this->_nbClient].fd << " index: " << this->_nbClient << std::endl;
			} else { // There is no places left
				displayErrorMessage("The number of client available is full.");
				close(newFD);
			}
		}
		
		//handling msg from known clients
		for (int i = 1; i < this->_nbClient + 1; i++) {
			if (this->_fds[i].fd && this->_fds[i].revents & POLLIN) { // there is data ready to recv()
				if (recv(this->_fds[i].fd, &buffer, bufferSize, 0) < 1) {
					clearFromChannel(*this, *this->_clientList[this->_fds[i].fd]);
					clearClient(*this, *this->_clientList[this->_fds[i].fd]);
				}
				tmpSentence.append(buffer);
				std::size_t indexEnd = tmpSentence.find("\r\n");
				
				while(indexEnd != std::string::npos)
				{
					std::string line = tmpSentence.substr(0, indexEnd);
					displayMessage(CLIENT, line);
					Commands cmd(line, *this->_clientList[this->_fds[i].fd], *this);

					cmd.executeCommand();
					tmpSentence = tmpSentence.substr(indexEnd + 2, tmpSentence.size());;
					indexEnd = tmpSentence.find("\r\n");
				}
				for (int i = 0; i <= bufferSize; i++)
					buffer[i] = '\0';
			}
		}
	}
	this->exit();
}

void displayMessage(int from, std::string message) {

	if (from == SERVER)
		std::cout << BLUE << "[SERVER] " << RESET << message << std::endl;
	else if (from == CLIENT)
		std::cout << YELLOW << "[CLIENT] " << RESET << message << std::endl;
}

Server::~Server() {
	this->exit();
}

void Server::exit() {
	Server::interrupt = true;
	
	for (int i = 0; i < this->_nbClient + 1; i++)
		close(this->_fds[i].fd);

	for (std::map<int, Client *>::iterator it = this->_clientList.begin(); it != this->_clientList.end(); it++)
		delete it->second;
	this->_clientList.clear();

	for (std::map<std::string, Channel *>::iterator it = this->_channelList.begin(); it != this->_channelList.end(); it++)
	    delete it->second;
	this->_channelList.clear();
}

void Server::initDataAndServer(int port, char *password) {
	int opt = 1;
	this->_nbClient = 0;
	this->_password = password;
	this->_addrLen = sizeof(this->_address);
	this->_address.sin_family = AF_INET;
	this->_address.sin_addr.s_addr = INADDR_ANY;
	this->_address.sin_port = htons(port); // htons function converts the unsigned short integer hostshort from host byte order to network byte order.
	this->_addrLen = sizeof(this->_address);
	this->_fds[0].events = POLLIN;
	this->_fds[0].revents = 0;
	
	// AF_INET = domain IPv4; SOCK_STREAM = socket oriente connexion (type TCP); 0 = protocole adapte au type
	// Create socket file descriptor
	if ((this->_fds[0].fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		throw(Server::ServerError(ERROR "Creation of socket failed."));
	
	// Forcefully attaching socket to the current port passing in paramater (port)
	if (setsockopt(this->_fds[0].fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
		throw(Server::ServerError(ERROR "Something went wrong."));

	if (bind(this->_fds[0].fd, (struct sockaddr *)&this->_address, sizeof(this->_address)) < 0)
		throw(Server::ServerError(ERROR "bind() failed."));
		
	if (listen(this->_fds[0].fd, 1) < 0)
		throw(Server::ServerError(ERROR "listen() failed."));
}

void Server::handleBreak(int sig) {
	if (sig == SIGINT || sig == SIGQUIT || sig == SIGTSTP)
	{
		Server::interrupt = true;

		if (sig == SIGINT)
			std::cerr << BLUE << BOLD << "SIGINT called." << RESET << std::endl;
		if (sig == SIGQUIT)
			std::cerr << BLUE << BOLD << "SIGQUIT called." << RESET << std::endl;
		if (sig == SIGTSTP)
			std::cerr << BLUE << BOLD << "SIGTSTP called." << RESET << std::endl;
	}
}

void Server::handlingSignal() {
	struct sigaction sig;
	sig.sa_handler = &Server::handleBreak;
	sig.sa_flags = 0;

	sigemptyset(&sig.sa_mask);
	
	if (sigaction(SIGINT, &sig, NULL) != 0)
		displayErrorMessage("SIGINT.");

	if (sigaction(SIGQUIT, &sig, NULL) != 0)
		displayErrorMessage("SIGQUIT.");
		
	if (sigaction(SIGTSTP, &sig, NULL) != 0)
		displayErrorMessage("SIGTSTP.");
}