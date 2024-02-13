/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 16:03:54 by msapin            #+#    #+#             */
/*   Updated: 2024/02/13 18:18:50 by msapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands.hpp"

void	executePing(Commands & command) {
	Client & client = command.getClient();
	
	if (!client.getRegister())
		client.displayError(ERR_NOTREGISTERED);
	else if (command.getArgSplit().size() < 1)
    	command.displayError(ERR_NEEDMOREPARAMS);
	else
	{
		std::string tmpPing = *command.getArgSplit().begin();
		std::string serverMessage = ":" + client.getNickname() + "!" + client.getUsername() + "@localhost" + " PONG " + tmpPing;
		sendMessage(client.getFD(), serverMessage);
	}
}
