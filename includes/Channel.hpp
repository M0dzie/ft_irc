/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <thmeyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 14:03:03 by thmeyer           #+#    #+#             */
/*   Updated: 2024/02/01 12:51:33 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "ft_irc.hpp"

# define CHANNELBASELIMIT 20

class Channel {
private:
    Channel();

    std::string _name;
    std::string _password;
    std::vector<std::string> _clientIn;
    unsigned long _channelLimit;
    bool _inviteOnly;
    std::string _topic;
    
public:
    Channel(std::string const &name, std::string const &password) : _name(name), _password(password), _channelLimit(CHANNELBASELIMIT), _inviteOnly(false) {}
    ~Channel() {}

    void updateClientIn(std::string const &name) {this->_clientIn.push_back(name);}
    bool isAlreadyIn(std::string const &name);

    void setChannelLimit(unsigned long const &limit) {this->_channelLimit = limit;}
    void setInviteOnlyMode(bool const &inviteOnly) {this->_inviteOnly = inviteOnly;}
    void setName(std::string const &name) {this->_name = name;}
    void setTopic(std::string const &topic) {this->_topic = topic;}
    void setPassword(std::string const &password) {this->_password = password;}

    std::vector<std::string>  const &getClientIn() const {return this->_clientIn;}
    bool const &getInviteOnly() const {return this->_inviteOnly;}
    unsigned long const &getChannelLimit() const {return this->_channelLimit;}
    std::string const &getName() const {return this->_name;}
    std::string const &getTopic() const {return this->_topic;}
    std::string const &getPassword() const {return this->_password;}
};

#endif