/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <thmeyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 14:03:03 by thmeyer           #+#    #+#             */
/*   Updated: 2024/02/02 12:04:07 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "ft_irc.hpp"
# include "Commands.hpp"

# define CHANNELBASELIMIT 20

class Channel {
private:
    Channel();

    std::string _name;
    std::string _password;
    std::string _topic;
    unsigned long _channelLimit;
    bool _inviteOnly;
    std::map<Client *, bool> _clients;
    
public:
    Channel(std::string const &name, std::string const &password) : _name(name), _password(password), _channelLimit(CHANNELBASELIMIT), _inviteOnly(false) {}
    ~Channel() {}

    bool isAlreadyIn(std::string const &name);
    void displayClientList();
    void updateClients(Client *client, bool first);
    void setOperator(Client *client) {this->_clients[client] = true;}
    void unsetOperator(Client *client) {this->_clients[client] = false;}
    std::string getClientList();
    std::map<Client *, bool> &getClients() {return this->_clients;}

    void setChannelLimit(unsigned long const &limit) {this->_channelLimit = limit;}
    void setInviteOnlyMode(bool const &inviteOnly) {this->_inviteOnly = inviteOnly;}
    void setName(std::string const &name) {this->_name = name;}
    void setPassword(std::string const &password) {this->_password = password;}
    void setTopic(std::string const &topic) {this->_topic = topic;}

    unsigned long const &getChannelLimit() const {return this->_channelLimit;}
    bool const &getInviteOnly() const {return this->_inviteOnly;}
    std::string const &getName() const {return this->_name;}
    std::string const &getPassword() const {return this->_password;}
    std::string const &getTopic() const {return this->_topic;}
};

#endif