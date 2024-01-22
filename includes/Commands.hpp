/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <thmeyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 12:43:15 by msapin            #+#    #+#             */
/*   Updated: 2024/01/22 16:36:56 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_HPP
# define COMMANDS_HPP
# include "Server.hpp"
# include "Client.hpp"
# include "Channel.hpp"

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

#endif
