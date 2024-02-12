/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 12:42:52 by msapin            #+#    #+#             */
/*   Updated: 2024/02/12 18:52:04 by msapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands.hpp"

void	executePass(Commands & command);
void	executeJoin(Commands & command);
void	executeNick(Commands & command);
void	executeUser(Commands & command);
void	executePing(Commands & command);
void	executeQuit(Commands & command);
void	executePrivateMsg(Commands & command);
void	executeInvite(Commands & command);
void	executeKick(Commands & command);
void	executeMode(Commands & command);
void	executeTopic(Commands & command);
void	executePart(Commands & command);

Commands::Commands(std::string & line, Client & client, Server & server) : _client(client),  _server(server) {

	std::stringstream streamLine(line);
	std::string word;

	streamLine >> this->_name;
	while (streamLine >> word)
	{
		this->_argSplit.push_back(word);
	}
}

static bool ignoreCommand(std::string & cmdName) {
	
	std::string commandToIgnore[] = {"WHO", "CAP"};

	for (unsigned int i = 0; i < 2; i++)
	{
		if (commandToIgnore[i] == cmdName)
			return true;
	}
	return false;
}

int Commands::executeCommand() {

	std::string arrayCommand[12] = {"PASS", "NICK", "USER", "JOIN", "PING", "QUIT", "PRIVMSG", "INVITE", "KICK", "MODE", "TOPIC", "PART"};
	void (*arrayFunction[])(Commands &) = {executePass, executeNick, executeUser, executeJoin, executePing, executeQuit, executePrivateMsg, executeInvite, executeKick, executeMode, executeTopic, executePart};
	unsigned int i = -1;
	
	if (!ignoreCommand(this->_name))
	{
		while (++i < 12)
		{
			if (arrayCommand[i] == this->_name)
			{
				(*arrayFunction[i])(*this);
				break;
			}
		}
		Client & tmpClient = this->getClient();
		
		if (i == 12)
		{
			if (!tmpClient.getRegister())
				sendMessage(tmpClient.getFD(), ":localhost 451 " + tmpClient.getNickname() + " :You have not registered");
			else
				sendMessage(tmpClient.getFD(), ":localhost 421 " + tmpClient.getNickname() + " " + this->_name + " :Unknown command");
		}
	}
	if (i == 5)
		return 0;
	return 1;
}

void login(Commands & command) {

	Client & tmpClient = command.getClient();
	bool isRegistered = tmpClient.getRegister();
	const std::string & password = tmpClient.getPassword();

	if (isRegistered)
		displayError(ERR_ALREADYREGISTERED, command);
	else if (password.empty())
		// displayError(ERR_NOTREGISTERED, command);
		tmpClient.displayErrorClient(ERR_NOTREGISTERED);
	else if (password != command.getServer().getPassword())
		displayError(ERR_PASSWDMISMATCH, command);
	else
	{
		tmpClient.setRegister(true);
		sendMessage(tmpClient.getFD(), ":localhost 001 " + tmpClient.getNickname() + " :Welcome to your IRC Network!");
		sendMessage(tmpClient.getFD(), ":localhost 375 " + tmpClient.getNickname() + " :- ft_irc Message of the day - ");
		sendMessage(tmpClient.getFD(), ":localhost 372 " + tmpClient.getNickname() + " :                                          ");
		sendMessage(tmpClient.getFD(), ":localhost 372 " + tmpClient.getNickname() + " :  ███████╗████████╗    ██╗██████╗  ██████╗");
		sendMessage(tmpClient.getFD(), ":localhost 372 " + tmpClient.getNickname() + " :  ██╔════╝╚══██╔══╝    ██║██╔══██╗██╔════╝");
		sendMessage(tmpClient.getFD(), ":localhost 372 " + tmpClient.getNickname() + " :  █████╗     ██║       ██║██████╔╝██║     ");
		sendMessage(tmpClient.getFD(), ":localhost 372 " + tmpClient.getNickname() + " :  ██╔══╝     ██║       ██║██╔══██╗██║     ");
		sendMessage(tmpClient.getFD(), ":localhost 372 " + tmpClient.getNickname() + " :  ██║        ██║       ██║██║  ██║╚██████╗");
		sendMessage(tmpClient.getFD(), ":localhost 372 " + tmpClient.getNickname() + " :  ╚═╝        ╚═╝       ╚═╝╚═╝  ╚═╝ ╚═════╝");
		sendMessage(tmpClient.getFD(), ":localhost 372 " + tmpClient.getNickname() + " :                                          ");
		sendMessage(tmpClient.getFD(), ":localhost 376 " + tmpClient.getNickname() + " :End of /MOTD command.");
	}
}

std::string getReason(std::vector<std::string> argSplit) {
	std::string reason;
	
	if (argSplit.size() < 1)
		reason = "Leaving";
	else {
		for (size_t i = 0; i < argSplit.size(); i++) {
			reason += argSplit[i];
			if (i != argSplit.size() - 1)
				reason += " ";
		}
		if (reason[0] == ':')
			reason = reason.substr(1);
	}
	
	return reason;
}
