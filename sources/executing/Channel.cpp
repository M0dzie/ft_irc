/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <thmeyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 14:02:49 by thmeyer           #+#    #+#             */
/*   Updated: 2024/02/05 13:07:51 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Channel.hpp"

std::string Channel::getClientList() {
    std::string display;

    for(std::map<Client *, bool>::iterator it = this->_clients.begin(); it != this->_clients.end(); it++) {
        Client *client = it->first;
        if (this->_clients[client])
            display += "@";
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

void Channel::sendMessageToChannel(std::string msg) {
	for (std::map<Client *, bool>::iterator it = this->_clients.begin(); it != this->_clients.end(); it++)
		sendMessage((it->first)->getFD(), msg);
}

void Channel::removeClient(Client *client, Server &server) {
    for (std::map<Client *, bool>::iterator it = this->_clients.begin(); it != this->_clients.end(); it++) {
        if (it->first == client) {
            this->_clients.erase(it->first);
            this->displayClientList();
            break;
        }
    }

    // check if an operator is still available, if not, upgrade the older member
    bool found = false;
    for (std::map<Client *, bool>::iterator it = this->_clients.begin(); it != this->_clients.end(); it++)
        if (it->second)
            found = true;
    if (!found) {
        this->setOperator(this->_clients.begin()->first);
        this->displayClientList();
    }

    // if there's no member left, delete the channel
    if (this->_clients.empty()) {
        server.getChannelList().erase(this->_name);
        delete this;
    }
}