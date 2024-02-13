/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:11:19 by msapin            #+#    #+#             */
/*   Updated: 2024/02/13 12:40:27 by msapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands.hpp"

void	executeTopic(Commands & command) {
	if (!command.getClient().getRegister())
		return (displayError(ERR_NOTREGISTERED, command));
	else if (command.getArgSplit().size() < 1)
    	return (displayError(ERR_NEEDMOREPARAMS, command));
	else if (command.getArgSplit()[0][0] != '#')
		return;

	Client &client = command.getClient();
	Channel *channel = command.getServer().getChannelList()[command.getArgSplit()[0]];
	if (!channel) {
		std::cout << PURPLE << BOLD << "Warning: " << RESET << client.getUsername() << " " << command.getArgSplit()[0] << " :No such channel" << std::endl;
		command.getServer().getChannelList().erase(command.getArgSplit()[0]);
		return;
	} else if (!channel->isAlreadyIn(client.getNickname()))
		return (channel->displayError(ERR_NOTONCHANNEL, client));
		// return (displayErrorChannel(ERR_NOTONCHANNEL, client, *channel));
	
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
		// return (displayErrorChannel(ERR_CHANOPRIVSNEEDED, client, *channel));

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
