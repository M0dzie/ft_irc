/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <thmeyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 14:02:49 by thmeyer           #+#    #+#             */
/*   Updated: 2024/02/01 15:11:37 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Channel.hpp"

bool Channel::isAlreadyIn(std::string const &name) {
    for (std::vector<Client *>::iterator it = this->_clientIn.begin(); it != this->_clientIn.end(); it++) {
        Client *tmp = *it;
        if (tmp->getNickname() == name)
            return true;
    }
    return false;
}