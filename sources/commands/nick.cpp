/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 13:15:32 by msapin            #+#    #+#             */
/*   Updated: 2024/02/07 10:48:39 by msapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands.hpp"

void sendMessage(int clientFd, std::string msg) {
	msg += "\r\n";
	if (send(clientFd, msg.c_str(), msg.length(), 0) < 0)
		displayErrorMessage("send() failed.");
}

bool isNicknameValid(std::string nickname, Commands & command) {

	if (nickname[0] == '#' || nickname[0] == ':')
		return std::cout << RED << BOLD << "Error: " << RESET << command.getClient().getUsername() << " " << nickname << " :Erroneus nickname" << std::endl, false;
	else if (nickname == "undefined")
		return displayError(ERR_CANNOTBEUNDEFINED, command), false;
	return true;
}

bool isUseElsewhere(Commands & command, std::string nickname) {

	Server & tmpServer = command.getServer();
	std::map<int, Client *> tmpMap = tmpServer.getClientList();
	std::map<int, Client *>::iterator  it = tmpMap.begin();

	while (it != tmpMap.end())
	{
		if (it->second->getNickname() == nickname && it->second->getNickname() != "undefined")
			return true;
		it++;
	}
	return false;
}

void	executeNick(Commands & command) {

	std::string nickname = *(command.getArgSplit().begin());
	std::string oldNickname = command.getClient().getNickname();

	if (command.getClient().getPassword().empty())
		displayError(ERR_NOTREGISTERED, command);
	else if (isUseElsewhere(command, nickname))
		displayError(ERR_NICKNAMEINUSE, command);
	else if (isNicknameValid(nickname, command))
	{
		std::string cmdToSend = ":" + oldNickname + " NICK " + nickname;
		
		command.getClient().setNickname(nickname);
		sendMessage(command.getClient().getFD(), cmdToSend);
		displayMessage(SERVER, cmdToSend);
	}
}
