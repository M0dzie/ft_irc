/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <thmeyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 14:03:03 by thmeyer           #+#    #+#             */
/*   Updated: 2024/01/25 13:34:19 by thmeyer          ###   ########.fr       */
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
    unsigned int _channelLimit;
    bool _inviteOnly;
    
public:
    Channel(std::string const &name, std::string const &password) : _name(name), _password(password) {}
    ~Channel() {}

    void updateClientIn(std::string const &name) {this->_clientIn.push_back(name);}
    bool isAlreadyIn(std::string const &name);

    void setChannelLimit(unsigned int const &limit) {this->_channelLimit = limit;}
    void setInviteOnlyMode(bool const &inviteOnly) {this->_inviteOnly = inviteOnly;}
    void setName(std::string const &name) {this->_name = name;}
    void setPassword(std::string const &password) {this->_password = password;}

    std::vector<std::string>  const &getClientIn() const {return this->_clientIn;}
    bool const &getInviteOnly() const {return this->_inviteOnly;}
    unsigned int const &getChannelLimit() const {return this->_channelLimit;}
    std::string const &getName() const {return this->_name;}
    std::string const &getPassword() const {return this->_password;}
};

#endif