/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 12:42:52 by msapin            #+#    #+#             */
/*   Updated: 2024/02/01 17:08:36 by msapin           ###   ########.fr       */
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

Commands::Commands(std::string & line, Client & client, Server & server) : _client(client),  _server(server) {

	std::stringstream streamLine(line);
	std::string word;

	streamLine >> this->_name;
	while (streamLine >> word)
	{
		this->_argSplit.push_back(word);
	}
}

Commands::~Commands(void) {

	// std::cout << "Delete Commands " << std::endl;
}

void login(Commands & command) {

	Client & tmpClient = command.getClient();
	bool isRegistered = tmpClient.getRegister();
	const std::string & password = tmpClient.getPassword();

	if (isRegistered)
		displayError(ERR_ALREADYREGISTERED, command);
	else if (password.empty())
		displayError(ERR_NOTREGISTERED, command);
	else if (password != command.getServer().getPassword())
		displayError(ERR_PASSWDMISMATCH, command);
	else
	{
		tmpClient.setRegister(true);
		sendMessage(tmpClient.getFD(), ":localhost 376 " + tmpClient.getUsername() + " :" + tmpClient.getUsername() + " connected!");
	}
}

bool ignoreCommand(std::string & cmdName) {
	
	std::string commandToIgnore[] = {"WHO", "CP"};

	for (unsigned int i = 0; i < commandToIgnore->length(); i++)
	{
		if (commandToIgnore[i] == cmdName)
			return true;
	}
	return false;
}

void Commands::executeCommand() {

	std::string arrayCommand[11] = {"PASS", "NICK", "USER", "JOIN", "PING", "QUIT", "PRIVMSG", "INVITE", "KICK", "MODE", "TOPIC"};
	void (*arrayFunction[])(Commands &) = {executePass, executeNick, executeUser, executeJoin, executePing, executeQuit, executePrivateMsg, executeInvite, executeKick, executeMode, executeTopic};
	unsigned int i = -1;
	
	if (!ignoreCommand(this->_name))
	{
		// for (unsigned int i = 0; i < arrayCommand->size(); i++)
		while (++i < 11)
		{
			if (arrayCommand[i] == this->_name)
			{
				(*arrayFunction[i])(*this);
				break;
			}
		}
		if (i == 11)
			std::cout << "command not found " << i << " " << 7 << std::endl;	
	}
}
