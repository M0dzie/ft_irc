/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:47:09 by msapin            #+#    #+#             */
/*   Updated: 2024/01/24 16:47:01 by msapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands.hpp"

void	executeQuit(Commands & command) {
    (void)command;

    std::string quitMessage = *command.getArgSplit().begin();
	Client & tmpClient = command.getClient();
    std::string serverMessage = ":" + tmpClient.getNickname() + "!" + tmpClient.getUsername() + "@localhost" + " QUIT " + quitMessage;

	sendMessage(tmpClient.getFD(), serverMessage);
	displayMessage(SERVER, serverMessage);
}
