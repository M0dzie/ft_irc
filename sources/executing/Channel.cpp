/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <thmeyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 14:02:49 by thmeyer           #+#    #+#             */
/*   Updated: 2024/02/01 18:07:06 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Channel.hpp"

std::string Channel::getClientList() {
    std::string display;

    for(std::map<Client *, bool>::iterator it = this->_clients.begin(); it != this->_clients.end(); it++) {
        Client *client = it->first;
        display += client->getNickname() + " ";
    }
    
    return display;
}

void Channel::displayClientList() {
    for (std::map<Client *, bool>::iterator it = this->_clients.begin(); it != this->_clients.end(); it++) {
        Client *client = it->first;
        displayRPL(RPL_NAMREPLY, *client, *this);
	    displayRPL(RPL_ENDOFNAMES, *client, *this);
    }
}

void Channel::updateClients(Client *client, bool first) {
    if (first)
        this->_clients.insert(std::pair<Client *, bool>(client, true));
    else
        this->_clients.insert(std::pair<Client *, bool>(client, false));
}

bool Channel::isAlreadyIn(std::string const &name) {
    for (std::map<Client *, bool>::iterator it = this->_clients.begin(); it != this->_clients.end(); it++) {
        Client *tmp = it->first;
        if (tmp->getNickname() == name)
            return true;
    }
    return false;
}