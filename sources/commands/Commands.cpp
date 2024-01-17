/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 12:42:52 by msapin            #+#    #+#             */
/*   Updated: 2024/01/17 16:05:49 by msapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands.hpp"

void	executeJoin(Commands & command);
void	executeNick(Commands & command);
void	executeUser(Commands & command);
void	executePing(Commands & command);

Commands::Commands(std::string line, Client * ptr) : _clientPtr(ptr) {

	std::cout << "Create Commands " << line << " " << this->_clientPtr->getNickname() << std::endl;

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

void Commands::executeCommand() {

	std::string arrayCommand[] = {"NICK", "USER", "JOIN", "PING"};
	void (*arrayFunction[5])(Commands &) = {executeNick, executeUser, executeJoin, executePing};

	for (int i = 0; i <= 1; i++)
	{
		if (arrayCommand[i] == this->_name)
		{
			(*arrayFunction[i])(*this);
		}
	}
}
