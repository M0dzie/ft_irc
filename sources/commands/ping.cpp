/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 16:03:54 by msapin            #+#    #+#             */
/*   Updated: 2024/01/22 15:29:34 by msapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands.hpp"

void	executePing(Commands & command) {

	std::string tmpPing = *command.getArgSplit().begin();
	Client & tmpClient = command.getClient();
	std::string serverMessage = ":" + tmpClient.getNickname() + "!" + tmpClient.getUsername() + "@localhost" + " PONG " + tmpPing;

	sendMessage(tmpClient.getFD(), serverMessage);
	displayMessage(SERVER, serverMessage);
}
