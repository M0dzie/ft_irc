/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 12:42:52 by msapin            #+#    #+#             */
/*   Updated: 2024/02/13 18:07:00 by msapin           ###   ########.fr       */
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

void	Commands::displayError(int errorCode) {
	
	switch (errorCode)
	{
		case ERR_NEEDMOREPARAMS:
			sendMessage(this->_client.getFD(), ":localhost 461 " + this->_client.getNickname() + " " + this->_name + " :Not enough parameters");
			break;
		case ERR_INVALIDARG:
			sendMessage(this->_client.getFD(), ":localhost " + this->_client.getNickname() + " " + this->_name + " :Invalid arguments");
			
			break;
		default:
			break;
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

	Client & client = command.getClient();
	const std::string & password = client.getPassword();

	if (client.getRegister())
		client.displayError(ERR_ALREADYREGISTERED);
	else if (password.empty() || client.getUsername().empty() || client.getNickname().empty())
		client.displayError(ERR_NOTREGISTERED);
	else if (password != command.getServer().getPassword())
		client.displayError(ERR_PASSWDMISMATCH);
	else
	{
		client.setRegister(true);
		displayRPL(RPL_WELCOME, client);
		displayRPL(RPL_MOTDSTART, client);
		displayRPL(RPL_MOTD, client);
		displayRPL(RPL_ENDOFMOTD, client);
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
