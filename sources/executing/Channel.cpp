/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <thmeyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 14:02:49 by thmeyer           #+#    #+#             */
/*   Updated: 2024/02/01 14:58:11 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Channel.hpp"

bool Channel::isAlreadyIn(Client *client) {
    if (std::find(this->_clientIn.begin(), this->_clientIn.end(), client) != this->_clientIn.end())
        return true;
    return false;
}