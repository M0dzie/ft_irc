/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:11:02 by msapin            #+#    #+#             */
/*   Updated: 2024/02/05 17:58:09 by msapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands.hpp"


// ERR_NEEDMOREPARAMS (461)

// ERR_NOSUCHCHANNEL (403)
// ERR_NOTONCHANNEL (442)
// ERR_USERNOTINCHANNEL (441)
// ERR_CHANOPRIVSNEEDED (482)

std::string	getKickChannelName(std::vector<std::string> args) {

	std::vector<std::string>::iterator it = args.begin();
	std::vector<std::string>::iterator itEnd = args.end();
	(void)itEnd;

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

std::pair<bool, bool> areOnChannel(Channel & tmpChannel, std::string receiverName, std::string senderName) {

	std::pair<bool, bool>	returnPair;

	returnPair.first = false;
	returnPair.second = false;
	if (tmpChannel.getName().empty())
		return returnPair;
	else
	{
		std::map<Client *, bool> const & listClient = tmpChannel.getClients();
		
		for (std::map<Client *, bool>::const_iterator it = listClient.begin(); it != listClient.end(); it++)
		{
			std::string tmpName = it->first->getNickname();
			
			if (tmpName == senderName)
				returnPair.first = true;
			else if (tmpName == receiverName)
				returnPair.second = true;
		}
	}
	return returnPair;
}

std::string getKickReason(std::vector<std::string> args) {

	std::vector<std::string>::iterator it = args.begin();
	std::string reason = "";
	
	while (it != args.end())
	{
		std::cout << *it << std::endl;	
	}
	return "test";
}

void	executeKick(Commands & command) {

	std::vector<std::string> tmpArgs = command.getArgSplit();

	if (!command.getClient().getRegister())
		displayError(ERR_NOTREGISTERED, command);
	else
	{
		Client & tmpClient = command.getClient();
		std::string &	channelName = *command.getArgSplit().begin();
		std::string &	receiverName = *++(command.getArgSplit()).begin();
		std::string const &	senderName = tmpClient.getNickname();
		Channel & tmpChannel = *(command.getServer().getChannelList().find(channelName))->second;
		std::pair<bool, bool>	senderReceiverOnChannel = areOnChannel(tmpChannel, receiverName, senderName);

		if (tmpChannel.getName().empty())
			displayKickErrorMessage(command, channelName);
		else if (!senderReceiverOnChannel.first)
			displayError(ERR_NOTONCHANNEL, command);
		else if (!senderReceiverOnChannel.second)
			displayError(ERR_USERNOTINCHANNEL, command);
		else if (!tmpChannel.getClients()[&tmpClient])
			return (displayErrorChannel(ERR_CHANOPRIVSNEEDED, tmpClient, tmpChannel));
		else
		{
			// add check if reason define or not
			std::string reason = getKickReason(tmpArgs);
			
			std::string commandMessage	= ":" + senderName + "!" + tmpClient.getUsername() + "@localhost KICK " + channelName + " " + receiverName + " " + reason;
			sendMessage(tmpClient.getFD(), commandMessage);
			// channel->sendMessageToChannel(tmpClient->getNickname() + " is leaving the channel " + channelName);
			
			Client & clientReceiver = foundClient(command, receiverName);
			sendMessage(clientReceiver.getFD(), ":" + clientReceiver.getNickname() + "!" + clientReceiver.getUsername() + "@localhost" + " PART " + channelName + " :" + reason);
			
			tmpChannel.removeClient(&clientReceiver, command.getServer());
		}
	}
}
