/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:47:09 by msapin            #+#    #+#             */
/*   Updated: 2024/02/06 11:33:30 by msapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands.hpp"

void	executeQuit(Commands & command) {
	(void)command;

	std::string quitMessage = *command.getArgSplit().begin();
	Client & tmpClient = command.getClient();
	std::string serverMessage = ":" + tmpClient.getNickname() + "!" + tmpClient.getUsername() + "@localhost" + " QUIT " + quitMessage;
	Server & tmpServer = command.getServer();
	(void)tmpServer;
	sendMessage(tmpClient.getFD(), serverMessage);
	displayMessage(SERVER, serverMessage);
	
	int tmpFD = tmpClient.getFD();
	(void)tmpFD;
	int numberClient = tmpServer.getNbClient();
	struct pollfd * tmpPoll = tmpServer.getPollFds();

	int i = -1;
	while (++i < numberClient)
	{
		if (tmpPoll[i].fd == tmpFD)
			break;
	}
	
	std::cout << RED << "REMOVE" << RESET << " client fd: " << tmpFD << " index: " << i << std::endl;
	while (i < numberClient)
	{
		tmpPoll[i].fd = tmpPoll[i + 1].fd;
		tmpPoll[i].events = tmpPoll[i + 1].events;
		tmpPoll[i].revents = tmpPoll[i + 1].revents;
		std::cout << "update fd: " << i << " with " << (i + 1) << " value" << std::endl;
		i++;
	}
	tmpServer.setNbClient(tmpServer.getNbClient() - 1);
	delete tmpServer.getClientList()[tmpFD];
	tmpServer.getClientList().erase(tmpFD);
	// close(tmpFD);
	// tmpServer.setFDValue(0, 1);
}
