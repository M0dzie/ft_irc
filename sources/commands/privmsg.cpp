/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 13:47:46 by msapin            #+#    #+#             */
/*   Updated: 2024/01/25 15:15:25 by msapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands.hpp"

Client & foundClient(Commands & command, std::string nickname) {

    Server & tmpServer = command.getServer();
    std::cout << "looking for " << nickname << std::endl;

    return command.getClient();
}

void	executePrivateMsg(Commands & command) {

	std::string tmpTarget = *command.getArgSplit().begin();
	Client & tmpClient = command.getClient();

    Client & tmpReceiver = foundClient(command, tmpTarget);
    (void)tmpTarget;
    (void)tmpClient;
    (void)tmpReceiver;
	// std::string serverMessage = ":" + tmpClient.getNickname() + "!" + tmpClient.getUsername() + "@localhost" + " PONG " + tmpPing;
	// std::string serverMessageSender = ":" + tmpTarget + " PRIVMSG " + tmpClient.getNickname() + " :Hello are you receiving this message ?";
	// std::string serverMessageReceiver = ":" + tmpClient.getNickname() + " PRIVMSG " + tmpTarget + " :Hello are you receiving this message ?";

    // // get fd of the client receiver
	// sendMessage(tmpClient.getFD(), serverMessageReceiver);
	// sendMessage(5, serverMessageReceiver);
	// // displayMessage(SERVER, serverMessageSender);
}
