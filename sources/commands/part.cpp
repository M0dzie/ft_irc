/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <thmeyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 10:57:56 by thmeyer           #+#    #+#             */
/*   Updated: 2024/02/05 15:39:51 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands.hpp"

void	executePart(Commands & command) {
	if (!command.getClient().getRegister())
		return;
    
    if (command.getArgSplit().size() < 1)
    	return (displayError(ERR_NEEDMOREPARAMS, command));

    std::map<std::string, Channel *> channels = command.getServer().getChannelList();
    std::string channelName = command.getArgSplit()[0];
    if (channels.find(channelName) == channels.end())
        return (displayError(ERR_NOSUCHCHANNEL, command));

    Channel* channel = channels[channelName];
    Client *client = &command.getClient();
    std::map<Client *, bool>::iterator it = channel->getClients().begin();
    std::map<Client *, bool>::iterator ite = channel->getClients().end();
    while (it != ite) {
        if (it->first == client) {
            std::string reason;
            for (size_t i = 1; i < command.getArgSplit().size(); i++) {
                reason += command.getArgSplit()[i];
                if (i != command.getArgSplit().size() - 1)
				    reason += " ";
            }
            reason = reason.substr(1);
            sendMessage(client->getFD(), ":" + client->getNickname() + "!" + client->getUsername() + "@localhost" + " PART " + channelName + " :" + reason);
            channel->sendMessageToChannel(client->getNickname() + " is leaving the channel " + channelName);
            channel->removeClient(client, command.getServer());
            return;
        }
        it++;
    }
    displayErrorChannel(ERR_NOTONCHANNEL, *client, *channel);
}