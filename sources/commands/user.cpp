/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 13:15:37 by msapin            #+#    #+#             */
/*   Updated: 2024/01/18 17:39:43 by msapin           ###   ########.fr       */
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

std::string extractRealname() {

	std::string realname;

	realname = "test";
	return realname;
}

void	executeUser(Commands & command) {

	(void)command;
	
	std::string username = *command.getArgSplit().begin();

	if (isUsernameValid(username))
	{
		command.getClient().setUsername(username);

		login(command);
	}
}
