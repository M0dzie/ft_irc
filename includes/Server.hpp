/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <thmeyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 10:36:14 by thmeyer           #+#    #+#             */
/*   Updated: 2024/01/10 14:42:12 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include "ft_irc.hpp"

# define MAXCLIENT 1

class Server {
private:
    Server();

public:
    Server(int port);
    ~Server() {}

    class ServerError: public std::exception {
    private:
        const char *_error;

    public:
        ServerError(const char *error) : _error(error) {}
        virtual const char *what() const throw() {
            return _error;
        }
    };
};

#endif