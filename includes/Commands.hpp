/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 12:43:15 by msapin            #+#    #+#             */
/*   Updated: 2024/01/23 13:57:24 by msapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef COMMANDS_HPP
# define COMMANDS_HPP
# include "Server.hpp"
# include "Client.hpp"
# include "Channel.hpp"
///////////////////////////////// SETUP OTHER NUMBER LATER
# define ERR_CANNOTBEUNDEFINED -1

# define ERR_NOTREGISTERED 451
# define ERR_NEEDMOREPARAMS 461
# define ERR_ALREADYREGISTERED 462
# define ERR_PASSWDMISMATCH 464

class Commands {

	private:
		Commands(void);
		std::string _name;
		std::vector<std::string> _argSplit;

		Client & _client;
		Server & _server;

	public:
		Commands(std::string & line, Client & client, Server & server);
		~Commands(void);

		void executeCommand();
		std::string const & getName() const {return this->_name;}
		std::vector<std::string> & getArgSplit() {return this->_argSplit;}
		Client & getClient() {return this->_client;}
		Server & getServer() {return this->_server;}
};

void	login(Commands & command);
void	sendMessage(int clientFd, std::string msg);
void    displayError(int errorCode, Commands & command);

#endif
