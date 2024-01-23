/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 13:15:37 by msapin            #+#    #+#             */
/*   Updated: 2024/01/23 16:59:50 by msapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands.hpp"

# define USERLEN 18	// put in ft_irc 

bool isUserArgValid(std::vector<std::string> & tmpArgs, Commands & command) {

	std::vector<std::string>::iterator it = tmpArgs.begin();

	if (it->empty())
		return displayError(ERR_NEEDMOREPARAMS, command), false;
	else if (it->size() > USERLEN)
		*it = it->substr(0, USERLEN);

	if (*(++it) != "0")
		return displayError(ERR_INVALIDARG, command), false;	// check if need to display with argument
	if (*(++it) != "*")
		return displayError(ERR_INVALIDARG, command), false;	// check if need to display with argument

	std::string realname = *(++it);
	if (realname[0] != ':')
		return displayError(ERR_INVALIDARG, command), false;
	return true;
}

void	executeUser(Commands & command) {
	
	std::vector<std::string> tmpArgs = command.getArgSplit();

	if (command.getClient().getRegister())
		displayError(ERR_ALREADYREGISTERED, command);
	else if (!command.getClient().getPassValidate() && command.getClient().getPassword().empty())
		displayError(ERR_NOTREGISTERED, command);
	else if (command.getClient().getNickname() == "undefined")
		displayError(ERR_CANNOTBEUNDEFINED, command);
	else
	{
		if (tmpArgs.empty() || tmpArgs.size() != 4)
			displayError(ERR_NEEDMOREPARAMS, command);
		else
		{
			if (isUserArgValid(tmpArgs, command))
			{
				command.getClient().setUsername(*tmpArgs.begin());
				command.getClient().setRealname((*(--tmpArgs.end())).erase(0, 1));
				login(command);
			}
		}
	}
}
