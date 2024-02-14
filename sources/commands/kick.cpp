/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:11:02 by msapin            #+#    #+#             */
/*   Updated: 2024/02/14 15:19:29 by msapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands.hpp"

static std::vector<std::string>::iterator	getReasonIterator(std::vector<std::string> & args) {
	std::vector<std::string>::iterator it = args.begin();

	while (it != args.end())
	{
		if ((*it)[0] == ':')
			return it;
		it++;
	}
	return it;
}

static std::string getKickReason(std::vector<std::string> & args) {
	std::vector<std::string>::iterator reasonIt = getReasonIterator(args);

	if (reasonIt == args.end())
		return "Kick without any particular reason";
	std::string reason = "";
	
	while (reasonIt != args.end())
	{
		std::vector<std::string>::iterator tmpIt = reasonIt;
		
		reason += *reasonIt;
		if (++tmpIt != args.end())
			reason += " ";
		reasonIt++;
	}
	return reason;
}

void	executeKick(Commands & command) {
	std::vector<std::string> tmpArgs = command.getArgSplit();
	Client & client = command.getClient();

	if (!client.getRegister())
		client.displayError(ERR_NOTREGISTERED);
	else
	{
		if (tmpArgs.size() < 2)
			command.displayError(ERR_NEEDMOREPARAMS);
		else
		{
			std::string &	channelName = *command.getArgSplit().begin();
			std::string &	receiverName = *++(command.getArgSplit()).begin();
			std::string const &	senderName = client.getNickname();
			Channel * channel = command.getServer().getChannelList()[channelName];

			if (!channel)
				sendMessage(client.getFD(), ":localhost 401 " + client.getNickname() + " " + command.getArgSplit()[0] + " :No such nick/channel");
			else
			{
				if (!channel->areClientOnChannel(senderName))
					channel->displayError(ERR_NOTONCHANNEL, client);
				else if (!channel->areClientOnChannel(receiverName))
					sendMessage(client.getFD(), ":localhost 441 " + client.getUsername() + " " + receiverName + " " + channel->getName() + " :They aren't on that channel");
				else if (!channel->getClients()[&client])
					channel->displayError(ERR_CHANOPRIVSNEEDED, client);
				else
				{
					Client & clientReceiver = foundClient(command, receiverName);
					std::string reason = getKickReason(tmpArgs);
					std::string commandMessage	= ":" + senderName + "!" + client.getUsername() + "@localhost KICK " + channelName + " " + receiverName + " " + reason;

					sendMessage(clientReceiver.getFD(), ":" + clientReceiver.getNickname() + "!" + clientReceiver.getUsername() + "@localhost" + " PART " + channelName + " " + reason);
					clientReceiver.removeOneChannel(channel);
					channel->removeClient(&clientReceiver, command.getServer());
				}
			}
		}
	}
}
