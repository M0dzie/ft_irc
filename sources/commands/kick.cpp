/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:11:02 by msapin            #+#    #+#             */
/*   Updated: 2024/02/05 16:14:13 by msapin           ###   ########.fr       */
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

std::pair<bool, bool> areOnChannel(Channel & tmpChannel) {
	(void)tmpChannel;
	
	std::pair<bool, bool>	returnPair;

	returnPair.first = false;
	returnPair.second = false;
	
	return returnPair;
}

void	executeKick(Commands & command) {

	std::vector<std::string> tmpArgs = command.getArgSplit();

	if (!command.getClient().getRegister())
		displayError(ERR_NOTREGISTERED, command);
	else
	{
		std::string	channelName = getKickChannelName(tmpArgs);
		Channel & tmpChannel = *(command.getServer().getChannelList().find(channelName))->second;
		std::pair<bool, bool>	senderReceiverOnChannel = areOnChannel(tmpChannel);

		std::cout << "check channelName: " << channelName << " pair " << senderReceiverOnChannel.first << " " << senderReceiverOnChannel.second << std::endl;

		if (tmpChannel.getName().empty())
			displayKickErrorMessage(command, channelName);
		// else if ()
			
			// displayError(ERR_NOSUCHCHANNEL, command);
			
		// // else if ()
			
	}
}
