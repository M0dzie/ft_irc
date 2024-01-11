/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <thmeyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 10:36:14 by thmeyer           #+#    #+#             */
/*   Updated: 2024/01/11 12:30:58 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include "ft_irc.hpp"

# define MAXCLIENT 200

class Server {
private:
    Server();

    int _opt;
    int _nbClient;
    bool _interrupt;
    socklen_t _addrLen;
    struct pollfd _fds[MAXCLIENT + 1]; // + 1 for serverFd
    struct sockaddr_in _address;

public:
    Server(int port);
    ~Server() {}

    void initDataAndServer(int port);
    void sendMessage(int clientFd, std::string msg);

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