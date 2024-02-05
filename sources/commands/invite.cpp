/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <thmeyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:11:00 by msapin            #+#    #+#             */
/*   Updated: 2024/02/05 19:01:25 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands.hpp"

static bool isIn(Channel &channel, std::string toFind) {
	if (std::find(channel.getInvitedList().begin(), channel.getInvitedList().end(), toFind) != channel.getInvitedList().end())
		return true;
	return false;
}

void	executeInvite(Commands & command) {
	if (!command.getClient().getRegister())
		return;
	else if (command.getArgSplit().size() < 1)
    	return (displayError(ERR_NEEDMOREPARAMS, command));

	Client &client = command.getClient();
	Client &target = foundClient(command, command.getArgSplit()[0]);
	Channel *channel = command.getServer().getChannelList()[command.getArgSplit()[1]];

	// Check if conditions are true
	if (!channel) {
		std::cout << PURPLE << BOLD << "Warning: " << RESET << client.getUsername() << " " << command.getArgSplit()[1] << " :No such channel" << std::endl;
		return;
	} else if (client == target) {
		std::cout << PURPLE << BOLD << "Warning: " << RESET << client.getUsername() << " " << command.getArgSplit()[0] << " :didn't exist" << std::endl;
		return;
	} else if (!channel->isAlreadyIn(client.getNickname()))
		return (displayErrorChannel(ERR_NOTONCHANNEL, client, *channel));
	else if (!channel->getClients()[&client] || (channel->getInviteOnly() && !channel->getClients()[&client]))
		return (displayErrorChannel(ERR_CHANOPRIVSNEEDED, client, *channel));
	else if (channel->isAlreadyIn(target.getNickname()))
		return (displayErrorChannel(ERR_USERONCHANNEL, client, *channel));

	// If user and client exist and invite is possible, send a RPL_INVITING
	if (!isIn(*channel, target.getNickname()))
		channel->getInvitedList().push_back(target.getNickname());
	sendMessage(client.getFD(), ":localhost 341 " + client.getNickname() + " " + target.getNickname() + " " + channel->getName());
	sendMessage(target.getFD(), ":" + client.getNickname() + "!" + client.getUsername() + "@localhost" + " INVITE " + target.getNickname() + " " + channel->getName());
}
