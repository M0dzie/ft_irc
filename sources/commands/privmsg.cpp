/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 13:47:46 by msapin            #+#    #+#             */
/*   Updated: 2024/02/13 17:59:11 by msapin           ###   ########.fr       */
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

static std::string	getMessageText(std::vector<std::string> & tmpArg) {
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

static void	sendMessageToChannel(Commands & command, std::vector<std::string> & args) {
	std::string target = *args.begin();
	Client & client = command.getClient();
	Channel * tmpChannel = command.getServer().getChannelList()[target];

	if (!tmpChannel)
		sendMessage(client.getFD(), ":localhost 403 " + client.getNickname() + " " + target + " :No such channel");
	else
	{
		if (!tmpChannel->areClientOnChannel(client.getNickname()))
			tmpChannel->displayError(ERR_NOTONCHANNEL, client);
		else
		{
			std::map<Client *, bool> const & listClient = tmpChannel->getClients();

			for (std::map<Client *, bool>::const_iterator it = listClient.begin(); it != listClient.end(); it++)
			{
				int tmpFdReceiver = it->first->getFD();
				
				if (client.getFD() != tmpFdReceiver)
				{
					std::string serverMessageReceiver = ":" + client.getNickname() + " PRIVMSG " + target + " " + getMessageText(args);
					sendMessage(tmpFdReceiver, serverMessageReceiver);
				}
			}	
		}
	}
}

static void	sendMessageToClient(Commands & command, std::vector<std::string> & args) {
	std::string target = *args.begin();
	Client & receiver = foundClient(command, target);
	Client & client = command.getClient();
			
	if (receiver == client)
		sendMessage(client.getFD(), ":localhost 401 " + client.getNickname() + " " + target + " :No such nick/channel");
	else
	{
		std::string serverMessageReceiver = ":" + client.getNickname() + " PRIVMSG " + target + " " + getMessageText(args);
		sendMessage(receiver.getFD(), serverMessageReceiver);
	}
}

void	executePrivateMsg(Commands & command) {
	if (!command.getClient().getRegister())
		command.getClient().displayError(ERR_NOTREGISTERED);
	else
	{
		std::vector<std::string> & args = command.getArgSplit();

		if (args.empty())
			command.displayError(ERR_NEEDMOREPARAMS);
		else
		{
			if ((*args.begin())[0] == '#')
				sendMessageToChannel(command, args);
			else
				sendMessageToClient(command, args);
		}
	}
}
