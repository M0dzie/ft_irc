/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <thmeyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 10:37:02 by thmeyer           #+#    #+#             */
/*   Updated: 2024/02/07 18:55:42 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# define BUFFERSIZE 1024

# include "ft_irc.hpp"

class Channel;

class Client {
private:
	Client() {}

	int _fd;
	std::string _nickname;
	std::string _username;
	std::string _realname;
	std::string _password;
	std::string _lastPing;
	
	std::string _bufferLine;

	std::vector<Channel *> _channels;

	// char	_buffer[BUFFERSIZE];

	bool _registered;

public:
	Client(int fd, std::string const &nickname) : _fd(fd), _nickname(nickname), _registered(false) {}
	// Client(int fd, std::string const &nickname) : _fd(fd), _nickname(nickname), _registered(false) {this->clearBuffer();}

	void setFD(int fd) {this->_fd = fd;}
	void setNickname(std::string const &nickname) {this->_nickname = nickname;}
	void setUsername(std::string const &username) {this->_username = username;}
	void setRealname(std::string const &realname) {this->_realname = realname;}
	void setPassword(std::string const &password) {this->_password = password;}
	void setLastPing(std::string const &lastPing) {this->_lastPing = lastPing;}
	void setRegister(bool value) {this->_registered = value;}

	void addChannels(Channel * channel) {this->_channels.push_back(channel);}
	void removeOneChannel(Channel * channel);

	// void	clearBuffer();

	bool operator==(Client const & rhs) const {return this->_nickname == rhs.getNickname();}

	int const &getFD() const {return this->_fd;}
	std::string const &getNickname() const {return this->_nickname;}
	std::string const &getUsername() const;
	std::string const &getRealname() const;
	std::string const &getPassword() const {return this->_password;}
	std::string const &getLastPing() const {return this->_lastPing;}
	std::vector<Channel *> & getChannels() {return this->_channels;}
	// char *	getBuffer() {return this->_buffer;}
	std::string & getBufferLine() {return this->_bufferLine;}
	bool getRegister() const {return this->_registered;}
};

#endif