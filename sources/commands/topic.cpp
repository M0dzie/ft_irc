/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <thmeyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:11:19 by msapin            #+#    #+#             */
/*   Updated: 2024/02/05 14:00:01 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands.hpp"

void	executeTopic(Commands & command) {
	if (!command.getClient().getRegister())
		return;
	else if (command.getArgSplit().size() < 1)
    	return (displayError(ERR_NEEDMOREPARAMS, command));
	else if (command.getArgSplit()[0][0] != '#') {
		std::cout << "ft_irc topic" << std::endl;
		return;
	}

	Client &client = command.getClient();
	Channel *channel = command.getServer().getChannelList()[command.getArgSplit()[0]];
	if (!channel->isAlreadyIn(client.getNickname()))
		return (displayErrorChannel(ERR_NOTONCHANNEL, client, *channel));
	else if (!channel->getClients()[&client])
		return (displayErrorChannel(ERR_CHANOPRIVSNEEDED, client, *channel));
	
	if (channel->getTopic().empty())
		displayRPL(RPL_NOTOPIC, client, *channel);
	else
		displayRPL(RPL_TOPIC, client, *channel);
}
