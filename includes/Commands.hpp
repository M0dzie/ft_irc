/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 12:43:15 by msapin            #+#    #+#             */
/*   Updated: 2024/01/17 14:41:14 by msapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_HPP
# define COMMANDS_HPP
# include "ft_irc.hpp"

void	sendMessage(int clientFd, std::string msg);

class Commands {

	private:
		Commands(void);
		std::string _name;
		std::vector<std::string> _argSplit;
		// std::map<std::string, std::vector<std::string> > _mapArguments;

		Client *_clientPtr;

	public:
		Commands(std::string line, Client * ptr);
		~Commands(void);

		void executeCommand();
		std::string const & getName() const {return this->_name;}
		std::vector<std::string> const & getArgSplit() const {return this->_argSplit;}
		Client * getClientPtr() {return this->_clientPtr;}
};
#endif
