/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 12:43:15 by msapin            #+#    #+#             */
/*   Updated: 2024/02/14 11:31:14 by msapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_HPP
# define COMMANDS_HPP

# include "Server.hpp"
# include "Client.hpp"
# include "Channel.hpp"

# define ERR_CANNOTBEUNDEFINED -1
# define ERR_INVALIDARG -2

# define ERR_NOSUCHNICK 401
# define ERR_NOSUCHCHANNEL 403
# define ERR_NONICKNAMEGIVEN 431
# define ERR_NICKNAMEINUSE 433
# define ERR_USERNOTINCHANNEL 441
# define ERR_NOTONCHANNEL 442
# define ERR_USERONCHANNEL 443
# define ERR_NOTREGISTERED 451
# define ERR_NEEDMOREPARAMS 461
# define ERR_ALREADYREGISTERED 462
# define ERR_PASSWDMISMATCH 464
# define ERR_CHANNELISFULL 471
# define ERR_INVITEONLYCHAN 473
# define ERR_BADCHANNELKEY 475
# define ERR_CHANOPRIVSNEEDED 482
# define ERR_UMODEUNKNOWNFLAG 501

# define RPL_CHANNELMODEIS 324
# define RPL_NOTOPIC 331
# define RPL_TOPIC 332
# define RPL_INVITING 341
# define RPL_NAMREPLY 353
# define RPL_ENDOFNAMES 366
# define RPL_WELCOME 001
# define RPL_MOTD 372
# define RPL_MOTDSTART 375
# define RPL_ENDOFMOTD 376

# define PASS "+k"
# define RMVPASS "-k"
# define INVITEONLY "+i"
# define RMVINVITEONLY "-i"
# define TOPICRESTRICT "+t"
# define RMVTOPICRESTRICT "-t"
# define OPECHAN "+o"
# define RMVOPECHAN "-o"
# define CHANLIMIT "+l"
# define RMVCHANLIMIT "-l"

class Commands {

	private:
		Commands(void);
		std::string _name;
		std::vector<std::string> _argSplit;

		Client & _client;
		Server & _server;

	public:
		Commands(std::string & line, Client & client, Server & server);
		~Commands(void) {}

		int executeCommand();
		
		void	displayError(int errorCode);

		// GETTER
		std::string const & getName() const {return this->_name;}
		std::vector<std::string> & getArgSplit() {return this->_argSplit;}
		
		Client & getClient() {return this->_client;}
		Server & getServer() {return this->_server;}
};

void	login(Commands & command);
void	sendMessage(int clientFd, std::string msg);
void	clearClient(Server & tmpServer, Client & tmpClient);
void	clearFromChannel(Server & tmpServer, Client & tmpClient, std::string msg);

Client & foundClient(Commands & command, std::string nickname);

std::string getReason(std::vector<std::string> argSplit);

#endif
