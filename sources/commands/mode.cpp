/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <thmeyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:06:01 by msapin            #+#    #+#             */
/*   Updated: 2024/02/06 10:59:27 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands.hpp"

static bool isValidModeString(std::string string) {
	if (string.empty())
		return false;
	if (string[0] != '+' || string[0] != '-')
		return false;
	return true;
}

void	executeMode(Commands & command) {
	if (!command.getClient().getRegister())
		return;
	else if (command.getArgSplit().size() < 1)
    	return (displayError(ERR_NEEDMOREPARAMS, command));

	Client &client = command.getClient();
	Server &server = command.getServer();
	Channel *channel = server.getChannelList()[command.getArgSplit()[0]];
	if (!channel) {
		std::cout << PURPLE << BOLD << "Warning: " << RESET << client.getUsername() << " " << command.getArgSplit()[0] << " :No such channel" << std::endl;
		server.getChannelList().erase(command.getArgSplit()[0]);
		return;
	}
	for (size_t i = 1; i < command.getArgSplit().size(); i++)
		if (!isValidModeString(command.getArgSplit()[i]))
			return (displayRPL(RPL_CHANNELMODEIS, client, *channel));
}
