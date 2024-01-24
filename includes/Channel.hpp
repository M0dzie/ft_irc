/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <thmeyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 14:03:03 by thmeyer           #+#    #+#             */
/*   Updated: 2024/01/24 15:49:03 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "ft_irc.hpp"

class Channel {
private:
    Channel();

    std::string _name;
    std::string _password;
    std::vector<std::string> _clientIn;
    
public:
    Channel(std::string const &name, std::string const &password) : _name(name), _password(password) {}
    ~Channel() {}

    void updateClientIn(std::string const &name) {this->_clientIn.push_back(name);}
    bool isAlreadyIn(std::string const &name);

    void setName(std::string const &name) {this->_name = name;}
    void setPassword(std::string const &password) {this->_password = password;}

    std::string const &getName() const {return this->_name;}
    std::string const &getPassword() const {return this->_password;}
};

#endif