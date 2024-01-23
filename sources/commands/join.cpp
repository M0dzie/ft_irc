/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <thmeyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 13:15:30 by msapin            #+#    #+#             */
/*   Updated: 2024/01/23 18:01:53 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands.hpp"

std::map<std::string, std::string> gPairs;

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

static void createPair(std::vector<std::string> args) {
	
	std::vector<std::string> channelName;
	std::vector<std::string> password;

	channelName = splitArg(args.at(0));
	password = splitArg(args.at(1));

	std::vector<std::string>::iterator itCN = channelName.begin();
	std::vector<std::string>::iterator iteCN = channelName.end();
	std::vector<std::string>::iterator itP = password.begin();
	std::vector<std::string>::iterator iteP = password.end();

	while (itCN != iteCN) {
		if (itP != iteP) {
			gPairs.insert(std::pair<std::string, std::string>(*itCN, *itP));
			itP++;
		} else
			gPairs.insert(std::pair<std::string, std::string>(*itCN, ""));
		itCN++;
	}
}

static bool isArgValid(Commands &command, std::vector<std::string> args) {
	
	if (args.size() > 2)
		return false;
	if (args.size() < 1 || args.at(0).empty()) {
		displayError(ERR_NEEDMOREPARAMS, command);
		return false;
	}

	createPair(args);
 
	std::map<std::string, std::string>::iterator it = gPairs.begin();
	std::map<std::string, std::string>::iterator ite = gPairs.end();
	while (it != ite) {
		if (it->first[0] != '#' || it->first.size() < 2 || it->first.find('#', 1) != std::string::npos)
			return false;
		it++;
	}

	return true;
}

void	executeJoin(Commands & command) {

	if (!isArgValid(command, command.getArgSplit()))
		return;

	// command.getServer().getChannelList().insert(std::pair<std::string, Channel *>(command.getArgSplit()[0], new Channel(command.getArgSplit()[0], "")));
	// displayMessage(SERVER, ":" + command.getClient().getNickname() + " JOIN " + command.getArgSplit()[0]);
	// sendMessage(command.getClient().getFD(), ":" + command.getClient().getNickname() + " JOIN " + command.getArgSplit()[0]);
	// sendMessage(command.getClient().getFD(), command.getClient().getNickname() + " is joining the channel " + command.getArgSplit()[0]);
}
