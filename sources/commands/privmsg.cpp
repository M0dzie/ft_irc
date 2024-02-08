/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <thmeyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 13:47:46 by msapin            #+#    #+#             */
/*   Updated: 2024/02/08 11:22:02 by thmeyer          ###   ########.fr       */
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
		std::vector<std::string>::iterator tmpIt = it;
		tmpIt++;
		
		messageText += *it;
		if (tmpIt != tmpArg.end())
			messageText += " ";
	}
	return  messageText;
}

void	sendMessageToChannel(Commands & command, std::vector<std::string> & args) {
	
	std::string target = *args.begin();
	Client & tmpClient = command.getClient();
	Server & tmpServer = command.getServer();
	std::map<std::string, Channel *> & tmpChannels = tmpServer.getChannelList();
	Channel & tmpChannel = *(tmpChannels.find(target))->second;

	if (tmpChannel.getName().empty())
		displayError(ERR_NOSUCHCHANNEL, command);
	else
	{
		std::map<Client *, bool> const & listClient = tmpChannel.getClients();

		for (std::map<Client *, bool>::const_iterator it = listClient.begin(); it != listClient.end(); it++)
		{
			int tmpFdReceiver = it->first->getFD();
			
			if (tmpClient.getFD() != tmpFdReceiver)
			{
				std::string serverMessageReceiver = ":" + tmpClient.getNickname() + " PRIVMSG " + target + " " + getMessageText(args);
				sendMessage(tmpFdReceiver, serverMessageReceiver);
				// displayMessage(SERVER, serverMessageReceiver);
			}
		}
	}
}

void	sendMessageToClient(Commands & command, std::vector<std::string> & args) {
	
	std::string target = *args.begin();
	Client & tmpReceiver = foundClient(command, target);
	Client & tmpClient = command.getClient();
			
	if (tmpReceiver == tmpClient)
		displayError(ERR_NOSUCHNICK, command);
	else
	{
		std::string serverMessageReceiver = ":" + tmpClient.getNickname() + " PRIVMSG " + target + " " + getMessageText(args);
		sendMessage(tmpReceiver.getFD(), serverMessageReceiver);
		// displayMessage(SERVER, serverMessageReceiver);
	}
}

void	executePrivateMsg(Commands & command) {

	if (!command.getClient().getRegister())
		displayError(ERR_NOTREGISTERED, command);
	else
	{
		std::vector<std::string> & args = command.getArgSplit();

		if (args.empty())
			displayError(ERR_NEEDMOREPARAMS, command);
		else
		{
			if ((*args.begin())[0] == '#')
				sendMessageToChannel(command, args);
			else
				sendMessageToClient(command, args);
		}
	}
}
