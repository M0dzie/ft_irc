/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_messages.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 15:45:25 by msapin            #+#    #+#             */
/*   Updated: 2024/01/24 14:09:16 by msapin           ###   ########.fr       */
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
	case ERR_NONICKNAMEGIVEN:
		std::cout << RED << BOLD << "Warning: " << RESET << command.getClient().getUsername() << " :No nickname given" << std::endl;
		break;
	case ERR_NICKNAMEINUSE:
		std::cout << PURPLE << BOLD << "Warning: " << RESET << command.getClient().getUsername() << " " << *(command.getArgSplit().begin()) << " :Nickname is already in use" << std::endl;
		break;
	case ERR_NOSUCHCHANNEL:	// ADD access of channel name
		std::cout << PURPLE << BOLD << "Warning: " << RESET << command.getClient().getUsername() << " " << *(command.getArgSplit().begin()) << " :No such channel" << std::endl;
		break;

	case ERR_CANNOTBEUNDEFINED:
		std::cout << PURPLE << BOLD << "Warning: " << RESET << command.getClient().getUsername() << " :Nickname cannot be \"undefined\"" << std::endl;
		break;
	case ERR_INVALIDARG:
		std::cout << PURPLE << BOLD << "Warning: " << RESET << command.getClient().getUsername() << " " << command.getName() << " :Invalid arguments" << std::endl;
		break;
	
	default:
		break;
	}
}
