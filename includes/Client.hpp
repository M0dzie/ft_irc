/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <thmeyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 10:37:02 by thmeyer           #+#    #+#             */
/*   Updated: 2024/01/15 14:20:02 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include "ft_irc.hpp"

class Client {
private:
    Client() {}

    int _id;
    std::string _nickname;
    std::string _user;

public:
    Client(int id) : _id(id) {}

    void setID(int const &id) {this->_id = id;}
    void setNickname(std::string const &nickname) {this->_nickname = nickname;}
    void setUser(std::string const &user) {this->_user = user;}

    int const &getID() const {return this->_id;}
    std::string const &getNickname() const {return this->_nickname;}
    std::string const &getUser() const {return this->_user;}
};

#endif