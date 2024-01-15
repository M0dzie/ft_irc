/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <thmeyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 10:37:02 by thmeyer           #+#    #+#             */
/*   Updated: 2024/01/15 14:49:50 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include "ft_irc.hpp"

class Client {
private:
    Client() {}

    int _fd;
    std::string _nickname;
    std::string _username;

public:
    Client(int fd, std::string const &nickname) : _fd(fd), _nickname(nickname) {}

    void setFD(int fd) {this->_fd = fd;}
    void setNickname(std::string const &nickname) {this->_nickname = nickname;}
    void setUsername(std::string const &username) {this->_username = username;}

    int const &getFD() const {return this->_fd;}
    std::string const &getNickname() const {return this->_nickname;}
    std::string const &getUsername() const {return this->_username;}
};

#endif