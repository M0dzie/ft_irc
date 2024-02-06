/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:47:09 by msapin            #+#    #+#             */
/*   Updated: 2024/02/06 13:36:55 by msapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands.hpp"

int	getClientFDIndex(Server & tmpServer, Client & tmpClient) {
	int numberClient = tmpServer.getNbClient();
	int tmpFD = tmpClient.getFD();
	struct pollfd * tmpPoll = tmpServer.getPollFds();
	int i = -1;
	
	while (++i < numberClient)
	{
		if (tmpPoll[i].fd == tmpFD)
			break;
	}
	return i;
}

void	clearFromChannel(Server & tmpServer, Client & tmpClient) {
	(void)tmpServer;
	(void)tmpClient;
	
}

void	clearClient(Server & tmpServer, Client & tmpClient) {
	int tmpFD = tmpClient.getFD();
	int numberClient = tmpServer.getNbClient();
	struct pollfd * tmpPoll = tmpServer.getPollFds();
	int i = getClientFDIndex(tmpServer, tmpClient);

	// std::cout << RED << "REMOVE" << RESET << " client fd: " << tmpFD << " index: " << i << std::endl;
	while (i < numberClient)
	{
		tmpPoll[i].fd = tmpPoll[i + 1].fd;
		tmpPoll[i].events = tmpPoll[i + 1].events;
		tmpPoll[i].revents = tmpPoll[i + 1].revents;
		// std::cout << "update fd: " << i << " with " << (i + 1) << " value" << std::endl;
		i++;
	}
	tmpServer.setNbClient(tmpServer.getNbClient() - 1);
	delete tmpServer.getClientList()[tmpFD];
	tmpServer.getClientList().erase(tmpFD);
	close(tmpFD);
}

void	executeQuit(Commands & command) {

	Client & tmpClient = command.getClient();
	std::string serverMessage = ":" + tmpClient.getNickname() + "!" + tmpClient.getUsername() + "@localhost" + " QUIT " + *command.getArgSplit().begin();
	Server & tmpServer = command.getServer();

	sendMessage(tmpClient.getFD(), serverMessage);
	displayMessage(SERVER, serverMessage);
	
	clearFromChannel(tmpServer, tmpClient);
	clearClient(tmpServer, tmpClient);
}
