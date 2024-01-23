/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <thmeyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 13:15:30 by msapin            #+#    #+#             */
/*   Updated: 2024/01/23 16:29:16 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands.hpp"

static std::vector<std::string> getChannelVector(std::string itChannel) {

	std::vector<std::string> tmpVector;
	std::string word;

	if ((itChannel).find(",") != std::string::npos) {
		std::stringstream streamLine(itChannel);

		while(!streamLine.eof()) {
			std::getline(streamLine, word, ',');
			tmpVector.push_back(word);
		}
	} else
		tmpVector.push_back(itChannel);
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

static bool isArgValid(Commands &command, std::vector<std::string> splitJoin, std::string &channelName, std::string &password) {
	
	if (splitJoin.size() < 1 || splitJoin.at(0).empty()) {
		displayError(ERR_NEEDMOREPARAMS, command);
		return false;
	}

	channelName = splitJoin.at(0);
	splitJoin.erase(splitJoin.begin());
	
	if (splitJoin.size() == 1) {
		password = splitJoin.at(1);
		splitJoin.erase(splitJoin.begin());
	}

	if (channelName[0] != '#' || channelName.size() < 2 || channelName.find('#', 1) != std::string::npos)
		return false;
	
	return true;
}

void	executeJoin(Commands & command) {

	std::string channelName;
	std::string password;
	std::vector<std::string> splitJoin = splitMultiChannels(command.getArgSplit());

	if (!isArgValid(command, splitJoin, channelName, password))
		return;

	std::cout << "channelName: " << channelName << std::endl;
	std::cout << "password: " << password << std::endl;

	command.getServer().getChannelList().insert(std::pair<std::string, Channel *>(command.getArgSplit()[0], new Channel(command.getArgSplit()[0], "")));
	displayMessage(SERVER, ":" + command.getClient().getNickname() + " JOIN " + command.getArgSplit()[0]);
	sendMessage(command.getClient().getFD(), ":" + command.getClient().getNickname() + " JOIN " + command.getArgSplit()[0]);
	sendMessage(command.getClient().getFD(), command.getClient().getNickname() + " is joining the channel " + command.getArgSplit()[0]);
}
