/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 10:38:04 by thmeyer           #+#    #+#             */
/*   Updated: 2024/01/23 14:08:53 by msapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Client.hpp"

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
