/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <thmeyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 14:03:03 by thmeyer           #+#    #+#             */
/*   Updated: 2024/02/06 16:38:39 by thmeyer          ###   ########.fr       */
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
    std::vector<std::string> _invitedList;
    std::vector<std::string> _modes;
    
public:
    Channel(std::string const &name, std::string const &password) : _name(name), _password(password), _channelLimit(CHANNELBASELIMIT), _inviteOnly(false) {}
    ~Channel() {}

    bool isAlreadyIn(std::string const &name);
    bool isInvited(std::string const &name);
    void displayClientList();
    void removeClient(Client *client, Server &server);
    void sendMessageToChannel(std::string msg);
    void setOperator(Client *client) {this->_clients[client] = true;}
    void updateClients(Client *client, bool first);
    void unsetOperator(Client *client) {this->_clients[client] = false;}
    std::map<Client *, bool> &getClients() {return this->_clients;}
    std::string getClientList();
    std::vector<std::string> &getInvitedList() {return this->_invitedList;}

    void setChannelLimit(unsigned long const &limit) {this->_channelLimit = limit;}
    void setInviteOnlyMode(bool inviteOnly) {this->_inviteOnly = inviteOnly;}
    void setName(std::string const &name) {this->_name = name;}
    void setPassword(std::string const &password) {this->_password = password;}
    void setTopic(std::string const &topic) {this->_topic = topic;}
    void setModes(std::string const &mode, bool plus);

    bool const &getInviteOnly() const {return this->_inviteOnly;}
    std::string const &getName() const {return this->_name;}
    std::string const &getPassword() const {return this->_password;}
    std::string const &getTopic() const {return this->_topic;}
    std::string getModes();
    unsigned long const &getChannelLimit() const {return this->_channelLimit;}
};

#endif