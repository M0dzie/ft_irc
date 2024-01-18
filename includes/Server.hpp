/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <thmeyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 10:36:14 by thmeyer           #+#    #+#             */
/*   Updated: 2024/01/18 13:11:13 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include "ft_irc.hpp"

# define MAXCLIENT 1000

class Client;

class Server {
private:
    Server();

    int _nbClient;
    std::string _password;
    socklen_t _addrLen;
    struct pollfd _fds[MAXCLIENT + 1]; // + 1 for serverFd
    struct sockaddr_in _address;
    std::map<int, Client *> _clientList;
    
    static bool interrupt;

public:
    Server(int port, char *password);
    ~Server();

    void exit();
    void handlingSignal();
    void initDataAndServer(int port, char *password);
    void sendMessage(int clientFd, std::string msg);
    
    static void handleBreak(int sig);

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