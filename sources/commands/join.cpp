/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <thmeyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 13:15:30 by msapin            #+#    #+#             */
/*   Updated: 2024/02/09 11:46:53 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands.hpp"

std::map<std::string, std::string> gPairs;

static std::vector<std::string> splitArg(std::string arg) {

	std::vector<std::string> tmpVector;
	std::string word;

	if (arg.find(',') != std::string::npos) {
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
	if (args.size() == 2)
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

static void joinChannel(Channel &channel, Client &client) {
	sendMessage(client.getFD(), ":" + client.getNickname() + "!" + client.getUsername() + "@localhost" + " JOIN " + channel.getName());
	channel.sendMessageToChannel(client.getNickname() + " is joining the channel " + channel.getName());
	if (channel.getTopic().empty())
		displayRPL(RPL_NOTOPIC, client, channel);
	else
		displayRPL(RPL_TOPIC, client, channel);
}

static void partAllChannels(Client &client, Server &server) {
	size_t size = client.getChannels().size();

	for (size_t i = 0; i < size; i++) {
		Channel * channel = *client.getChannels().begin();
		std::cout << channel->getName() << std::endl;
		sendMessage(client.getFD(), ":" + client.getNickname() + "!" + client.getUsername() + "@localhost" + " PART " + channel->getName() + " :Leaving");
		channel->sendMessageToChannel(client.getNickname() + " is leaving the channel " + channel->getName());
		client.removeOneChannel(channel);
		channel->removeClient(&client, server);
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
			
	if (command.getArgSplit()[0][0] == '0' && !command.getArgSplit()[0][1])
		return (partAllChannels(command.getClient(), command.getServer()), false);
 
	std::map<std::string, std::string>::iterator it = gPairs.begin();
	std::map<std::string, std::string>::iterator ite = gPairs.end();
	while (it != ite) {
		if (it->first[0] != '#' || it->first.size() < 2 || it->first.find('#', 1) != std::string::npos)
			return (gPairs.clear(), false);
		it++;
	}

	return true;
}

void	executeJoin(Commands & command) {

	if (!command.getClient().getRegister())
		return (displayError(ERR_NOTREGISTERED, command));

	if (!isArgValid(command, command.getArgSplit()))
		return;

	std::map<std::string, std::string>::iterator it = gPairs.begin();
	std::map<std::string, std::string>::iterator ite = gPairs.end();
	
	while (it != ite) {
		std::map<std::string, Channel *>::iterator channelIt = command.getServer().getChannelList().find(it->first);
		Client &client = command.getClient();
		
		if (channelIt == command.getServer().getChannelList().end()) {
			std::cout << PURPLE << BOLD << "Warning: " << RESET << client.getUsername() << " " << it->first << " :No such channel" << std::endl;
			command.getServer().getChannelList().insert(std::pair<std::string, Channel *>(it->first, new Channel(it->first, it->second)));
			Channel *channel = command.getServer().getChannelList()[it->first];
			channel->updateClients(&client, true);
			joinChannel(*channel, client);
			channel->displayClientList();
			client.addChannels(channel);
			if (!it->second.empty())
				channel->setModes(PASS, true);
			channel->setModes(TOPICRESTRICT, true);
			channel->setModes(CHANLIMIT, true);
			it++;
			continue;
		}

		Channel *channel = command.getServer().getChannelList()[it->first];
		if (channel->isAlreadyIn(client.getNickname())) {
			displayErrorChannelTarget(ERR_USERONCHANNEL, client, client.getNickname(), *channel);
			it++;
			continue;
		} else if (!channel->getPassword().empty() && it->second != channel->getPassword()) {
			displayErrorChannel(ERR_BADCHANNELKEY, client, *channel);
			it++;
			continue;
		} else if (channel->getChannelLimited() && channel->getClients().size() >= channel->getChannelLimit()) {
			displayErrorChannel(ERR_CHANNELISFULL, client, *channel);
			it++;
			continue;
		} else if (channel->getInviteOnly() && !channel->isInvited(client.getNickname())) {
			displayErrorChannel(ERR_INVITEONLYCHAN, client, *channel);
			it++;
			continue;
		}
		
		channel->updateClients(&client, false);
		joinChannel(*channel, client);
		channel->displayClientList();
		client.addChannels(channel);
		it++;
	}

	gPairs.clear();
}