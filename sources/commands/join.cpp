/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <thmeyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 13:15:30 by msapin            #+#    #+#             */
/*   Updated: 2024/01/23 14:03:01 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands.hpp"

static std::vector<std::string> getChannelVector(std::string itChannel) {

	std::vector<std::string> tmpVector;
	std::string word;

	if ((itChannel).find(",") != std::string::npos)
	{
		std::stringstream streamLine(itChannel);

		while(!streamLine.eof())
		{
			std::getline(streamLine, word, ',');
			tmpVector.push_back(word);
		}
	}
	else
	{
		tmpVector.push_back(itChannel);
	}
	return tmpVector;
}

static std::vector<std::string> splitMultiChannels(std::vector<std::string> vectorContent) {

	std::vector<std::string> splitJoin;
	std::vector<std::string> tmp;
	std::vector<std::string>::iterator it;

	for (it = vectorContent.begin(); it != vectorContent.end(); it++) {
		tmp = getChannelVector(*it);
		splitJoin.insert(splitJoin.end(), tmp.begin(), tmp.end());
	}
	return splitJoin;
}

// bool getArg(Commands &command, std::string &channelName, std::string &password) {
	
// }

void	executeJoin(Commands & command) {

	std::string channelName;
	std::string password;
	std::vector<std::string> splitJoin = splitMultiChannels(command.getArgSplit());


	// std::map<std::string, Channel *>::iterator it = command.getServer().getChannelList().find(name);
	
	command.getServer().getChannelList().insert(std::pair<std::string, Channel *>(command.getArgSplit()[0], new Channel(command.getArgSplit()[0], "")));
	displayMessage(SERVER, ":" + command.getClient().getNickname() + " JOIN " + command.getArgSplit()[0]);
	sendMessage(command.getClient().getFD(), ":" + command.getClient().getNickname() + " JOIN " + command.getArgSplit()[0]);
	sendMessage(command.getClient().getFD(), command.getClient().getNickname() + " is joining the channel " + command.getArgSplit()[0]);
	
	// std::vector<std::string>::iterator itChannel = commandLine.begin();
	// std::string command = *itChannel;
	// std::vector<std::string> channelVector = getChannelVector(*(++itChannel));

	// std::cout << "CHANNEL:" << std::endl;
	// displayVectorContent(channelVector);
	// if ((itChannel) != commandLine.end())
	// {
	// 	std::vector<std::string> passwordVector = getChannelVector(*(++itChannel));
	// 	std::cout << std::endl << "PASSWORD: " << std::endl;
	// 	displayVectorContent(passwordVector);
	// }
}
