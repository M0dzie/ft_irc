/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 13:15:37 by msapin            #+#    #+#             */
/*   Updated: 2024/02/12 18:56:31 by msapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands.hpp"

static bool isUserArgValid(std::vector<std::string> & tmpArgs, Commands & command, std::string & tmpRealname) {
	std::vector<std::string>::iterator it = tmpArgs.begin();

	if (it->empty())
		return displayError(ERR_NEEDMOREPARAMS, command), false;
	else if (it->size() > USERLEN)
		*it = it->substr(0, USERLEN);
		
	if (*(++it) != "0")
		return displayError(ERR_INVALIDARG, command), false;
	if (!(*(++it) == "*" || *(it) == "0"))
		return displayError(ERR_INVALIDARG, command), false;
	
	while (++it != tmpArgs.end())
		tmpRealname += *(it);
	if (tmpRealname[0] != ':' || !tmpRealname[1])
		return displayError(ERR_INVALIDARG, command), false;
	return true;
}

void	executeUser(Commands & command) {
	std::vector<std::string> tmpArgs = command.getArgSplit();
	Client & client = command.getClient();

	if (command.getClient().getRegister())
		client.displayErrorClient(ERR_ALREADYREGISTERED);
	else if (command.getClient().getPassword().empty())
		client.displayErrorClient(ERR_NOTREGISTERED);
	else if (command.getClient().getNickname() == "undefined")
		client.displayErrorClient(ERR_CANNOTBEUNDEFINED);
	else
	{
		if (tmpArgs.empty() || tmpArgs.size() < 4)
			displayError(ERR_NEEDMOREPARAMS, command);
		else
		{
			std::string tmpRealname;
			
			if (isUserArgValid(tmpArgs, command, tmpRealname))
			{
				command.getClient().setUsername(*tmpArgs.begin());
				command.getClient().setRealname(tmpRealname);
				login(command);
			}
		}
	}
}
