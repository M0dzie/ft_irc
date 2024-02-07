/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <thmeyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 10:57:56 by thmeyer           #+#    #+#             */
/*   Updated: 2024/02/07 11:30:17 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands.hpp"

static std::vector<std::string> getChannelNames(std::string string) {
    std::vector<std::string> channelNames;

    while (string.find(',') != std::string::npos) {
        size_t index = string.find(',');
        channelNames.push_back(string.substr(0, index));
        string = string.substr(index + 1);
    }
    channelNames.push_back(string.substr(0, std::string::npos));
    return channelNames;
} 

void executePart(Commands & command) {
	if (!command.getClient().getRegister())
		return;
    
    if (command.getArgSplit().size() < 1)
    	return (displayError(ERR_NEEDMOREPARAMS, command));

    std::map<std::string, Channel *> channels = command.getServer().getChannelList();
    Client *client = &command.getClient();
    std::vector<std::string> channelNames = getChannelNames(command.getArgSplit()[0]);
    // std::string channelName = command.getArgSplit()[0];
    
    for (size_t i = 0; i < channelNames.size(); i++) {
        if (channels.find(channelNames[i]) == channels.end()) {
            std::cout << PURPLE << BOLD << "Warning: " << RESET << command.getClient().getUsername() << " " << channelNames[i] << " :No such channel" << std::endl;
            continue;
        }

        Channel* channel = channels[channelNames[i]];
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
                sendMessage(client->getFD(), ":" + client->getNickname() + "!" + client->getUsername() + "@localhost" + " PART " + channelNames[i] + " :" + reason);
                channel->sendMessageToChannel(client->getNickname() + " is leaving the channel " + channelNames[i]);
                client->removeOneChannel(channel);
                channel->removeClient(client, command.getServer());
                it++;
                continue;
            }
            it++;
            
            if (it == ite)
                displayErrorChannel(ERR_NOTONCHANNEL, *client, *channel);
        }
    }
}