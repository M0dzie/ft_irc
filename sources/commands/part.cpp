/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 10:57:56 by thmeyer           #+#    #+#             */
/*   Updated: 2024/02/13 18:18:05 by msapin           ###   ########.fr       */
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
    Client *client = &command.getClient();
    
	if (!client->getRegister())
		return (client->displayError(ERR_NOTREGISTERED));
    if (command.getArgSplit().size() < 1)
    	return (command.displayError(ERR_NEEDMOREPARAMS));

    std::map<std::string, Channel *> channels = command.getServer().getChannelList();
    std::vector<std::string> channelNames = getChannelNames(command.getArgSplit()[0]);
    
    for (size_t i = 0; i < channelNames.size(); i++) {
        if (channels.find(channelNames[i]) == channels.end()) {
            sendMessage(client->getFD(), ":localhost 403 " + client->getNickname() + " " + channelNames[i] + " :No such channel");
            continue;
        }

        Channel* channel = channels[channelNames[i]];
        std::map<Client *, bool>::iterator it = channel->getClients().begin();
        std::map<Client *, bool>::iterator ite = channel->getClients().end();
        while (it != ite) {
            if (it->first == client) {
                std::vector<std::string>::iterator it = command.getArgSplit().begin() + 1;
                std::vector<std::string>::iterator ite = command.getArgSplit().end();
                std::vector<std::string> newVec(it, ite);
                channel->sendMessageToChannel(":" + client->getNickname() + "!" + client->getUsername() + "@localhost" + " PART " + channel->getName() + " :" + getReason(newVec));
                client->removeOneChannel(channel);
                channel->removeClient(client, command.getServer());
                break;
            }
            it++;
            
            if (it == ite)
                channel->displayError(ERR_NOTONCHANNEL, *client);
        }
    }
}