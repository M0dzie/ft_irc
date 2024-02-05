/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <thmeyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 13:15:30 by msapin            #+#    #+#             */
/*   Updated: 2024/02/05 16:36:49 by thmeyer          ###   ########.fr       */
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
			return (gPairs.clear(), false);
		it++;
	}

	return true;
}

static void joinChannel(Channel &channel, Client &client) {
	sendMessage(client.getFD(), ":" + client.getNickname() + "!" + client.getUsername() + "@localhost" + " JOIN " + channel.getName());
	channel.sendMessageToChannel(client.getNickname() + " is joining the channel " + channel.getName());
	if (channel.getTopic().empty())
		displayRPL(RPL_NOTOPIC, client, channel);
	else
		displayRPL(RPL_TOPIC, client, channel);
}

static void joinAllChannels(Client &client, Server &server) {
	std::map<std::string, Channel *>::iterator it = server.getChannelList().begin();
	std::map<std::string, Channel *>::iterator ite = server.getChannelList().end();

	while (it != ite) {
		Channel *channel = server.getChannelList()[it->first];
		if (channel->isAlreadyIn(client.getNickname())) {
			displayErrorChannel(ERR_USERONCHANNEL, client, *channel);
			it++;
			continue;
		} else if (!channel->getPassword().empty()) {
			displayErrorChannel(ERR_BADCHANNELKEY, client, *channel);
			it++;
			continue;
		} else if (channel->getClients().size() >= channel->getChannelLimit()) {
			displayErrorChannel(ERR_CHANNELISFULL, client, *channel);
			it++;
			continue;
		} else if (channel->getInviteOnly()) {
			displayErrorChannel(ERR_INVITEONLYCHAN, client, *channel);
			it++;
			continue;
		}
		
		server.getChannelList()[it->first]->updateClients(&client, false);
		joinChannel(*channel, client);
		server.getChannelList()[it->first]->displayClientList();
		it++;
	}
}

void	executeJoin(Commands & command) {

	if (!command.getClient().getRegister())
		return;

	if (command.getArgSplit()[0][0] == '0')
		return (joinAllChannels(command.getClient(), command.getServer()));

	if (!isArgValid(command, command.getArgSplit()))
		return;

	std::map<std::string, std::string>::iterator it = gPairs.begin();
	std::map<std::string, std::string>::iterator ite = gPairs.end();
	
	while (it != ite) {
		std::map<std::string, Channel *>::iterator channelIt = command.getServer().getChannelList().find(it->first);
		if (channelIt == command.getServer().getChannelList().end()) {
			std::cout << PURPLE << BOLD << "Warning: " << RESET << command.getClient().getUsername() << " " << it->first << " :No such channel" << std::endl;
			command.getServer().getChannelList().insert(std::pair<std::string, Channel *>(it->first, new Channel(it->first, it->second)));
			command.getServer().getChannelList()[it->first]->updateClients(&command.getClient(), true);
			joinChannel(*command.getServer().getChannelList()[it->first], command.getClient());
			command.getServer().getChannelList()[it->first]->displayClientList();
			it++;
			continue;
		}

		Channel *channel = command.getServer().getChannelList()[it->first];
		if (channel->isAlreadyIn(command.getClient().getNickname())) {
			displayErrorChannel(ERR_USERONCHANNEL, command.getClient(), *channel);
			it++;
			continue;
		} else if (!channel->getPassword().empty() && it->second != channel->getPassword()) {
			displayErrorChannel(ERR_BADCHANNELKEY, command.getClient(), *channel);
			it++;
			continue;
		} else if (channel->getClients().size() >= channel->getChannelLimit()) {
			displayErrorChannel(ERR_CHANNELISFULL, command.getClient(), *channel);
			it++;
			continue;
		} else if (channel->getInviteOnly()) {
			displayErrorChannel(ERR_INVITEONLYCHAN, command.getClient(), *channel);
			it++;
			continue;
		}
		
		command.getServer().getChannelList()[it->first]->updateClients(&command.getClient(), false);
		joinChannel(*command.getServer().getChannelList()[it->first], command.getClient());
		command.getServer().getChannelList()[it->first]->displayClientList();
		it++;
	}

	gPairs.clear();
}