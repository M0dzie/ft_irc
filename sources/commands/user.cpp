/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 13:15:37 by msapin            #+#    #+#             */
/*   Updated: 2024/01/17 16:00:55 by msapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands.hpp"

# define USERLEN 18	// put in ft_irc 

bool isUsernameValid(std::string & username) {

	if (username.empty())
		return std::cout << "<client> <command> :Not enough parameters" << std::endl, false;	// ERR_NEEDMOREPARAMS
	else if (username.size() > USERLEN)
		username = username.substr(0, USERLEN);
	return true;
}

void	executeUser(Commands & command) {
	
	// std::cout << "Execute USER" << std::endl;
	std::string username = *command.getArgSplit().begin();

	if (isUsernameValid(username))
	{
		// std::cout << "Set username " << username << std::endl;
		command.getClientPtr()->setUsername(username);

		sendMessage(command.getClientPtr()->getFD(), ":localhost 376 " + username + " :" + username + " connected!");
	}
}
