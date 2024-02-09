/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 16:03:54 by msapin            #+#    #+#             */
/*   Updated: 2024/02/09 15:39:08 by msapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands.hpp"

void	executePing(Commands & command) {
	if (!command.getClient().getRegister())
		displayError(ERR_NOTREGISTERED, command);
	else if (command.getArgSplit().size() < 1)
    	displayError(ERR_NEEDMOREPARAMS, command);
	else
	{
		std::string tmpPing = *command.getArgSplit().begin();
		Client & tmpClient = command.getClient();
		std::string serverMessage = ":" + tmpClient.getNickname() + "!" + tmpClient.getUsername() + "@localhost" + " PONG " + tmpPing;

		sendMessage(tmpClient.getFD(), serverMessage);
		// displayMessage(SERVER, serverMessage);
	}
}
