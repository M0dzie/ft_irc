/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 13:15:32 by msapin            #+#    #+#             */
/*   Updated: 2024/01/18 18:14:26 by msapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands.hpp"

void sendMessage(int clientFd, std::string msg) {
	msg += "\r\n";
	if (send(clientFd, msg.c_str(), msg.length(), 0) < 0)
		displayErrorMessage("send() failed.");
}

bool isNicknameValid(std::string nickname) {

	if (nickname[0] == '#')
		return false;
	return true;
}

void	executeNick(Commands & command) {

	(void)command;

	std::string nickname = *(command.getArgSplit().begin());
	std::string oldNickname = command.getClient().getNickname();

	if (isNicknameValid(nickname))
	{
		command.getClient().setNickname(nickname);
		// check if not first use of nick function
		if (!oldNickname.empty())
		{
			sendMessage(command.getClient().getFD(), ":" + oldNickname + " NICK " + nickname);
			displayMessage(SERVER, ":" + oldNickname + " NICK " + nickname);
		}
		// check if nick trigger login
		// login(command);
	}
}
