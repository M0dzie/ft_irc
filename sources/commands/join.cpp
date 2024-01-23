/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <thmeyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 13:15:30 by msapin            #+#    #+#             */
/*   Updated: 2024/01/23 17:14:00 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands.hpp"

static std::vector<std::string> splitArg(std::string arg) {

	std::vector<std::string> tmpVector;
	std::string word;

	if ((arg).find(",") != std::string::npos) {
		std::stringstream streamLine(arg);

		while(!streamLine.eof()) {
			std::getline(streamLine, word, ',');
			tmpVector.push_back(word);
		}
	} else
		tmpVector.push_back(arg);
	return tmpVector;
}

// static std::vector<std::string> splitMultiChannels(std::vector<std::string> vectorContent) {

// 	std::vector<std::string> splitJoin;
// 	std::vector<std::string> tmp;
// 	std::vector<std::string>::iterator it;

// 	for (it = vectorContent.begin(); it != vectorContent.end(); it++) {
// 		tmp = getChannelVector(*it);
// 		splitJoin.insert(splitJoin.end(), tmp.begin(), tmp.end());
// 	}
// 	return splitJoin;
// }

static std::map<std::string, std::string> createPair(std::vector<std::string> args) {
	
	std::vector<std::string> channelName;
	std::vector<std::string> password;
	std::map<std::string, std::string> pairs;

	channelName = splitArg(args.at(0));
	password = splitArg(args.at(1));

	std::vector<std::string>::iterator it;
	std::vector<std::string>::iterator ite;
	for (it = channelName.begin(); it != channelName.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
	for (it = password.begin(); it != password.end(); it++)
		std::cout << *it << " ";

	return pairs;
}

static bool isArgValid(Commands &command, std::vector<std::string> args) {
	
	if (args.size() < 1 || args.at(0).empty()) {
		displayError(ERR_NEEDMOREPARAMS, command);
		return false;
	} else if (args.at(0)[0] != '#' || args.at(0).size() < 2) {
		return false;
	}
 
	std::map<std::string, std::string> pairs = createPair(args);
	// channelName = splitJoin.at(0);
	// splitJoin.erase(splitJoin.begin());
	
	// if (splitJoin.size() == 1) {
	// 	password = splitJoin.at(1);
	// 	splitJoin.erase(splitJoin.begin());
	// }

	return true;
}

void	executeJoin(Commands & command) {

	// std::vector<std::string> splitJoin = splitMultiChannels(command.getArgSplit());

	if (!isArgValid(command, command.getArgSplit()))
		return;

	command.getServer().getChannelList().insert(std::pair<std::string, Channel *>(command.getArgSplit()[0], new Channel(command.getArgSplit()[0], "")));
	displayMessage(SERVER, ":" + command.getClient().getNickname() + " JOIN " + command.getArgSplit()[0]);
	sendMessage(command.getClient().getFD(), ":" + command.getClient().getNickname() + " JOIN " + command.getArgSplit()[0]);
	sendMessage(command.getClient().getFD(), command.getClient().getNickname() + " is joining the channel " + command.getArgSplit()[0]);
}
