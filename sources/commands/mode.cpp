/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:06:01 by msapin            #+#    #+#             */
/*   Updated: 2024/02/13 18:17:22 by msapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands.hpp"

static bool isValidModeString(std::string const &string) {
	if (string[0] != '+' && string[0] != '-')
		return false;
	if (!std::isalpha(string[1]) || string[2])
		return false;
	if (!(string[1] == 'i' || string[1] == 't' || string[1] == 'k' ||
		string[1] == 'o' || string[1] == 'l'))
		return false;
	return true;
}

static bool isNumber(std::string const &string) {
	std::string::const_iterator it = string.begin();
	while (it != string.end() && std::isdigit(*it))
		it++;
	return it == string.end();
}

static void handlePass(std::vector<std::string> modeString, Client &client, Channel &channel) {
	if (modeString.size() == 1 && *modeString.begin() == RMVPASS) {
		channel.setPassword("");
		channel.setModes(PASS, false);
		channel.sendMessageToChannel(":localhost 300 " + client.getNickname() + " " + channel.getName() + " :Remove password successfully");
	} else if (modeString.size() == 2 && !modeString[1].empty() && *modeString.begin() == PASS) {
		channel.setPassword(modeString[1]);
		channel.setModes(PASS, true);
		channel.sendMessageToChannel(":localhost 300 " + client.getNickname() + " " + channel.getName() + " :Set password successfully : " + modeString[1]);
	} else
		sendMessage(client.getFD(), ":localhost 300 " + client.getNickname() + " " + channel.getName() + " :Invalid arguments");
}

static void handleInviteOnly(std::vector<std::string> modeString, Client &client, Channel &channel) {
	if (modeString.size() == 1 && *modeString.begin() == RMVINVITEONLY) {
		channel.setInviteOnlyMode(false);
		channel.setModes(INVITEONLY, false);
		channel.sendMessageToChannel(":localhost 300 " + client.getNickname() + " " + channel.getName() + " :Remove invite only successfully");
	} else if (modeString.size() == 1 && *modeString.begin() == INVITEONLY) {
		channel.setInviteOnlyMode(true);
		channel.setModes(INVITEONLY, true);
		channel.sendMessageToChannel(":localhost 300 " + client.getNickname() + " " + channel.getName() + " :Set invite only successfully");
	} else
		sendMessage(client.getFD(), ":localhost 300 " + client.getNickname() + " " + channel.getName() + " :Invalid arguments");
}

static void handleTopicRestrict(std::vector<std::string> modeString, Client &client, Channel &channel) {
	if (modeString.size() == 1 && *modeString.begin() == RMVTOPICRESTRICT) {
		channel.setTopicRestrict(false);
		channel.setModes(TOPICRESTRICT, false);
		channel.sendMessageToChannel(":localhost 300 " + client.getNickname() + " " + channel.getName() + " :Remove topic restriction successfully");
	} else if (modeString.size() == 1 && *modeString.begin() == TOPICRESTRICT) {
		channel.setTopicRestrict(true);
		channel.setModes(TOPICRESTRICT, true);
		channel.sendMessageToChannel(":localhost 300 " + client.getNickname() + " " + channel.getName() + " :Set topic restriction successfully");
	} else
		sendMessage(client.getFD(), ":localhost 300 " + client.getNickname() + " " + channel.getName() + " :Invalid arguments");
}

static void handleOpeChan(std::vector<std::string> modeString, Client &client, Channel &channel) {
	if (modeString.size() != 2) {
		sendMessage(client.getFD(), ":localhost 300 " + client.getNickname() + " " + channel.getName() + " :Invalid arguments");
		return;
	}
	
	std::map<Client *, bool>::iterator it = channel.getClients().begin();
    std::map<Client *, bool>::iterator ite = channel.getClients().end();
	Client *target = NULL;
	while (it != ite) {
		if (it->first->getNickname() == modeString[1]) {
			target = it->first;
			break;
		}
		it++;
	}
	if (!target)
		return (channel.displayErrorTarget(ERR_USERNOTINCHANNEL, client, modeString[1]));
	
	if (modeString.size() == 2 && *modeString.begin() == RMVOPECHAN) {
		if (channel.unsetOperator(target)) {
			channel.displayClientList();
			channel.sendMessageToChannel(":localhost 300 " + client.getNickname() + " " + channel.getName() + " :Remove " + target->getNickname() + " from operators successfully");
		}
	} else if (modeString.size() == 2 && *modeString.begin() == OPECHAN) {
		if (channel.setOperator(target)) {
			channel.displayClientList();
			channel.sendMessageToChannel(":localhost 300 " + client.getNickname() + " " + channel.getName() + " :Set " + target->getNickname() + " operator successfully");
		}
	} else
		sendMessage(client.getFD(), ":localhost 300 " + client.getNickname() + " " + channel.getName() + " :Invalid arguments");
}

static void handleChanLimit(std::vector<std::string> modeString, Client &client, Channel &channel) {
	if (modeString.size() == 1 && *modeString.begin() == RMVCHANLIMIT) {
		channel.setChannelLimited(false);
		channel.setModes(CHANLIMIT, false);
		channel.sendMessageToChannel(":localhost 300 " + client.getNickname() + " " + channel.getName() + " :Remove channel limit successfully");
	} else if (modeString.size() == 2 && *modeString.begin() == CHANLIMIT) {
		if (!isNumber(modeString[1]))
			sendMessage(client.getFD(), ":localhost 300 " + client.getNickname() + " " + channel.getName() + " :Invalid arguments");
		else {
			std::stringstream ss(modeString[1]);
			unsigned long limit;
			ss >> limit;
			channel.setChannelLimited(true);
			channel.setChannelLimit(limit);
			channel.setModes(CHANLIMIT, true);
			channel.sendMessageToChannel(":localhost 300 " + client.getNickname() + " " + channel.getName() + " :Set channel limit to " + modeString[1] + " successfully");
		}
	} else
		sendMessage(client.getFD(), ":localhost 300 " + client.getNickname() + " " + channel.getName() + " :Invalid arguments");
}


static void splitModes(std::vector<std::string> modeString, Client &client, Channel &channel) {
	std::string modes[10] = {PASS, RMVPASS, INVITEONLY, RMVINVITEONLY, TOPICRESTRICT, RMVTOPICRESTRICT, OPECHAN, RMVOPECHAN, CHANLIMIT, RMVCHANLIMIT};
	void (*arrayFunction[])(std::vector<std::string>, Client &, Channel &) = {handlePass, handleInviteOnly, handleTopicRestrict, handleOpeChan, handleChanLimit};
	int i = -1;
	
	while (++i < 10)
	{
		if (i < 9 && (modes[i] == *modeString.begin() || modes[i + 1] == *modeString.begin()))
		{
			int tmpI = i / 2;
				(*arrayFunction[tmpI])(modeString, client, channel);
			break;
		}
		i++;
	}
}

void	executeMode(Commands & command) {
	Client &client = command.getClient();
	
	if (!client.getRegister())
		return (client.displayError(ERR_NOTREGISTERED));
	if (command.getArgSplit().size() < 1)
    	return (command.displayError(ERR_NEEDMOREPARAMS));

	Server &server = command.getServer();
	Channel *channel = server.getChannelList()[command.getArgSplit()[0]];
	if (!channel) {
		sendMessage(client.getFD(), ":localhost 403 " + client.getNickname() + " " + command.getArgSplit()[0] + " :No such channel");
		server.getChannelList().erase(command.getArgSplit()[0]);
		return;
	}
	if (command.getArgSplit().size() == 1)
		return (displayChannelRPL(RPL_CHANNELMODEIS, client, *channel));
	if (!isValidModeString(command.getArgSplit()[1]))
		return (sendMessage(client.getFD(), ":localhost 501 " + client.getNickname() + " " + channel->getName() + " :Unknown MODE flag"));
	if (!channel->getClients()[&client])
		return (channel->displayError(ERR_CHANOPRIVSNEEDED, client));

	// if everything good, split and setup modes
	std::vector<std::string> modes;
	std::copy(command.getArgSplit().begin() + 1, command.getArgSplit().end(), std::back_inserter(modes));
	splitModes(modes, client, *channel);
}
