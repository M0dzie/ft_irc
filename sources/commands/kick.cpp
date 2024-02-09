/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:11:02 by msapin            #+#    #+#             */
/*   Updated: 2024/02/09 11:22:26 by msapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands.hpp"

std::string	getKickChannelName(std::vector<std::string> args) {

	std::vector<std::string>::iterator it = args.begin();

	while (it != args.end())
	{
		if ((*it)[0] == '#')
			return *it;
		it++;
	}
	return *(args.begin());
}

void	displayKickErrorMessage(Commands & command, std::string & channelName) {
	
	std::cout << PURPLE << BOLD << "Warning: " << RESET << command.getClient().getUsername() << " " << channelName << " :No such channel" << std::endl;
}

std::vector<std::string>::iterator	getReasonIterator(std::vector<std::string> & args) {
	
	std::vector<std::string>::iterator it = args.begin();

	while (it != args.end())
	{
		if ((*it)[0] == ':')
			return it;
		it++;
	}
	return it;
}

std::string getKickReason(std::vector<std::string> & args) {

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

	if (!command.getClient().getRegister())
		displayError(ERR_NOTREGISTERED, command);
	else
	{
		if (tmpArgs.size() < 2)
			displayError(ERR_NEEDMOREPARAMS, command);
		else
		{
			Client & tmpClient = command.getClient();
			std::string &	channelName = *command.getArgSplit().begin();
			std::string &	receiverName = *++(command.getArgSplit()).begin();
			std::string const &	senderName = tmpClient.getNickname();
			Channel * tmpChannel = command.getServer().getChannelList()[channelName];

			if (!tmpChannel)
				displayKickErrorMessage(command, channelName);
			else
			{
				if (!tmpChannel->areClientOnChannel(senderName))
					displayErrorChannel(ERR_NOTONCHANNEL, tmpClient, *tmpChannel);
				else if (!tmpChannel->areClientOnChannel(receiverName))
					std::cout << PURPLE << BOLD << "Warning: " << RESET << tmpClient.getUsername() << " " << receiverName << " " << tmpChannel->getName() << " :They aren't on that channel" << std::endl;
				else if (!tmpChannel->getClients()[&tmpClient])
					displayErrorChannel(ERR_CHANOPRIVSNEEDED, tmpClient, *tmpChannel);
				else
				{
					Client & clientReceiver = foundClient(command, receiverName);
					std::string reason = getKickReason(tmpArgs);
					std::string commandMessage	= ":" + senderName + "!" + tmpClient.getUsername() + "@localhost KICK " + channelName + " " + receiverName + " " + reason;
					
					sendMessage(tmpClient.getFD(), commandMessage);
					sendMessage(clientReceiver.getFD(), ":" + clientReceiver.getNickname() + "!" + clientReceiver.getUsername() + "@localhost" + " PART " + channelName + " " + reason);
					tmpChannel->removeClient(&clientReceiver, command.getServer());
				}
			}
				
		}
	}
}
