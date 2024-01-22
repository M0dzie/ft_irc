/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 12:42:52 by msapin            #+#    #+#             */
/*   Updated: 2024/01/22 17:36:52 by msapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands.hpp"

void	executePass(Commands & command);
void	executeJoin(Commands & command);
void	executeNick(Commands & command);
void	executeUser(Commands & command);
void	executePing(Commands & command);

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
	bool isPassValidate = tmpClient.getPassValidate();
	const std::string & password = tmpClient.getPassword();

	if (!isPassValidate && password.empty())
		displayError(ERR_NOTREGISTERED, command);
	else if (!isPassValidate && !password.empty())
		displayError(ERR_PASSWDMISMATCH, command);
	else
		sendMessage(tmpClient.getFD(), ":localhost 376 " + tmpClient.getUsername() + " :" + tmpClient.getUsername() + " connected!");
}

void Commands::executeCommand() {

	std::string arrayCommand[] = {"PASS", "NICK", "USER", "JOIN", "PING"};
	void (*arrayFunction[6])(Commands &) = {executePass, executeNick, executeUser, executeJoin, executePing};

	for (int i = 0; i <= 6; i++)
	{
		if (arrayCommand[i] == this->_name)
		{
			(*arrayFunction[i])(*this);
		}
	}
}
