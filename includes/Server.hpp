/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 10:36:14 by thmeyer           #+#    #+#             */
/*   Updated: 2024/02/07 16:58:08 by msapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include "ft_irc.hpp"

# define MAXCLIENT 1000
# define SERVER 1
# define CLIENT 2
# define INFO 3

class Client;
class Channel;

class Server {
private:
    Server();

    int _nbClient;
    std::string _password;
    socklen_t _addrLen;
    struct pollfd _fds[MAXCLIENT + 1]; // + 1 for serverFd
    struct sockaddr_in _address;
    std::map<int, Client *> _clientList;
    std::map<std::string, Channel *> _channelList;
    
    static bool interrupt;

public:
    Server(int port, char *password);
    ~Server();

    void exit();
    void handlingSignal();
    void initDataAndServer(int port, char *password);
    void sendMessage(int clientFd, std::string msg);

    std::string const &getPassword() const {return this->_password;}
    std::map<int, Client *> &getClientList() {return this->_clientList;}
    std::map<std::string, Channel *> &getChannelList() {return this->_channelList;}
    int getNbClient() const {return this->_nbClient;}
    struct pollfd * getPollFds() {return this->_fds;};

    void setNbClient(int value) {this->_nbClient = value;}
    void setFDValue(int value, int index) {this->_fds[index].fd = value;}
    
    static void handleBreak(int sig);
    int	recoverCommandLine(Client & tmpClient);

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