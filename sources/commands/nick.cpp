/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 13:15:32 by msapin            #+#    #+#             */
/*   Updated: 2024/01/23 14:17:49 by msapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands.hpp"

void sendMessage(int clientFd, std::string msg) {
	msg += "\r\n";
	if (send(clientFd, msg.c_str(), msg.length(), 0) < 0)
		displayErrorMessage("send() failed.");
}

bool isNicknameValid(std::string nickname, Commands & command) {

	if (nickname[0] == '#')
		return false;
	else if (nickname == "undefined")
		return displayError(ERR_CANNOTBEUNDEFINED, command), false;
	return true;
}

void	executeNick(Commands & command) {

	std::string nickname = *(command.getArgSplit().begin());
	std::string oldNickname = command.getClient().getNickname();

	if (!command.getClient().getPassValidate())
		displayError(ERR_NOTREGISTERED, command);
	else if (isNicknameValid(nickname, command))
	{
		command.getClient().setNickname(nickname);
		// check if not first use of nick function
		if (oldNickname != "undefined")
		{
			sendMessage(command.getClient().getFD(), ":" + oldNickname + " NICK " + nickname);
			displayMessage(SERVER, ":" + oldNickname + " NICK " + nickname);
		}
	}
}
