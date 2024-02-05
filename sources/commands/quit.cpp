/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:47:09 by msapin            #+#    #+#             */
/*   Updated: 2024/02/05 11:53:15 by msapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands.hpp"

void	executeQuit(Commands & command) {
	(void)command;

	std::string quitMessage = *command.getArgSplit().begin();
	Client & tmpClient = command.getClient();
	std::string serverMessage = ":" + tmpClient.getNickname() + "!" + tmpClient.getUsername() + "@localhost" + " QUIT " + quitMessage;
	Server & tmpServer = command.getServer();
	(void)tmpServer;

	sendMessage(tmpClient.getFD(), serverMessage);
	displayMessage(SERVER, serverMessage);
	
	// std::cout << tmpServer.getNbClient() << std::endl;
	// tmpServer.setNbClient(tmpServer.getNbClient() - 1);
	// delete tmpServer.getClientList()[tmpClient.getFD()];
	// tmpServer.getClientList().erase(tmpClient.getFD());
	tmpServer.setFDValue(0, 1);
}
