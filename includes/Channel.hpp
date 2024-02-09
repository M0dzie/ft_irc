/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 14:03:03 by thmeyer           #+#    #+#             */
/*   Updated: 2024/02/09 15:53:24 by msapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP
# define CHANNELBASELIMIT 20

# include "ft_irc.hpp"
# include "Commands.hpp"

class Channel {
private:
	Channel();

	std::string _name;
	std::string _password;
	std::string _topic;
	unsigned long _channelLimit;
	bool _inviteOnly;
	bool _topicRestrict;
	bool _isChannelLimited;
	std::map<Client *, bool> _clients;
	std::vector<std::string> _invitedList;
	std::vector<std::string> _modes;
	
public:
	Channel(std::string const &name, std::string const &password) : _name(name), _password(password), _channelLimit(CHANNELBASELIMIT), _inviteOnly(false), _topicRestrict(true), _isChannelLimited(true) {}
	~Channel() {}

	bool isAlreadyIn(std::string const &name);
	bool isInvited(std::string const &name);
	bool setOperator(Client *client);
	bool unsetOperator(Client *client);
	bool areClientOnChannel(std::string const & clientName);
	
	void displayClientList();
	void removeClient(Client *client, Server &server);
	void sendMessageToChannel(std::string msg);
	void updateClients(Client *client, bool first);

	// SETTER
	void setChannelLimit(unsigned long const &limit) {this->_channelLimit = limit;}
	void setInviteOnlyMode(bool inviteOnly) {this->_inviteOnly = inviteOnly;}
	void setTopicRestrict(bool topicRestrict) {this->_topicRestrict = topicRestrict;}
	void setChannelLimited(bool isChannelLimited) {this->_isChannelLimited = isChannelLimited;}
	void setName(std::string const &name) {this->_name = name;}
	void setPassword(std::string const &password) {this->_password = password;}
	void setTopic(std::string const &topic) {this->_topic = topic;}
	void setModes(std::string const &mode, bool plus);

	// GETTER
	std::map<Client *, bool> &getClients() {return this->_clients;}
	std::string getClientList();
	std::vector<std::string> &getInvitedList() {return this->_invitedList;}

	bool const &getInviteOnly() const {return this->_inviteOnly;}
	bool const &getTopicRestrict() const {return this->_topicRestrict;}
	bool const &getChannelLimited() {return this->_isChannelLimited;}

	std::string const &getName() const {return this->_name;}
	std::string const &getPassword() const {return this->_password;}
	std::string const &getTopic() const {return this->_topic;}
	std::string getModes();
	
	unsigned long const &getChannelLimit() const {return this->_channelLimit;}
};

#endif