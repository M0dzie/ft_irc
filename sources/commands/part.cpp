/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <thmeyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 10:57:56 by thmeyer           #+#    #+#             */
/*   Updated: 2024/02/02 11:29:26 by thmeyer          ###   ########.fr       */
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

    // Channel* channel = channels[channelName];
    // Client client = command.getClient();
    
}