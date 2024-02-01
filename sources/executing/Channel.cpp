/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <thmeyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 14:02:49 by thmeyer           #+#    #+#             */
/*   Updated: 2024/02/01 16:06:13 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Channel.hpp"

std::string Channel::displayClientList() {
    std::string display;

    for(std::vector<Client *>::iterator it = this->_clientIn.begin(); it != this->_clientIn.end(); it++) {
        Client const *client = *it;
        display += client->getNickname() + " ";
    }
    
    return display;
}

void Channel::updateClientList() {
    for(std::vector<Client *>::iterator it = this->_clientIn.begin(); it != this->_clientIn.end(); it++) {
        Client const *client = *it;
        displayRPL(RPL_NAMREPLY, *client, *this);
	    displayRPL(RPL_ENDOFNAMES, *client, *this);
    }
}

bool Channel::isAlreadyIn(std::string const &name) {
    for (std::vector<Client *>::iterator it = this->_clientIn.begin(); it != this->_clientIn.end(); it++) {
        Client *tmp = *it;
        if (tmp->getNickname() == name)
            return true;
    }
    return false;
}