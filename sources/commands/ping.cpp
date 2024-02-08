/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <thmeyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 16:03:54 by msapin            #+#    #+#             */
/*   Updated: 2024/02/08 11:21:39 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands.hpp"

void	executePing(Commands & command) {

	if (!command.getClient().getRegister())
		displayError(ERR_NOTREGISTERED, command);
	else
	{
		std::string tmpPing = *command.getArgSplit().begin();
		Client & tmpClient = command.getClient();
		std::string serverMessage = ":" + tmpClient.getNickname() + "!" + tmpClient.getUsername() + "@localhost" + " PONG " + tmpPing;

		sendMessage(tmpClient.getFD(), serverMessage);
		// displayMessage(SERVER, serverMessage);
	}
}
