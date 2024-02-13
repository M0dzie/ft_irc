/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 17:28:24 by msapin            #+#    #+#             */
/*   Updated: 2024/02/13 16:12:04 by msapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands.hpp"

void	executePass(Commands & command) {
	std::vector<std::string> tmpArgs = command.getArgSplit();

	if (tmpArgs.begin() == tmpArgs.end())
		command.displayError(ERR_NEEDMOREPARAMS);
	else
	{
		Client & client = command.getClient();
		std::string password = *(command.getArgSplit().begin());
		bool isRegistered = client.getRegister();

		if (password.empty())
			command.displayError(ERR_NEEDMOREPARAMS);
		else if (isRegistered)
			client.displayError(ERR_ALREADYREGISTERED);
		else
		{
			if (password.empty())
				command.displayError(ERR_NEEDMOREPARAMS);
			else
			{
				displayMessage(INFO, "Connection password set (" + password + ")");
				client.setPassword(password);
			}
		}
	}
}
