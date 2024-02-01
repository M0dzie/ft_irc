/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <thmeyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 14:02:49 by thmeyer           #+#    #+#             */
/*   Updated: 2024/02/01 17:48:05 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Channel.hpp"

std::string Channel::getClientList() {
    std::string display;

    for(std::vector<Client *>::iterator it = this->_clients.begin(); it != this->_clients.end(); it++) {
        Client const *client = *it;
        display += client->getNickname() + " ";
    }
    
    return display;
}

void Channel::displayClientList() {
    for(std::vector<Client *>::iterator it = this->_clients.begin(); it != this->_clients.end(); it++) {
        Client const *client = *it;
        displayRPL(RPL_NAMREPLY, *client, *this);
	    displayRPL(RPL_ENDOFNAMES, *client, *this);
    }
}

void Channel::updateClients(Client *client) {
    this->_clients.push_back(client);
}

bool Channel::isAlreadyIn(std::string const &name) {
    for (std::vector<Client *>::iterator it = this->_clients.begin(); it != this->_clients.end(); it++) {
        Client *tmp = *it;
        if (tmp->getNickname() == name)
            return true;
    }
    return false;
}