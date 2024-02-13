/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:11:19 by msapin            #+#    #+#             */
/*   Updated: 2024/02/13 17:59:40 by msapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands.hpp"

void	executeTopic(Commands & command) {
	Client &client = command.getClient();
	
	if (!client.getRegister())
		return (client.displayError(ERR_NOTREGISTERED));
	else if (command.getArgSplit().size() < 1)
    	return (command.displayError(ERR_NEEDMOREPARAMS));
	else if (command.getArgSplit()[0][0] != '#')
		return;

	Channel *channel = command.getServer().getChannelList()[command.getArgSplit()[0]];
	if (!channel) {
		sendMessage(client.getFD(), ":localhost 403 " + client.getNickname() + " " + command.getArgSplit()[0] + " :No such channel");
		command.getServer().getChannelList().erase(command.getArgSplit()[0]);
		return;
	} else if (!channel->isAlreadyIn(client.getNickname()))
		return (channel->displayError(ERR_NOTONCHANNEL, client));
	
	// Only display the topic
	if (command.getArgSplit().size() == 1) {
		if (channel->getTopic().empty())
			displayChannelRPL(RPL_NOTOPIC, client, *channel);
		else
			displayChannelRPL(RPL_TOPIC, client, *channel);
		return;
	}

	// Check if the client is an operator if topicRestriction is off
	if (channel->getTopicRestrict() && !channel->getClients()[&client])
		return (channel->displayError(ERR_CHANOPRIVSNEEDED, client));

	// Update topic
	std::string newTopic;
	if (command.getArgSplit()[1].empty() || (command.getArgSplit()[1][0] == ':' && command.getArgSplit()[1][1] == ':' && !command.getArgSplit()[1][2]))
		newTopic = "";
	else {
		for (size_t i = 1; i < command.getArgSplit().size(); i++) {
			newTopic += command.getArgSplit()[i];
			if (i != command.getArgSplit().size() - 1)
				newTopic += " ";
		}
		newTopic = newTopic.substr(1);
	}
	channel->setTopic(newTopic);

	// Display the change for every clients inside the channel
	for (std::map<Client *, bool>::iterator it = channel->getClients().begin(); it != channel->getClients().end(); it++) {
		if (channel->getTopic().empty())
			displayChannelRPL(RPL_NOTOPIC, *it->first, *channel);
		else
			displayChannelRPL(RPL_TOPIC, *it->first, *channel);
	}
}
