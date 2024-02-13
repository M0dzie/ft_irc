/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 10:38:04 by thmeyer           #+#    #+#             */
/*   Updated: 2024/02/13 11:02:08 by msapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Client.hpp"
#include "../../includes/Channel.hpp"

void	Client::displayError(int errorCode) {
	switch (errorCode)
	{
		case ERR_NOTREGISTERED:
			sendMessage(this->_fd, ":localhost 451 " + this->_nickname + " :You have not registered");
			break;
		case ERR_ALREADYREGISTERED:
			sendMessage(this->_fd, ":localhost 462 " + this->_nickname + " :You may not reregister");
			break;
		case ERR_PASSWDMISMATCH:
			sendMessage(this->_fd, ":localhost 464 " + this->_nickname + " :Password incorrect");
			break;
		case ERR_NONICKNAMEGIVEN:
			sendMessage(this->_fd, ":localhost 431 " + this->_nickname + " :No nickname given");
			break;
		case ERR_CANNOTBEUNDEFINED:
			sendMessage(this->_fd, ":localhost " + this->_nickname + " :Nickname cannot be \"undefined\"");
			break;
		default:
			break;
	}
}

std::string const & Client::getUsername() const {
	if (this->_username.empty())
		return this->getNickname();
	else
		return this->_username;
}

std::string const & Client::getRealname() const {
	if (this->_realname.empty())
		return this->getNickname();
	else
		return this->_realname;
}

void Client::removeOneChannel(Channel * channel) {
	std::vector<Channel *> & tmpChannels = this->getChannels();
	std::string channelName = channel->getName();
	
	for (std::vector<Channel *>::iterator it = tmpChannels.begin(); it != tmpChannels.end(); it++)
	{
		if (channelName == (*it)->getName())
		{
			tmpChannels.erase(it);
			break;
		}
	}
}
