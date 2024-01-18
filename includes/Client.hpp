/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 10:37:02 by thmeyer           #+#    #+#             */
/*   Updated: 2024/01/18 18:28:28 by msapin           ###   ########.fr       */
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
    std::string _realname;
    std::string _password;
    std::string _lastPing;

    bool _passValidate;
    bool _registered;

public:
    Client(int fd, std::string const &nickname) : _fd(fd), _nickname(nickname), _passValidate(false), _registered(false) {}

    void setFD(int fd) {this->_fd = fd;}
    void setNickname(std::string const &nickname) {this->_nickname = nickname;}
    void setUsername(std::string const &username) {this->_username = username;}
    void setPassword(std::string const &password) {this->_password = password;}
    void setLastPing(std::string const &lastPing) {this->_lastPing = lastPing;}
    void setPassValidate(bool value) {this->_passValidate = value;}
    void setRegister(bool value) {this->_registered = value;}

    int const &getFD() const {return this->_fd;}
    std::string const &getNickname() const {return this->_nickname;}
    std::string const &getUsername() const {return this->_username;}
    std::string const &getPassword() const {return this->_password;}
    std::string const &getLastPing() const {return this->_lastPing;}
    bool getPassValidate() const {return this->_passValidate;}
    bool getRegister() const {return this->_registered;}
};

#endif