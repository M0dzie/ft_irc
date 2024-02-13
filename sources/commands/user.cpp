/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 13:15:37 by msapin            #+#    #+#             */
/*   Updated: 2024/02/13 18:54:03 by msapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands.hpp"

static bool isUserArgValid(std::vector<std::string> & tmpArgs, Commands & command, std::string & tmpRealname) {
	std::vector<std::string>::iterator it = tmpArgs.begin();

	if (it->empty())
		return command.displayError(ERR_NEEDMOREPARAMS), false;
	else if (it->size() > USERLEN)
		*it = it->substr(0, USERLEN);
		
	if (*(++it) != "0")
		return command.displayError(ERR_INVALIDARG), false;
	if (!(*(++it) == "*" || *(it) == "0"))
		return command.displayError(ERR_INVALIDARG), false;
	
	while (++it != tmpArgs.end())
		tmpRealname += *(it);
	if (tmpRealname[0] != ':' || !tmpRealname[1])
		return command.displayError(ERR_INVALIDARG), false;
	return true;
}

void	executeUser(Commands & command) {
	std::vector<std::string> tmpArgs = command.getArgSplit();

	if (tmpArgs.empty() || tmpArgs.size() < 4)
		command.displayError(ERR_NEEDMOREPARAMS);
	else
	{
		std::string tmpRealname;
		
		if (isUserArgValid(tmpArgs, command, tmpRealname))
		{
			command.getClient().setUsername(*tmpArgs.begin());
			command.getClient().setRealname(tmpRealname);
			command.getClient().setValidUser(true);
			login(command);
		}
		else
			command.getClient().setValidUser(false);
	}
}
