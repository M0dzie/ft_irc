/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 13:15:32 by msapin            #+#    #+#             */
/*   Updated: 2024/02/13 18:47:31 by msapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands.hpp"

static bool isNicknameValid(std::string nickname, Client & client) {
	if (nickname[0] == '#' || nickname[0] == ':')
		return sendMessage(client.getFD(), ":localhost 432 " + client.getNickname() + " " + nickname + " :Erroneus nickname"), false;
	return true;
}

static bool isUseElsewhere(Commands & command, std::string nickname) {
	Server & tmpServer = command.getServer();
	std::map<int, Client *> & tmpMap = tmpServer.getClientList();
	std::map<int, Client *>::iterator  it = tmpMap.begin();

	while (it != tmpMap.end())
	{
		if (it->second->getNickname() == nickname && !it->second->getNickname().empty() && command.getClient().getNickname() != nickname)
			return true;
		it++;
	}
	return false;
}

void	executeNick(Commands & command) {
	if (command.getArgSplit().size() < 1)
    	return (command.displayError(ERR_NEEDMOREPARAMS));
	std::string nickname = *(command.getArgSplit().begin());
	Client & client = command.getClient();
	std::string oldNickname = client.getNickname();

	if (isUseElsewhere(command, nickname))
	{
		if (oldNickname.empty())
			oldNickname = "undefined";
		sendMessage(client.getFD(), ":localhost 433 " + oldNickname + " " + nickname + " :Nickname is already in use");
		client.setNickname(nickname);
		client.setValidNick(false);
	}
	else if (isNicknameValid(nickname, client))
	{
		if (oldNickname.empty())
			oldNickname = nickname;
		std::string cmdToSend = ":" + oldNickname + "!" + client.getUsername() + "@localhost NICK " + nickname;

		sendMessage(client.getFD(), cmdToSend);
		client.setNickname(nickname);
		client.setValidNick(true);
	}
	if (client.getRegister())
	{
		std::vector<Channel *> tmpChannels = client.getChannels();

		for (std::vector<Channel *>::iterator it = tmpChannels.begin(); it != tmpChannels.end(); it++)
			(*it)->displayClientList();
	}
	else
		login(command);
}
