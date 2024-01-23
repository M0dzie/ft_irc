/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_messages.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 15:45:25 by msapin            #+#    #+#             */
/*   Updated: 2024/01/23 14:06:52 by msapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands.hpp"
#include "../../includes/Client.hpp"

void    displayError(int errorCode, Commands & command) {
	(void)command;

	switch (errorCode)
	{
	case ERR_NOTREGISTERED:
		std::cout << PURPLE << BOLD << "Warning: " << RESET << command.getClient().getUsername() << " :You have not registered" << std::endl;
		break;
	case ERR_NEEDMOREPARAMS:
		std::cout << PURPLE << BOLD << "Warning: " << RESET << command.getClient().getUsername() << " " << command.getName() << " :Not enough parameters" << std::endl;
		break;
	case ERR_ALREADYREGISTERED:
		std::cout << PURPLE << BOLD << "Warning: " << RESET << command.getClient().getUsername() << " :You may not reregister" << std::endl;
		break;
	case ERR_PASSWDMISMATCH:
		std::cout << RED << BOLD << "Error: " << RESET << command.getClient().getUsername() << " :Password incorrect" << std::endl;
		break;

	case ERR_CANNOTBEUNDEFINED:
		std::cout << PURPLE << BOLD << "Warning: " << RESET << command.getClient().getUsername() << " :Nickname cannot be \"undefined\"" << std::endl;
		break;
	
	default:
		break;
	}
}
