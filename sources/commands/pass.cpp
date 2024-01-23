/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 17:28:24 by msapin            #+#    #+#             */
/*   Updated: 2024/01/23 14:20:04 by msapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands.hpp"

void	executePass(Commands & command) {

	std::vector<std::string> tmpArgs = command.getArgSplit();

	if (tmpArgs.begin() == tmpArgs.end())
		displayError(ERR_NEEDMOREPARAMS, command);
	else
	{
		std::string password = *(command.getArgSplit().begin());
		Client & tmpClient = command.getClient();
		bool isRegistered = tmpClient.getRegister();

		if (password.empty())
			displayError(ERR_NEEDMOREPARAMS, command);

		// std::cout << "|" << password << "|" << std::endl;
		if (isRegistered)
			displayError(ERR_ALREADYREGISTERED, command);
		else
		{
			if (password.empty())
				displayError(ERR_NEEDMOREPARAMS, command);
			else
			{
				tmpClient.setPassword(password);
				if (password == command.getServer().getPassword())
					tmpClient.setPassValidate(true);
				else
					tmpClient.setPassValidate(false);
			}
		}
	}
}
