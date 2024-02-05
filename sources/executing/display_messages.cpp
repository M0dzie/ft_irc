/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_messages.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <thmeyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 15:45:25 by msapin            #+#    #+#             */
/*   Updated: 2024/02/05 18:31:13 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands.hpp"
#include "../../includes/Client.hpp"

void    displayError(int errorCode, Commands & command) {

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
	case ERR_NOSUCHCHANNEL:
		std::cout << PURPLE << BOLD << "Warning: " << RESET << command.getClient().getUsername() << " " << *(command.getArgSplit().begin()) << " :No such channel" << std::endl;
		break;
	case ERR_NONICKNAMEGIVEN:
		std::cout << RED << BOLD << "Warning: " << RESET << command.getClient().getUsername() << " :No nickname given" << std::endl;
		break;
	case ERR_NICKNAMEINUSE:
		std::cout << PURPLE << BOLD << "Warning: " << RESET << command.getClient().getUsername() << " " << *(command.getArgSplit().begin()) << " :Nickname is already in use" << std::endl;
		break;
	case ERR_NOSUCHNICK:
		std::cout << PURPLE << BOLD << "Warning: " << RESET << command.getClient().getUsername() << " " << *(command.getArgSplit().begin()) << " :No such nick/channel" << std::endl;
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

void	displayErrorChannel(int errorCode, Client const &client, Channel &channel) {
	switch (errorCode) {
		case ERR_USERONCHANNEL:
			std::cout << PURPLE << BOLD << "Warning: " << RESET << client.getUsername() << " " << client.getNickname() << " " << channel.getName() << " :is already on channel" << std::endl;
			break;
		case ERR_CHANNELISFULL:
			std::cout << PURPLE << BOLD << "Warning: " << RESET << client.getUsername() << " " << channel.getName() << " :Cannot join channel (+l)" << std::endl;
			break;
		case ERR_BADCHANNELKEY:
			std::cout << PURPLE << BOLD << "Warning: " << RESET << client.getUsername() << " " << channel.getName() << " :Cannot join channel (+k)" << std::endl;
			break;
		case ERR_INVITEONLYCHAN:
			std::cout << PURPLE << BOLD << "Warning: " << RESET << client.getUsername() << " " << channel.getName() << " :Cannot join channel (+i)" << std::endl;
			break;
		case ERR_USERNOTINCHANNEL:
			std::cout << PURPLE << BOLD << "Warning: " << RESET << client.getUsername() << " " << channel.getName() << " :They aren't on that channel" << std::endl;
			break;
		case ERR_NOTONCHANNEL:
			std::cout << PURPLE << BOLD << "Warning: " << RESET << client.getUsername() << " " << channel.getName() << " :You're not on that channel" << std::endl;
			break;
		case ERR_CHANOPRIVSNEEDED:
			std::cout << PURPLE << BOLD << "Warning: " << RESET << client.getUsername() << " " << channel.getName() << " :You're not channel operator" << std::endl;
			break;

		default:
			break;
	}
}


void displayRPL(int RPLCode, Client const &client, Channel &channel) {
	
	switch(RPLCode) {
		case RPL_NOTOPIC:
			sendMessage(client.getFD(), ":localhost 331 " + client.getNickname() + " " + channel.getName() + " :No topic is set");
			break;
		case RPL_TOPIC:
			sendMessage(client.getFD(), ":localhost 332 " + client.getNickname() + " " + channel.getName() + " :" + channel.getTopic());
			break;
		case RPL_NAMREPLY:
			sendMessage(client.getFD(), ":localhost 353 " + client.getNickname() + " = " + channel.getName() + " :" + channel.getClientList());
			break;
		case RPL_ENDOFNAMES:
			sendMessage(client.getFD(), ":localhost 366 " + client.getNickname() + " " + channel.getName() + " :End of /NAMES list");
			break;
		case RPL_INVITING:
			sendMessage(client.getFD(), ":localhost 341 " + client.getNickname() + " " + channel.getInvitedList().back() + " " + channel.getName());
			break;
		
		default:
			break;
	}
}
