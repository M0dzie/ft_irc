/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 13:47:46 by msapin            #+#    #+#             */
/*   Updated: 2024/02/01 15:29:06 by msapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands.hpp"

Client & foundClient(Commands & command, std::string nickname) {

	Server & tmpServer = command.getServer();
	Client & tmpClient = command.getClient();
	std::map<int, Client *> tmpClientList = tmpServer.getClientList();
	std::map<int, Client *>::iterator it = tmpClientList.begin();
	
	while (it != tmpClientList.end())
	{
		if ((it->second->getNickname()) == nickname && tmpClient.getNickname() != nickname)
			return *it->second;
		it++;
	}
	return command.getClient();
}

std::string	getMessageText(std::vector<std::string> & tmpArg) {
	std::string messageText;
	
	for (std::vector<std::string>::iterator it = ++tmpArg.begin(); it != tmpArg.end(); it++)
	{
		messageText += *it;
	}

	return  messageText;
}

void	executePrivateMsg(Commands & command) {

	std::vector<std::string> & tmpArg = command.getArgSplit();

	if (tmpArg.empty())
		displayError(ERR_NEEDMOREPARAMS, command);
	else
	{
		std::string tmpTarget = *tmpArg.begin();
		Client & tmpClient = command.getClient();
		Server & tmpServer = command.getServer();

		if (tmpTarget[0] == '#')
		{
			std::map<std::string, Channel *> & tmpChannels = tmpServer.getChannelList();
			Channel & tmpChannel = *(tmpChannels.find(tmpTarget))->second;

			if (tmpChannel.getName().empty())
				displayError(ERR_NOSUCHCHANNEL, command);
			else
			{
				std::vector<Client *> const & listClient = tmpChannel.getClientIn();

				for (std::vector<Client *>::const_iterator it = listClient.begin(); it != listClient.end(); it++)
				{
					int tmpFdReceiver = (*it)->getFD();
					
					if ( tmpClient.getFD() != tmpFdReceiver)
					{
						std::string serverMessageReceiver = ":" + tmpClient.getNickname() + " PRIVMSG " + tmpTarget + " " + getMessageText(tmpArg);
						sendMessage((*it)->getFD(), serverMessageReceiver);
					}
				}
			}
		}
		else
		{
			Client & tmpReceiver = foundClient(command, tmpTarget);
					
			if (tmpReceiver == tmpClient)
				displayError(ERR_NOSUCHNICK, command);
			else
			{
				std::string serverMessageReceiver = ":" + tmpClient.getNickname() + " PRIVMSG " + tmpTarget + " " + getMessageText(tmpArg);
				sendMessage(tmpReceiver.getFD(), serverMessageReceiver);
			}
		}
	}
}
