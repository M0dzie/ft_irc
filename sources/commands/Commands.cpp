/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 12:42:52 by msapin            #+#    #+#             */
/*   Updated: 2024/01/16 18:15:56 by msapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands.hpp"

void	executeJoin(Commands & command);
void	executeNick(Commands & command);
void	executeUser(Commands & command);

Commands::Commands(std::string line) {

    (void)line;
    std::cout << "Create Commands " << line << std::endl;
}

void Commands::executeCommand() {

	std::string arrayCommand[] = {"NICK", "USER", "JOIN"};
	void (*arrayFunction[4])(Commands &) = {executeNick, executeUser, executeJoin};
    (void)arrayFunction;

	// std::cout << "LINE: " << line << std::endl;

	// std::stringstream streamLine(line);
	// std::string word;
	// std::vector<std::string> lineSplit;

	// while (streamLine >> word)
	// {
	// 	lineSplit.push_back(word);
	// }

	// for (int i = 0; i <= 1; i++)
	// {
	// 	if (arrayCommand[i] == *lineSplit.begin())
	// 	{
	// 		(*arrayFunction[i])(lineSplit, fd);
	// 	}
	// }
}
