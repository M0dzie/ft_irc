/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 13:47:46 by msapin            #+#    #+#             */
/*   Updated: 2024/01/25 16:50:04 by msapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands.hpp"

Client & foundClient(Commands & command, std::string nickname) {

	Server & tmpServer = command.getServer();
	Client & tmpClient = command.getClient();
	std::map<int, Client *> tmpClientList = tmpServer.getClientList();
	std::map<int, Client *>::iterator it = tmpClientList.begin();
	(void)tmpServer;
	(void)tmpClient;

	while (it != tmpClientList.end())
	{
		if ((it->second->getNickname()) == nickname && tmpClient.getNickname() != nickname)
		{
			std::cout << nickname << " found" << std::endl;
			return *it->second;
		}
		it++;
	}
	return command.getClient();
}

void	executePrivateMsg(Commands & command) {

	std::vector<std::string> & tmpArg = command.getArgSplit();
	std::string tmpTarget = *tmpArg.begin();
	Client & tmpClient = command.getClient();
	Client & tmpReceiver = foundClient(command, tmpTarget);
	(void)tmpTarget;
	(void)tmpClient;
	(void)tmpReceiver;

	if (tmpReceiver == tmpClient)
		displayError(ERR_NOSUCHNICK, command);
	else
	{
		std::string messageText;
		for (std::vector<std::string>::iterator it = ++tmpArg.begin(); it != tmpArg.end(); it++)
		{
			messageText += *it;
		}
		std::string serverMessageSender = ":" + tmpReceiver.getNickname() + " PRIVMSG " + tmpTarget + " " + messageText;
		std::string serverMessageReceiver = ":" + tmpClient.getNickname() + " PRIVMSG " + tmpTarget + " " + messageText;

		sendMessage(tmpClient.getFD(), serverMessageSender);
		sendMessage(tmpReceiver.getFD(), serverMessageReceiver);
	}
}
