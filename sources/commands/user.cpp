/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 13:15:37 by msapin            #+#    #+#             */
/*   Updated: 2024/01/22 17:49:30 by msapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands.hpp"

# define USERLEN 18	// put in ft_irc 

bool isUsernameValid(std::string & username, Commands & command) {

	if (username.empty())
		return displayError(ERR_NEEDMOREPARAMS, command), false;
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

	if (isUsernameValid(username, command))
	{
		command.getClient().setUsername(username);

		login(command);
	}
}
