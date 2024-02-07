/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 10:38:04 by thmeyer           #+#    #+#             */
/*   Updated: 2024/02/07 12:53:30 by msapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Client.hpp"
#include "../../includes/Channel.hpp"

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

void	Client::clearBuffer() {
	for (int i = 0; i < BUFFERSIZE; i++)
		this->_buffer[i] = '\0';
}
