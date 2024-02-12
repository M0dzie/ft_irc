/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:47:09 by msapin            #+#    #+#             */
/*   Updated: 2024/02/12 11:05:31 by msapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands.hpp"

static int	getClientFDIndex(Server & tmpServer, Client & tmpClient) {
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
	std::vector<Channel *> & tmpChannels = tmpClient.getChannels();

	for (std::vector<Channel *>::iterator it = tmpChannels.begin(); it != tmpChannels.end(); it++)
	{
		(*it)->sendMessageToChannel(tmpClient.getNickname() + " is leaving the channel " + (*it)->getName());
		(*it)->removeClient(&tmpClient, tmpServer);
	}
}

void	clearClient(Server & tmpServer, Client & tmpClient) {
	int tmpFD = tmpClient.getFD();
	int numberClient = tmpServer.getNbClient();
	struct pollfd * tmpPoll = tmpServer.getPollFds();
	int i = getClientFDIndex(tmpServer, tmpClient);

	while (i < numberClient)
	{
		tmpPoll[i].fd = tmpPoll[i + 1].fd;
		tmpPoll[i].events = tmpPoll[i + 1].events;
		tmpPoll[i].revents = tmpPoll[i + 1].revents;
		i++;
	}
	tmpServer.setNbClient(tmpServer.getNbClient() - 1);
	delete tmpServer.getClientList()[tmpFD];
	tmpServer.getClientList().erase(tmpFD);
	close(tmpFD);
}

void	executeQuit(Commands & command) {
	if (!command.getClient().getRegister())
		return (displayError(ERR_NOTREGISTERED, command));

	Client & tmpClient = command.getClient();
	std::string serverMessage = ":" + tmpClient.getNickname() + "!" + tmpClient.getUsername() + "@localhost" + " QUIT " + getReason(command.getArgSplit());
	Server & tmpServer = command.getServer();

	sendMessage(tmpClient.getFD(), serverMessage);
	clearFromChannel(tmpServer, tmpClient);
	clearClient(tmpServer, tmpClient);
}
