/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <thmeyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:11:19 by msapin            #+#    #+#             */
/*   Updated: 2024/02/05 16:44:15 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands.hpp"

void	executeTopic(Commands & command) {
	if (!command.getClient().getRegister())
		return;
	else if (command.getArgSplit().size() < 1)
    	return (displayError(ERR_NEEDMOREPARAMS, command));
	else if (command.getArgSplit()[0][0] != '#')
		return;

	Client &client = command.getClient();
	Channel *channel = command.getServer().getChannelList()[command.getArgSplit()[0]];
	if (!channel->isAlreadyIn(client.getNickname()))
		return (displayErrorChannel(ERR_NOTONCHANNEL, client, *channel));
	
	if (command.getArgSplit().size() == 1) {
		if (channel->getTopic().empty())
			displayRPL(RPL_NOTOPIC, client, *channel);
		else
			displayRPL(RPL_TOPIC, client, *channel);
		return;
	}

	if (!channel->getClients()[&client])
		return (displayErrorChannel(ERR_CHANOPRIVSNEEDED, client, *channel));
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

	for (std::map<Client *, bool>::iterator it = channel->getClients().begin(); it != channel->getClients().end(); it++) {
		if (channel->getTopic().empty())
			displayRPL(RPL_NOTOPIC, *it->first, *channel);
		else
			displayRPL(RPL_TOPIC, *it->first, *channel);
	}
}
