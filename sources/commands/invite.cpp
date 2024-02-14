/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:11:00 by msapin            #+#    #+#             */
/*   Updated: 2024/02/13 18:11:51 by msapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands.hpp"

static bool isIn(Channel &channel, std::string toFind) {
	if (std::find(channel.getInvitedList().begin(), channel.getInvitedList().end(), toFind) != channel.getInvitedList().end())
		return true;
	return false;
}

void	executeInvite(Commands & command) {
	Client &client = command.getClient();
	
	if (!client.getRegister())
		return (client.displayError(ERR_NOTREGISTERED));
	else if (command.getArgSplit().size() < 1)
		return (command.displayError(ERR_NEEDMOREPARAMS));
	Client &target = foundClient(command, command.getArgSplit()[0]);
	Channel *channel = command.getServer().getChannelList()[command.getArgSplit()[1]];

	// Check if conditions are true
	if (!channel) {
		std::string channelName = command.getArgSplit()[1];
		
		sendMessage(client.getFD(), ":localhost 403 " + client.getNickname() + " " + channelName + " :No such channel");
		command.getServer().getChannelList().erase(channelName);
		return;
	}
	if (!channel->getClients()[&client])
		return (channel->displayError(ERR_CHANOPRIVSNEEDED, client));
	if (client == target)
		return (sendMessage(client.getFD(), ":localhost 401 " + client.getNickname() + " " + command.getArgSplit()[0] + " :No such nick/channel"));
	if (!channel->isAlreadyIn(client.getNickname()))
		return (channel->displayError(ERR_NOTONCHANNEL, client));
	if (channel->isAlreadyIn(target.getNickname()))
		return (channel->displayErrorTarget(ERR_USERONCHANNEL, client, target.getNickname()));

	// If user and client exist and invite is possible, send a RPL_INVITING
	if (!isIn(*channel, target.getNickname()))
		channel->getInvitedList().push_back(target.getNickname());
	sendMessage(client.getFD(), ":localhost 341 " + client.getNickname() + " " + target.getNickname() + " " + channel->getName());
	sendMessage(target.getFD(), ":" + client.getNickname() + "!" + client.getUsername() + "@localhost" + " INVITE " + target.getNickname() + " " + channel->getName());
}
