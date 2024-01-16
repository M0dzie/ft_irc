/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 13:15:32 by msapin            #+#    #+#             */
/*   Updated: 2024/01/16 17:08:43 by msapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands.hpp"

void sendMessage(int clientFd, std::string msg) {
	msg += "\r\n";
	if (send(clientFd, msg.c_str(), msg.length(), 0) < 0)
		displayErrorMessage("send() failed.");
}

bool isNicknameValid(std::string nickname) {

	if (nickname[0] == '#')
		return false;
	return true;
}

// void	loginClient(std::string userName, int fd) {

// 	sendMessage(fd, ":localhost 376 " + userName + ":" + userName + "connected!");
// }

void	executeNick(Commands & command) {

	(void)command;

	std::cout << "Execute NICK" << std::endl;
	
	// std::vector<std::string>::iterator itChannel = commandLine.begin();
	// std::string command = *itChannel;
	// std::string nickname = *(++itChannel);
	// std::string oldNickname = "Undefined";

	// if (isNicknameValid(nickname))
	// {
	// 	if (oldNickname == "Undefined")
	// 	{
	// 		// std::cout << ":" + nickname + " NICK " + nickname << std::endl;
	// 		sendMessage(fd, ":" + nickname + " NICK " + nickname);
	// 	}
	// }
	// // check if not already connected and all arg valid, password, username, nickname
	// std::string tmpUserName = "msapin";
	// // loginClient(tmpUserName, fd);
	// sendMessage(fd, ":localhost 376 " + userName + ":" + userName + "connected!");
}
