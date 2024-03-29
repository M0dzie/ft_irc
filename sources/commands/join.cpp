/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 13:15:30 by msapin            #+#    #+#             */
/*   Updated: 2024/02/13 18:14:20 by msapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands.hpp"

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

static void createPair(std::vector<std::string> args, std::map<std::string, std::string> &pairs) {
	
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
			pairs.insert(std::pair<std::string, std::string>(*itCN, *itP));
			itP++;
		} else
			pairs.insert(std::pair<std::string, std::string>(*itCN, ""));
		itCN++;
	}
}

static void joinChannel(Channel &channel, Client &client) {
	sendMessage(client.getFD(), ":" + client.getNickname() + "!" + client.getUsername() + "@localhost" + " JOIN " + channel.getName());
	channel.sendMessageToChannel(client.getNickname() + " is joining the channel " + channel.getName());
	if (channel.getTopic().empty())
		displayChannelRPL(RPL_NOTOPIC, client, channel);
	else
		displayChannelRPL(RPL_TOPIC, client, channel);
}

static void partAllChannels(Client &client, Server &server) {
	size_t size = client.getChannels().size();

	for (size_t i = 0; i < size; i++) {
		Channel * channel = *client.getChannels().begin();
		sendMessage(client.getFD(), ":" + client.getNickname() + "!" + client.getUsername() + "@localhost" + " PART " + channel->getName() + " :Leaving");
		channel->sendMessageToChannel(client.getNickname() + " is leaving the channel " + channel->getName());
		client.removeOneChannel(channel);
		channel->removeClient(&client, server);
	}
}

static bool isArgValid(Commands &command, std::vector<std::string> args,std::map<std::string, std::string> &pairs) {
	
	if (args.size() > 2)
		return false;
	if (args.size() < 1 || args.at(0).empty())
		return command.displayError(ERR_NEEDMOREPARAMS), false;
	createPair(args, pairs);
			
	if (command.getArgSplit()[0][0] == '0' && !command.getArgSplit()[0][1])
		return (partAllChannels(command.getClient(), command.getServer()), false);
 
	std::map<std::string, std::string>::iterator it = pairs.begin();
	std::map<std::string, std::string>::iterator ite = pairs.end();
	while (it != ite) {
		if (it->first[0] != '#' || it->first.size() < 2 || it->first.find('#', 1) != std::string::npos)
			return (pairs.clear(), false);
		it++;
	}
	return true;
}

void	executeJoin(Commands & command) {
	Client &client = command.getClient();
	
	if (!client.getRegister())
		return (client.displayError(ERR_NOTREGISTERED));
	std::map<std::string, std::string> pairs;

	if (!isArgValid(command, command.getArgSplit(), pairs))
		return;
	std::map<std::string, std::string>::iterator it = pairs.begin();
	std::map<std::string, std::string>::iterator ite = pairs.end();
	
	while (it != ite) {
		std::map<std::string, Channel *>::iterator channelIt = command.getServer().getChannelList().find(it->first);
		
		if (channelIt == command.getServer().getChannelList().end()) {
			sendMessage(client.getFD(), ":localhost 403 " + client.getNickname() + " " + it->first + " :No such channel");
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
			channel->displayErrorTarget(ERR_USERONCHANNEL, client, client.getNickname());
			it++;
			continue;
		}
		if (!channel->getPassword().empty() && it->second != channel->getPassword()) {
			channel->displayError(ERR_BADCHANNELKEY, client);
			it++;
			continue;
		}
		if (channel->getChannelLimited() && channel->getClients().size() >= channel->getChannelLimit()) {
			channel->displayError(ERR_CHANNELISFULL, client);
			it++;
			continue;
		}
		if (channel->getInviteOnly() && !channel->isInvited(client.getNickname())) {
			channel->displayError(ERR_INVITEONLYCHAN, client);
			it++;
			continue;
		}
		channel->updateClients(&client, false);
		joinChannel(*channel, client);
		channel->displayClientList();
		client.addChannels(channel);
		it++;
	}
}
