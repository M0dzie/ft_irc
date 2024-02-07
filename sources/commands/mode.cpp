/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <thmeyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:06:01 by msapin            #+#    #+#             */
/*   Updated: 2024/02/07 14:55:34 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands.hpp"

static bool isValidModeString(std::string const &string) {
	if (string[0] != '+' && string[0] != '-')
		return false;
	if (!std::isalpha(string[1]))
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
		displayMessage(INFO, "Remove password successfully");
	} else if (modeString.size() == 2 && !modeString[1].empty() && *modeString.begin() == PASS) {
		channel.setPassword(modeString[1]);
		channel.setModes(PASS, true);
		displayMessage(INFO, "Set password successfully : " + modeString[1]);
	} else
		std::cout << PURPLE << BOLD << "Warning: " << RESET << client.getUsername() << " " << modeString[0] << " :Wrong parameters" << std::endl;
}

static void handleInviteOnly(std::vector<std::string> modeString, Client &client, Channel &channel) {
	if (modeString.size() == 1 && *modeString.begin() == RMVINVITEONLY) {
		channel.setInviteOnlyMode(false);
		channel.setModes(INVITEONLY, false);
		displayMessage(INFO, "Remove invite only successfully");
	} else if (modeString.size() == 1 && *modeString.begin() == INVITEONLY) {
		channel.setInviteOnlyMode(true);
		channel.setModes(INVITEONLY, true);
		displayMessage(INFO, "Set invite only successfully");
	} else
		std::cout << PURPLE << BOLD << "Warning: " << RESET << client.getUsername() << " " << modeString[0] << " :Wrong parameters" << std::endl;
}

static void handleTopicRestrict(std::vector<std::string> modeString, Client &client, Channel &channel) {
	if (modeString.size() == 1 && *modeString.begin() == RMVTOPICRESTRICT) {
		channel.setTopicRestrict(false);
		channel.setModes(TOPICRESTRICT, false);
		displayMessage(INFO, "Remove topic restriction successfully");
	} else if (modeString.size() == 1 && *modeString.begin() == TOPICRESTRICT) {
		channel.setTopicRestrict(true);
		channel.setModes(TOPICRESTRICT, true);
		displayMessage(INFO, "Set topic restriction successfully");
	} else
		std::cout << PURPLE << BOLD << "Warning: " << RESET << client.getUsername() << " " << modeString[0] << " :Wrong parameters" << std::endl;
}

static void handleOpeChan(std::vector<std::string> modeString, Client &client, Channel &channel) {
	if (modeString.size() != 2) {
			std::cout << PURPLE << BOLD << "Warning: " << RESET << client.getUsername() << " " << modeString[0] << " :Wrong parameters" << std::endl;
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
		return (displayErrorChannel(ERR_USERNOTINCHANNEL, client, channel));
	
	if (modeString.size() == 2 && *modeString.begin() == RMVOPECHAN) {
		if (channel.unsetOperator(target)) {
			channel.displayClientList();
			displayMessage(INFO, "Remove " + target->getNickname() + " from operators successfully");
		}
	} else if (modeString.size() == 2 && *modeString.begin() == OPECHAN) {
		if (channel.setOperator(target)) {
			channel.displayClientList();
			displayMessage(INFO, "Set " + target->getNickname() + " operator successfully");
		}
	} else
		std::cout << PURPLE << BOLD << "Warning: " << RESET << client.getUsername() << " " << modeString[0] << " :Wrong parameters" << std::endl;
}

static void handleChanLimit(std::vector<std::string> modeString, Client &client, Channel &channel) {
	if (modeString.size() == 1 && *modeString.begin() == RMVCHANLIMIT) {
		channel.setChannelLimited(false);
		channel.setModes(CHANLIMIT, false);
		displayMessage(INFO, "Remove channel limit successfully");
	} else if (modeString.size() == 2 && *modeString.begin() == CHANLIMIT) {
		if (!isNumber(modeString[1]))
			std::cout << PURPLE << BOLD << "Warning: " << RESET << client.getUsername() << " " << modeString[0] << " :Wrong parameters" << std::endl;
		std::stringstream ss(modeString[1]);
		unsigned long limit;
		ss >> limit;
		channel.setChannelLimited(true);
		channel.setChannelLimit(limit);
		channel.setModes(CHANLIMIT, true);
		displayMessage(INFO, "Set channel limit to " + modeString[1] + " successfully");
	} else
		std::cout << PURPLE << BOLD << "Warning: " << RESET << client.getUsername() << " " << modeString[0] << " :Wrong parameters" << std::endl;
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
	if (!command.getClient().getRegister())
		return;
	else if (command.getArgSplit().size() < 1)
    	return (displayError(ERR_NEEDMOREPARAMS, command));

	Client &client = command.getClient();
	Server &server = command.getServer();
	Channel *channel = server.getChannelList()[command.getArgSplit()[0]];
	if (!channel) {
		std::cout << PURPLE << BOLD << "Warning: " << RESET << client.getUsername() << " " << command.getArgSplit()[0] << " :No such channel" << std::endl;
		server.getChannelList().erase(command.getArgSplit()[0]);
		return;
	}
	if (command.getArgSplit().size() == 1 || !isValidModeString(command.getArgSplit()[1]))
		return (displayRPL(RPL_CHANNELMODEIS, client, *channel));
	if (!channel->getClients()[&client])
		return (displayErrorChannel(ERR_CHANOPRIVSNEEDED, client, *channel));

	// if everything good, split and setup modes
	std::vector<std::string> modes;
	std::copy(command.getArgSplit().begin() + 1, command.getArgSplit().end(), std::back_inserter(modes));
	splitModes(modes, client, *channel);
}
