/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <thmeyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 12:42:52 by msapin            #+#    #+#             */
/*   Updated: 2024/02/08 16:48:31 by thmeyer          ###   ########.fr       */
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

bool ignoreCommand(std::string & cmdName) {
	
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
		if (i == 12)
			std::cout << PURPLE << BOLD << "Warning: " << RESET << this->getClient().getUsername() << " " << this->_name << " :Unknown command" << std::endl;
	}
	if (i == 5)
		return 0;
	return 1;
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
